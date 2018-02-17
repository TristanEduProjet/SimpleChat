# SimpleChat
Client/Serveur de chat

## Résumé du [sujet](https://github.com/gamazeps/esgi/blob/master/project.md)
Projet de C++ consistant en un serveur +client de chat (comme irc, slack , etc...), mais en plus "simple".

Fonctionnalités requises :
  - [x] un serveur central
    - [x] déconnecte un client si la connexion est perdu/fermée (tolérance ~1 min)
    - [x] chaque client peut se connecter (même si autre(s) client(s) déjà connecté(s))
    - [x] communication minimale avec un "canal" général/commun à tous le monde
    - [ ] notifie des (dé)connexions des clients
    - [x] doit être capable d'accepter au minimum 20 connections en parallèle
    - [x] doit pouvoir envoyer les messages aux clients en moins d'une seconde
  - [x] un client
    - [x] permet d'écrire & envoyer messages au serveur
    - [ ] permet de recevoir & afficher des messages du serveur
    - [x] les clients se connectent avec la même commande
    - [ ] si programme interrompu, doit être déconnecté du serveur
    - [ ] informe des (dé)connexions (du serveur/channel)

Contraintes :
  - [x] Les dépendances doivent être explicites et résolue dans la phase d’installation
  - [ ] doit être compilable et lançable sous linux (Ubuntu 16.04 LTS)
  - [ ] doit être testé (coverage de 50% minimum)
  - [ ] doit passer le test de memcheck (valgrind)
  - [x] _doit être versionné sous git_
  - [ ] doit avoir une intégration continue
  - [x] pas de GUI graphique (utilisable en console)

> La contrainte d’ordonnancement des messages est la suivante: si un client U envoie le message `m1` puis le message `m2`, les autres clients doivent les recevoir dans cet ordre. Cependant il n'y a pas de priorité entre les clients.

> Vous devez pouvoir montrer que des clients sur différentes machines peuvent communiquer via ce serveur (machines virtuelles sur la même machine physique autorisées).

Fonctionnalités supplémentaires :
  - [ ] Sauvegarder l'historique des conversations sur le serveur (dans un fichier ou une base de données)
  - [ ] Vérifier que deux clients n'ont pas le même identifiant
  - [x] Gérer les connexion de manière multi-threadé
  - [ ] Permettre aux clients de demander l'historique
  - [ ] Permettre l'envoi de messages personnels (visibles uniquement entre les deux clients concernés)
  - [ ] Permettre la création de canaux de discussions par les clients (channels sur irc/slacks)


## Requirements
Le projet nécessite :
  - lors de la compilation :
      - CMake (3.x)
      - make
      - MinGW sous Windows
      - GCC/CLang/? sous Linux
  - pour le programme :
      - ...

## Build
CMake se charge de tester et gérer les dépendances du projet.  
Les seules commandes sont :

En debug _(par défault)_ :
```bash
cmake -G"<Generator>" -Wdeprecated -Wdev -DCMAKE_BUILD_TYPE=Debug .
cmake --build . [--clean-first] [--target <tgt>]
```

En release :
```bash
cmake -G"<Generator>" -DCMAKE_BUILD_TYPE=Release .
cmake --build . [--clean-first] [--target <tgt>]
```

`<Generator>` correspond suivant le système à :
  - `MinGW Makefiles` sous Windows
  - `Unix Makefiles` sous Linux (sauf si vous voulez compilez les binaires pour windows avec mingw)

`<tgt>` peut-être :
  - `all` (_par défaut si option non utilisée_)
  - `clean`, `help`, `rebuild_cache`, `install`
  - `SChat`, `schatSrv` ou `schatCli`

