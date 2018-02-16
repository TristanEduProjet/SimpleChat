#include <iostream>
#include <cstdlib>
#include <cstdbool>
#include <cstring>
#include <thread>
#include <list>
#include <atomic>
#include <csignal>
#include "common/network.hpp"
#include "common/data.hpp"
#include "common/utils.hpp"
#include <unistd.h>

std::atomic<bool> global_exit(false);
std::list<std::thread> connections;
//msgs

const static std::string welcome = "Bienvenu to the <servername> server.";
void loop_for_client(const SOCKET socketCli, const SockAddress addrCli) {
    const std::thread::id this_id = std::this_thread::get_id();
    std::cout << std::this_thread::get_id() << " has socket " << socketCli << std::endl;
    // Envoi de la requête au serveur //
    /*int n = write(socketCli, welcome.c_str(), welcome.length());
    if(n < 0)
       std::cerr << "ERREUR d'écriture sur la socket" << std::endl;
    std::cout << "Requête envoyée : " << welcome << std::endl;

    bool connected = true;
    char reponse[2048];
    int n2;
    while(connected) {
        // Réceptionne et affiche la réponse du serveur
        memset(reponse, 0x0, 2048); // Nettoyage du tampon de réception
        std::cout << "Attente de réponse ..." << std::endl;
        n2 = read(socketCli, reponse, 2048);
        if(n2 < 0)
            std::cerr << "ERREUR de lecture depuis la socket" << std::endl;
        std::cout << "Reçu " << n2 << " oct : " << reponse << std::endl;
        if(!n2)
            connected = false;
    }*/
    //shutdown(socketCli, 0);
    closesocket(socketCli);
    std::cout << "Fin du thread " << std::this_thread::get_id() << std::endl;
}

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
                ///err = clients(socketSrv);
                std::cout << "server listening on port " << PORT << " ..." << std::endl;
                std::cout << "wating clients ..." << std::endl;
                SockAddress adresseEmetteur;
                socklen_t addrlen = sizeof(adresseEmetteur.addr);
                // Tentative de connexion au serveur //
                while(!global_exit) {
                    SOCKET socketCli = accept(socketSrv, &(adresseEmetteur.addr), &addrlen);
                    if(socketCli == INVALID_SOCKET) {
                        print_net_error("Error accepting connection");
                        //return_code = EXIT_FAILURE;
                    } else {
                        std::cout << "Connexion établie " << socketCli << std::endl;
                        connections.push_back(std::thread(loop_for_client, socketCli, adresseEmetteur));
                    }
                }
                std::cout << "Server shutdown ..." << std::endl;
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
}
