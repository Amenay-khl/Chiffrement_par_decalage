#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

int main() {
    char reponse[100000];
    int taille;

    // Affiche les échanges avec le serveur
    mode_debug(false);

    // Attend après chaque échange l'appui sur entrée
    attente_automatique(false);

    // Commentez ou passez à 'false' les lignes ci-dessus pour en désactiver 
    // les effets.

    if (! connexion()) {
        fprintf (stderr, "Impossible de se connecter à AppoLab!\n");
        return 1;
    }

    envoyer_recevoir("login DUPREY 11711718", reponse);
    /* printf("%s", reponse);  // décommentez pour afficher la réponse du serveur */
    envoyer_recevoir("load hello", reponse);
    envoyer_recevoir("help", reponse);
    envoyer_recevoir("depart", reponse);

 

    // Bonne réponse à décommenter
     taille = envoyer_recevoir("Hello world!", reponse);

    // Il est possible de travailler sur la réponse du serveur, par exemple
    // ici on passe tout en majuscules.
    for (int i=0; i<taille; i++)
        reponse[i] = toupper(reponse[i]);
    printf("%s", reponse);

    return 0;
}
