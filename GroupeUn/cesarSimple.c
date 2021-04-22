#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

int main() {
    char reponse[100000];
    /* int taille; */
    char lettreLue;
    char lettreSuivante3;
    char reponse3[10];
	
    // Affiche les échanges avec le serveur
    //mode_debug(true);

    // Attend après chaque échange l'appui sur entrée
    attente_automatique(false);

    // Commentez ou passez à 'false' les lignes ci-dessus pour en désactiver 
    // les effets.

    if (! connexion()) {
        fprintf (stderr, "Impossible de se connecter à AppoLab!\n");
        return 1;
    }

    envoyer_recevoir("login LANG aqwzsx", reponse);
    /* printf("%s", reponse);  // décommentez pour afficher la réponse du serveur */
    envoyer_recevoir("load cesarSimple", reponse);
    envoyer_recevoir("help", reponse);
    envoyer_recevoir("depart", reponse);

lettreLue=reponse[0];
while (strcmp(reponse, "Félicitations ! Vous avez réussi cet exercice.")!=0){
/* travail sur reponse, lettre +3, renvoi de la lettre, recu de reponse */
   lettreLue = reponse[0];
   if(lettreLue >= 'a' && lettreLue <= 'z'){
        lettreSuivante3 = lettreLue + 3;
        if(lettreSuivante3 > 'z'){
            lettreSuivante3 = lettreSuivante3 - 'z' + 'a' - 1;
        }
    }
    else if(lettreLue >= 'A' && lettreLue <= 'Z'){
        lettreSuivante3 = lettreLue + 3;
        if(lettreSuivante3 > 'Z'){
            lettreSuivante3 = lettreSuivante3 - 'Z' + 'A' - 1;
        }
    }
    else{
        lettreSuivante3 = lettreLue;
    }
reponse3[0]=lettreSuivante3; reponse3[1]='\0';
    envoyer_recevoir(reponse3, reponse);
}


    return 0;
}
