#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

char lettreLue, lettreSuivante3;

void decalage (char* reponse, int i){
	
 	  lettreLue = reponse[i];
 	  if(lettreLue >= 'a' && lettreLue <= 'z'){
 	       lettreSuivante3 = lettreLue - 5;
 	       if(lettreSuivante3 < 'a'){
  	          lettreSuivante3 = lettreSuivante3 - 'a' + 'z' + 1;
	
  	      }
  	  }
  	  else if(lettreLue >= 'A' && lettreLue <= 'Z'){
  	      lettreSuivante3 = lettreLue - 5;
  	      if(lettreSuivante3 < 'A'){
    	        lettreSuivante3 = lettreSuivante3 - 'A' + 'Z' + 1;
    	    }
   	 }
   	 else{
   	     lettreSuivante3 = lettreLue;
   	 }
	printf("%c", lettreSuivante3);
	}



int main() {
    char reponse[100000];



    // Affiche les échanges avec le serveur
    mode_debug(true);

    // Attend après chaque échange l'appui sur entrée
    attente_automatique(false);

    // Commentez ou passez à 'false' les lignes ci-dessus pour en désactiver 
    // les effets.

    if (! connexion()) {
        fprintf (stderr, "Impossible de se connecter à AppoLab!\n");
        return 1;
    }

    envoyer_recevoir("login DUPREY 11711718", reponse);
    
    envoyer_recevoir("load projetX", reponse);
    envoyer_recevoir("help", reponse);

	int i=0;
    while (reponse[i]!='\0'){
	decalage(reponse, i);
	i++;
    }
    envoyer_recevoir("depart", reponse);
    envoyer_recevoir("Veni, vidi, vici",reponse);

    return 0;
}
