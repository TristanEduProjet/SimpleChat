#include <iostream>
#include <cstdlib>
#include <cstdbool>
#include <cstring>
#include <list>
#include <atomic>
#include <csignal>
#include "common/network.hpp"
#if !(defined(WIN32) || defined(_WIN32))
#include <arpa/inet.h>
#endif // defined
#include "common/data.hpp"
#include "common/utils.hpp"
#include <unistd.h>
#include <cerrno>
#include <utility> //as_const
#include <algorithm> //max, max_element
#include <thread>
#include <chrono>
#include <queue>

std::atomic<bool> global_exit(false);
void signals_handle(const int signal) {
    std::cout << "signal capturé : exit demandé" << std::endl;
    global_exit.store(true);
}

#define BUFFER_SIZE (2048+1) //2k +1

const static std::string welcome_msg("Server v?\r\nBienvenu to the <servername> server.\r\n");

int main_wait_client(SOCKET const& socketSrv, SockAddress const& addrSrv, const std::shared_ptr<std::list<SOCKET>> &connections, const std::shared_ptr<std::queue<std::string>> &msg);
void check_new_clients(SOCKET const& socketSrv, fd_set const& readfs, const std::shared_ptr<std::list<SOCKET>> &connections);
void check_incoming_msg(fd_set const& readfs, const std::shared_ptr<std::list<SOCKET>> &connections, const std::shared_ptr<std::queue<std::string>> &message);
void loop_for_client(const SOCKET socketSrv, const std::shared_ptr<std::list<SOCKET>> connections, const std::shared_ptr<std::queue<std::string>> msg);

int main(const int argc, const char *argv[])
{
    #if defined (WIN32) || defined (_WIN32)
        WSADATA wsa_data;
        if(WSAStartup(MAKEWORD(2, 2), &wsa_data) != NO_ERROR) {
            std::cerr << "WIN: winsock2: Error" << std::endl;
            print_net_error("Problem when initialize WSA");
            return EXIT_FAILURE;
        } else
            std::cout << "WIN: winsock2: OK" << std::endl;
    #endif
    int return_code = EXIT_SUCCESS;//!< design choisi pour permettre la fermeture des ressources (au lieu d'un return ou exit())
    /* open a socket in TCP/IP mode */
    SOCKET socketSrv = new_socket_tcp(); // Création d'une socket TCP
    if(socketSrv == INVALID_SOCKET) {
        print_net_error("Error while creating socket");
        return_code = EXIT_FAILURE;
    } else {
        int opt = 1; //TRUE
        if(setsockopt(socketSrv, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt)) != 0) //autoriser socket srv multiples connexions
            print_net_error("Error while config server socket"); //not necessary
        std::cout << "socket " << socketSrv << " is now opened in TCP/IP mode" << std::endl;
        SockAddress addrSrv = new_socket_address(PORT);
        if(bind(socketSrv, &(addrSrv.addr), /*INET_ADDRSTRLEN*/sizeof(addrSrv.addr)) != 0) { // Attachement de l'adresse à la socket du recepteur
            print_error("problem for biding the connection");
            return_code = EXIT_FAILURE;
        } else {
            if(listen(socketSrv, SOMAXCONN) != 0 /*SOCKET_ERROR*/) { //start listening (server mode)
                print_net_error("Problem for listening");
                return_code = EXIT_FAILURE;
            } else {
                std::cout << "server listening on port " << PORT << " ..." << std::endl;
                /* settings thread for messages and signal for stop */
                std::shared_ptr<std::list<SOCKET>> connections(new std::list<SOCKET>());
                std::shared_ptr<std::queue<std::string>> msgs(new std::queue<std::string>());
                std::thread dispacther(loop_for_client, socketSrv, connections, msgs);
                if (signal(SIGINT, signals_handle) == SIG_ERR) {
                    std::cerr << "error for setting handle signal" << std::endl;
                } else {
                    /* main loop for "events" */
                    return_code = main_wait_client(socketSrv, addrSrv, connections, msgs);
                }
                std::cout << "Server shutdown ..." << std::endl;
                if(dispacther.joinable())
                    dispacther.join();
            }
        }
        std::cout << "closing socket " << socketSrv << " ... ";
        /* close the socket. */
        if(closesocket(socketSrv) != 0)
            print_error("Error while closing main socket");
        else
            std::cout << "now closed." << std::endl;
        socketSrv = INVALID_SOCKET;
    }
    #if defined(WIN32) || defined (_WIN32)
        WSACleanup();
    #endif
    return return_code;
};

/**
 * Main loop gérant les sockets par la méthode `select` (évite un thread par connection et CPU à 100%)
 */
int main_wait_client(SOCKET const& socketSrv, SockAddress const& addrSrv, const std::shared_ptr<std::list<SOCKET>> &connections, const std::shared_ptr<std::queue<std::string>> &msg)
{
    int return_code = EXIT_SUCCESS;
    /// init select env
    fd_set readfs; //set sockets descriptor(s)
    /// Reception des connections
    std::cout << "waiting clients ..." << std::endl;
    SOCKET max_sd;
    while(!global_exit) {
        FD_ZERO(&readfs); //clean set
        FD_SET(socketSrv, &readfs); //ajout socket srv au set
        max_sd = socketSrv;
        for(const auto& sd : /*std::as_const*/(*connections)) { //cherche pour select
            if(sd != INVALID_SOCKET) //si socket valide
                FD_SET(sd, &readfs); // ajout à liste lecture
            if(sd > max_sd)
                max_sd = sd; // (+) descripteur, besoin pour select
        }
        const int res = select(max_sd+1, &readfs, NULL, NULL, NULL);
        /*//#ifdef errno
        //if(res < 0)
        //#else
        if((res < 0) and (errno != EINTR))
        //#endif // errno
            std::cerr << "select() error" << std::endl;*/
        check_new_clients(socketSrv, readfs, connections);
        check_incoming_msg(readfs, connections, msg);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return return_code;
}

void check_new_clients(SOCKET const& socketSrv, fd_set const& readfs, const std::shared_ptr<std::list<SOCKET>> &connections)
{
    if(FD_ISSET(socketSrv, &readfs)) { //si event sur socket srv -> connexion entrante
        SockAddress cliAddress;
        socklen_t addrlen = sizeof(cliAddress.addr_in);
        SOCKET new_cli = accept(socketSrv, &(cliAddress.addr), &addrlen);
        if(new_cli == INVALID_SOCKET) {
            print_net_error("Error accepting connection");
            //exit(EXIT_FAILURE);
        } else {
            std::cout << "Nouvelle connexion " << new_cli << " de " << inet_ntoa(cliAddress.addr_in.sin_addr) << " sur " << ntohs(cliAddress.addr_in.sin_port) << std::endl;
            if(send(new_cli, welcome_msg.c_str(), welcome_msg.length(), 0) != 0) {
                print_net_error("Erreur envoie message démarrage");
                shutdown(new_cli, SHUT_RDWR);
                closesocket(new_cli);
            } else
                connections->push_back(new_cli);
        }
    }
}

void check_incoming_msg(fd_set const& readfs, const std::shared_ptr<std::list<SOCKET>> &connections, const std::shared_ptr<std::queue<std::string>> &message)
{
    /*byte*/char buffer[BUFFER_SIZE] = {0};
    for(const auto& con : /*std::as_const*/(*connections))
        if(FD_ISSET(con, &readfs)) {
            int resval = read(con, buffer, BUFFER_SIZE);
            if(resval == 0) { //si fermée ou ... autre
                SockAddress address;
                socklen_t addrlen = sizeof(address.addr_in);
                getpeername(con, &(address.addr), &addrlen);
                std::cout << "Déconnexion du client " << con << " de " << inet_ntoa(address.addr_in.sin_addr) << ":" << ntohs(address.addr_in.sin_port) << std::endl;
                connections->remove(con);
                shutdown(con, SHUT_RDWR); //TODO: check return
                closesocket(con); //TODO: check return
            } else {
                buffer[resval] = '\0'; //sécurité (obligatoire pour chaines), terminé les données par NULL
                message->emplace(buffer);
                std::cout << "new message queued" << std::endl;
            }
        }
}
