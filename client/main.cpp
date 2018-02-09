#include <iostream>
#include <cstdlib>
#include <cstdbool>
#include <stdlib.h>
#include <curses.h>
#include "common/sample.hpp"

using namespace std;

int main(const int argc, const char *argv[])
{
    bool connected = true;
    char entry[2048];
    struct sockaddr_in adresseServeur;
    string servaddr;
    string user;
    char begin[256];
    string lines[9];
    WINDOW * mainwin;

    cout << "NOM D'UTILISATEUR:" << endl;
    cin >> user;

    sprintf(begin,"%s",user.c_str());
    strcat((char *)begin," a dit:");

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

    /*  Init ncurses  */
    if ( (mainwin = initscr()) == NULL ) {
        cout << "Erreur initialisation ncurses" << endl;
        exit(EXIT_FAILURE);
    }

    mvaddstr(1, 1, "SimpleChat Client v1.0 - Groupe 6 - Nicolas Baptista / Tristan Chuine / Pierre-Henry Langlois");
    for(int a=2,b=0;a<12;a++,b++){
        char ligne[256];
        sprintf(ligne, "message ligne %d",a);
        //lines[b] = sprintf(ligne, "message ligne %d",a);
        mvaddstr(a,1,ligne);
    }
    mvaddstr(12,1,"===========================================================");


    refresh();

    while(connected)
    {
        mvaddstr(13,11,"                                                                                      "); // On clean
        mvaddnstr(13,1,user.c_str(),10);
        move(13,11); // Curseur pour l'écriture
        // ecriture du message
        getstr(entry);
        /*for(int a=2,b=0;a<11;a++,b++){
            lines[b] = lines[b+1];
            char ligne[256];
            sprintf(ligne, "%s",lines[b]);
            mvaddstr(a,1,ligne);
        }
        char newline[256];
        sprintf(newline, "%s%s",begin,entry);
        mvaddstr(12,1,newline);*/
        // Envoi de la requête au serveur

        int ret = write( socketClient, begin, strlen(begin) );
        if ( ret < 0 )connected = false;
        int ret2 = write( socketClient, entry, strlen(entry) );
        if ( ret2 < 0 )connected = false;

        if(strcmp(entry,"exit\n") == 0){
            connected = false;
        }
    }


    /* Fermeture de la socket */
    close( socketClient );

    /* Fermeture NCurses */
    delwin(mainwin);
    endwin();
    refresh();

    return EXIT_SUCCESS;
}
