#include <iostream>
#include <cstdlib>
#include <cstdbool>
#include <cstring>
#include <list>
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
extern "C" {
    #include <unistd.h>
}
#include "common/sample.hpp"

const static char requete[] = "PREMIER MESSAGE ENVOYE PAR LE SERVEUR";
void loop_for_client(const int socketCli) {
    const std::thread::id this_id = std::this_thread::get_id();
    std::cout << this_id << " has socket " << socketCli << std::endl;
    // Envoi de la requête au serveur //
    int n = write(socketCli, requete, strlen(requete));
    if(n < 0)
       std::cerr << "ERREUR d'écriture sur la socket" << std::endl;
    std::cout << "Requête envoyée : " << requete << std::endl;

    bool connected = true;
    char reponse[2048];
    int n2;
    while(connected) {
        // Réceptionne et affiche la réponse du serveur
        bzero(reponse, 2048); // Nettoyage du tampon de réception
        std::cout << "Attente de réponse ..." << std::endl;
        n2 = read(socketCli, reponse, 2048);
        if(n2 < 0)
            std::cerr << "ERREUR de lecture depuis la socket" << std::endl;
        std::cout << "Reçu " << n2 << " oct : " << reponse << std::endl;
        if(!n2)
            connected = false;
    }
    std::cout << "Fin du thread " << this_id << std::endl;
}

int main(const int argc, const char *argv[])
{
    struct sockaddr_in adresseRecepteur;

    // Création d'une socket TCP //
    int socketRecepteur = socket( AF_INET, SOCK_STREAM, 0 );

    // Configuration de l'adresse du serveur //
    bzero(&adresseRecepteur, sizeof(adresseRecepteur));
    adresseRecepteur.sin_family = AF_INET;
    adresseRecepteur.sin_port = htons( 5669 ); // <-- port
    adresseRecepteur.sin_addr.s_addr = INADDR_ANY ;//inet_addr( real_ip().c_str() );

    // Attachement de l'adresse à la socket du recepteur //
    bind(socketRecepteur, (struct sockaddr*)&adresseRecepteur, sizeof(adresseRecepteur));

    int listener = listen(socketRecepteur, 1);
    std::cout << "socket d'écoute " << listener << std::endl;

    struct sockaddr_in adresseEmetteur;
    std::list<std::thread> connections;
    // Tentative de connexion au serveur //
    while(true) { ///TODO: boolean for proper exit
        socklen_t addrlen = sizeof(adresseEmetteur);
        int accepter = accept(socketRecepteur, (struct sockaddr*)&adresseEmetteur, &addrlen);
        std::cout << "Connexion établie " << accepter << std::endl;
        connections.push_back(std::thread(loop_for_client, accepter));
    }

    // Fermeture de la socket //
    close( socketRecepteur );

    return EXIT_SUCCESS;
}
