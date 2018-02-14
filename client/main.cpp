#include <iostream>
#include <cstdlib>
#include <cstdbool>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
extern "C" {
    #include <unistd.h>
}
#include <arpa/inet.h>
#include "common/sample.hpp"

using namespace std;

int main(const int argc, const char *argv[])
{
    bool connected = true;
    char entry[2048];
    struct sockaddr_in adresseServeur;
    string servaddr;
    string user;

    cout << "NOM D'UTILISATEUR: ";
    cin >> user;

    /* Création d'une socket TCP */
    int socketClient = socket( AF_INET, SOCK_STREAM, 0 );

    cout << "VEUILLEZ TAPER L'IP DU SERVEUR: ";
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

    const char * begin = user.c_str();
    strcat((char *)begin," a dit:");

    while(connected)
    {
        cout << user << ">";

        //begin[0] = '\0'; // initialisation
        // envoi du message
        fgets(entry, 2048, stdin);

        /* Envoi de la requête au serveur */

        int ret = write( socketClient, begin, strlen(begin) );
        if ( ret < 0 ) cout << "ERREUR d'écriture sur la socket" << endl;
        int ret2 = write( socketClient, entry, strlen(entry) );
        if ( ret2 < 0 ) cout << "ERREUR d'écriture sur la socket" << endl;

        if(strcmp(entry,"exit\n") == 0){
            connected = false;
        }
        cout << endl;
    }

    /* Fermeture de la socket */
    close( socketClient );

    return EXIT_SUCCESS;
}
