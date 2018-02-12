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
    adresseRecepteur.sin_addr.s_addr = inet_addr( real_ip().c_str() );

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
      cout << "ERREUR d'écriture sur la socket" << endl;
    cout << "Requête envoyée :" << endl << requete << endl;

    bool connected = true;
    while(connected)
    {
       // Réceptionne et affiche la réponse du serveur
       bzero(reponse, 2048); // Nettoyage du tampon de réception
       printf("Attente de réponse...\n");
       int n2 = read(accepter,reponse,2048);
       if ( n2 < 0 ) cout << "ERREUR de lecture depuis la socket" << endl;
       printf( "Reçu %do : \n%s\n", n2, reponse );
       if(!n2)connected=false;
    }

    // Fermeture de la socket //
    close( socketRecepteur );

    return EXIT_SUCCESS;
}
