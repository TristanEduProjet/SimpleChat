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
    string servaddr;

    /* Création d'une socket TCP */
    int socketClient = socket( AF_INET, SOCK_STREAM, 0 );

    cout << "VEUILLEZ TAPER L'IP DU SERVEUR:" << endl;
    cin >> servaddr;
    /* Configuration de l'adresse du serveur */
    bzero( &adresseServeur, sizeof(adresseServeur) );
    adresseServeur.sin_family = AF_INET;
    adresseServeur.sin_port = htons( 5669 ); // <-- port
    adresseServeur.sin_addr.s_addr = inet_addr( servaddr.c_str() );

    /* Tentative de connexion au serveur */
    if ( connect( socketClient, (struct sockaddr *)&adresseServeur, sizeof(adresseServeur)) == -1 )
        cout << "Impossible d'établir une connexion" << endl;
    cout << "Connexion établie" << endl;

    while(connected)
    {
        cout << ">";
        cin >> entry;

        // envoi du message
        //fgets(entry, 2048, stdin);
        /* Envoi de la requête au serveur */
        int ret = write( socketClient, entry.c_str(), strlen(entry.c_str()) );
        if ( ret < 0 ) cout << "ERREUR d'écriture sur la socket" << endl;

        if(entry == "exit"){
            connected = false;
        }
        cout << endl;
    }

    /* Fermeture de la socket */
    close( socketClient );

    return EXIT_SUCCESS;
}
