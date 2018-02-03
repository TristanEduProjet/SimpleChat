#include <iostream>
#include <cstdlib>
#include <cstdbool>
#include "common/sample.hpp"

using namespace std;

int main(const int argc, const char *argv[])
{
    struct sockaddr_in adresseRecepteur, adresseEmetteur;
    char reponse[2048];

    // Création d'une socket TCP //
    int socketRecepteur = socket( AF_INET, SOCK_STREAM, 0 );

    // Configuration de l'adresse du serveur //
    bzero( &adresseRecepteur, sizeof(adresseRecepteur) );
    adresseRecepteur.sin_family = AF_INET;
    adresseRecepteur.sin_port = htons( 5669 ); // <-- port
    adresseRecepteur.sin_addr.s_addr = inet_addr( "172.22.17.1" );

    // Attachement de l'adresse à la socket du recepteur //
    bind(socketRecepteur,(struct sockaddr*)&adresseRecepteur,sizeof(adresseRecepteur));

    int listener = listen(socketRecepteur,1);
    printf("Connexion établie %d\n",listener);

    socklen_t addrlen = sizeof(adresseEmetteur);
    // Tentative de connexion au serveur //
    int accepter = accept(socketRecepteur,(struct sockaddr*)&adresseEmetteur,&addrlen);
    printf("Connexion établie %d\n",accepter);

    // Envoi de la requête au serveur //
    char *requete = "PREMIER MESSAGE ENVOYE PAR LE SERVEUR";
    int n = write(accepter,requete,strlen(requete));
    if ( n < 0 )
      perror("ERREUR d'écriture sur la socket\n");
    printf("Requête envoyée :\n%s\n",requete);

    // Fermeture de la socket //
    close( socketRecepteur );

    return EXIT_SUCCESS;
}
