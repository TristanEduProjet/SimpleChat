#include <iostream>
#include <cstdlib>
#include <cstdbool>
#include "common/sample.hpp"

using namespace std;

int main(const int argc, const char *argv[])
{
    bool connected = true;
    string entry;
    struct sockaddr_in adresseServeur;

    /* Création d'une socket TCP */
    int socketClient = socket( AF_INET, SOCK_STREAM, 0 );

    /* Configuration de l'adresse du serveur */
    bzero( &adresseServeur, sizeof(adresseServeur) );
    adresseServeur.sin_family = AF_INET;
    adresseServeur.sin_port = htons( 5669 ); // <-- port
    adresseServeur.sin_addr.s_addr = inet_addr( "172.22.17.1" );

    /* Tentative de connexion au serveur */
    if ( connect( socketClient, (struct sockaddr *)&adresseServeur, sizeof(adresseServeur)) == -1 )
        perror("Impossible d'établir une connexion\n");
    printf("Connexion établie\n");

    while(connected)
    {
        cout << ">";
        cin >> entry;
        if(entry == "exit"){
            connected = false;
        }
        cout << endl;
    }

    /* Fermeture de la socket */
    close( socketClient );

    return EXIT_SUCCESS;
}
