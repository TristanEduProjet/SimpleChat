#include <iostream>
#include <cstdlib>
#include <cstdbool>
#include <stdlib.h>
#include <curses.h>
#include <thread>
#include "common/sample.hpp"

using namespace std;

bool connected = true;
string servaddr;
string lines[12];

void ReadData()
{
    struct sockaddr_in adresseRecepteur, adresseEmetteur;
    char reponse[2048];

    // Création d'une socket TCP //
    int socketRecepteur = socket( AF_INET, SOCK_STREAM, 0 );

    // Configuration de l'adresse du serveur //
    bzero( &adresseRecepteur, sizeof(adresseRecepteur) );
    adresseRecepteur.sin_family = AF_INET;
    adresseRecepteur.sin_port = htons( 5669 ); // <-- port
    adresseRecepteur.sin_addr.s_addr = inet_addr( servaddr.c_str() );

    // Attachement de l'adresse à la socket du recepteur //
    bind(socketRecepteur,(struct sockaddr*)&adresseRecepteur,sizeof(adresseRecepteur));

    int listener = listen(socketRecepteur,1);

    socklen_t addrlen = sizeof(adresseEmetteur);
    // Tentative de connexion au serveur //
    int accepter = accept(socketRecepteur,(struct sockaddr*)&adresseEmetteur,&addrlen);

    // Envoi de la requête au serveur //
    char *requete = "PREMIER MESSAGE ENVOYE PAR LE SERVEUR";
    int n = write(accepter,requete,strlen(requete));

    while(connected)
    {
       // Réceptionne et affiche la réponse du serveur
       bzero(reponse, 2048); // Nettoyage du tampon de réception
       int n2 = read(accepter,reponse,2048);
       for(int a=0;a<10;a++){
           lines[a] = lines[a+1];
       }
       lines[9] = reponse;
       if(!n2)connected=false;
    }


}

int main(const int argc, const char *argv[])
{
    char entry[2048];
    struct sockaddr_in adresseServeur;
    string user;
    char begin[256];
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
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_RED);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_WHITE);
    init_pair(4, COLOR_BLACK, COLOR_GREEN);

    attron(COLOR_PAIR(4));

    mvaddstr(1, 1, "SimpleChat Client v1.0 - Groupe 6 - Nicolas Baptista / Tristan Chuine / Pierre-Henry Langlois");

    for(int a=2,b=0;a<12;a++,b++){
        lines[b] = "";
    }
    attron(COLOR_PAIR(2));
    mvhline(12, 1, '-', 70);
    attron(COLOR_PAIR(1));
    mvaddnstr(13,1,user.c_str(),10);

    refresh();

    std::thread(ReadData);
    while(connected)
    {
        attron(COLOR_PAIR(2));
        for(int a=2,b=0;a<12;a++,b++){
            //char ligne[256];
            //sprintf(ligne, "%s", lines[b]);
            mvaddstr(a,1,lines[b].c_str());
        }

        attron(COLOR_PAIR(3));
        mvhline(13, 11, ' ', 60); // On clean
        move(13,11); // Curseur pour l'écriture
        // ecriture du message
        getstr(entry);
        /*for(int a=0;a<10;a++){
            lines[a] = lines[a+1];
        }
        lines[9] = begin;
        lines[9].append(entry);*/

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
