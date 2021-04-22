#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>




char lettreLue, lettreSuivante3;
char mdecode[100000], reponse[100000], answer[100], hasta[] = "hasta la revolucion";
int taille, key, decal;


int cle(char *reponse){
	int i=1;
	while ((reponse[i] < 'A') || (reponse[i] > 'Z')){
		i++;
	}
	return i;
}


char decalage (char lettreLue, char key){
	 	  
	if(lettreLue >= 'a' && lettreLue <= 'z'){
		lettreSuivante3 = (lettreLue-key-'a'+26)%26+'a';
    }
    else if(lettreLue >= 'A' && lettreLue <= 'Z'){
		lettreSuivante3 = (lettreLue-key-'A'+26)%26+'A';
	}
	else{
		lettreSuivante3 = lettreLue;
	 }
	return lettreSuivante3;
}


	
void decode(char * mdecode, int taille, int key ){
	for (int i=0; i<taille; i++)
		mdecode[i] = decalage(reponse[i],key);
}

void cryp_mot( char * mot, char * mot_code, int key ){
	int taille = strlen(mot);
	for (int i=0; i<taille; i++)
		mot_code[i] = decalage(mot[i],key);	
	
}
int main() {
	
	FILE* fichier = NULL;
	fichier = fopen("planBreponse.txt", "w");
    
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

    envoyer_recevoir("login LANG aqwzsx", reponse);
    
    envoyer_recevoir("load planB", reponse);

    taille=envoyer_recevoir("help", reponse);
	
	key=reponse[0] - 'C';
	//printf("decalage : %d\n",key);
	decode(mdecode,taille,key);
	//printf("%s\n", mdecode);
	
	envoyer_recevoir("start", reponse);
	cryp_mot(hasta,answer,key);
	taille=envoyer_recevoir(answer, reponse);
	//printf("reponse : %s\n",reponse);
	
	
	decal = cle(reponse);
	
	//printf("decal : %d\n char : %c\n ", decal,reponse[decal]);
	key=reponse[decal] - 'C';
	
	decode(mdecode,taille,key);
	if (fichier != NULL){
		fprintf(fichier, "%s",mdecode);
        fclose(fichier);
    }
	printf("%s", mdecode);
	cryp_mot("hasta la victoria siempre",answer,key);
	taille=envoyer_recevoir(answer, reponse);
    return 0;


}
