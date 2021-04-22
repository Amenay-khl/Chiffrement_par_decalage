#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>


int cherche_indice(char *Seq, char c, int longueurSeq) {	 //retourne l'indice du caractère dans la séquence, -1 s'il n'y est pas
	for (int i = 0; i < longueurSeq; i++) {		 
		if (c == Seq[i]) {
			return i;
		}
	}
	return -1;
}


void deplace_fin(char *Seq, int indice, int longueurSeq) {	
	char temp = Seq[indice];							
	for (int i = indice; i < longueurSeq; i++) {
		Seq[i] = Seq[i+1];
	}
	Seq[longueurSeq - 1] = temp;
}


void crypte(char *chaine_e,char *chaine_s ){
	char Seq[1000]; 
    char c;
    int i=0, longueurSeq=0,indice;
    while(i<strlen(chaine_e)){
        c=chaine_e[i];
		indice = cherche_indice(Seq, c, longueurSeq);
        if(indice == -1){
            Seq[longueurSeq]=c; 
            chaine_s[i]=c;
			longueurSeq++;
        }
        else{
            if(indice == 0){
				chaine_s[i] = Seq[longueurSeq-1]; 	
				deplace_fin(Seq, indice, longueurSeq);
			} 
			else{ 									
				chaine_s[i] = Seq[indice-1];
				deplace_fin(Seq, indice, longueurSeq);				
			}   
        }
        i++;
    }   
}


void decrypte(char *chaine_e2,char *chaine_s2){	
	char Seq2[1000]; 
    char c;
    int i=0, longueurSeq=0,indice;
    while(i<strlen(chaine_e2)){
        c=chaine_e2[i];
		indice = cherche_indice(Seq2, c, longueurSeq);
        if(indice == -1){
            Seq2[longueurSeq]=c; 
            chaine_s2[i]=c;
			longueurSeq++;
        }
        else{
            if(indice == longueurSeq-1){
				chaine_s2[i] = Seq2[0]; 	
				deplace_fin(Seq2, 0, longueurSeq);
			} 
			else{ 									
				chaine_s2[i] = Seq2[indice+1];
				deplace_fin(Seq2, indice+1, longueurSeq);				
			}   
        }
		chaine_s2[i+1] ='\0';
        i++;	
    }
}






int main() {
	char chaine_e[100000], chaine_e2[100000], car;
	char reponse[100000], chaine_s[100000]="",chaine_s2[100000]="";
	int k=0; //compteur pour le traitement des fichiers
	int compteurLigne=0, taille;
	
	FILE* fichier = NULL, *f2 = NULL, *f3 = NULL ;
	fichier = fopen("planBreponse.txt", "r");
	f2 = fopen("reponseCrypte.txt", "w+");
	f3 = fopen("reponseCrypteFinal.txt", "w+");
	
	if (fichier != NULL){  // ecrit le texte réponse de planB dans le tableau de caratère chaine_e
		fscanf(fichier,"%c",&car);
		chaine_e[k]=car;
		while(!feof(fichier)){
			fscanf(fichier,"%c",&car);
			k++;
			chaine_e[k]=car;
		}
		chaine_e[k]='\n';
		fclose(fichier);	
    }
    
    // Affiche les Ã©changes avec le serveur
   // mode_debug(true);

    // Attend aprÃ¨s chaque Ã©change l'appui sur entrÃ©e
    attente_automatique(false);

    // Commentez ou passez Ã  'false' les lignes ci-dessus pour en dÃ©sactiver 
    // les effets.

    if (! connexion()) {
        fprintf (stderr, "Impossible de se connecter Ã  AppoLab!\n");
        return 1;
    }

    envoyer_recevoir("login LANG aqwzsx", reponse);
    envoyer_recevoir("load crypteSeq", reponse);
    envoyer_recevoir("start", reponse);
    crypte(chaine_e,chaine_s);
    envoyer_recevoir(chaine_s, reponse);
	
	
	if (f2 != NULL){  
		fprintf(f2, "%s",reponse); // ecrit la réponse dans le fichier reponseCrypte.txt
		rewind(f2);
		fscanf(f2,"%c",&car);
		while(!feof(f2)){
			if(car == '\n'){
				compteurLigne ++;
			}
			if (compteurLigne >= 2){	//ignore les deux premières lignes de la réponse qui ne font pas parti du message à décrypter
				if (!((compteurLigne == 2) && (car == '\n'))){
					fprintf(f3, "%c",car); // écrit la réponse modifié dans le fichier reponseCrypteFinal.txt
				}	
			}
			fscanf(f2,"%c",&car);
		}
		fclose(f2);
    }
	
	
	rewind(f3);
	k=0;
	if (f3 != NULL){ // stocke le message à décrypter dans chaine_e2
		fscanf(f3,"%c",&car);
		chaine_e2[k]=car;
		while(!feof(f3)){
			fscanf(f3,"%c",&car);
			k++;
			chaine_e2[k]=car;
		}
		chaine_e2[k]='\n';
		fclose(f3);	
    }
    decrypte(chaine_e2,chaine_s2);
    envoyer_recevoir(chaine_s2, reponse);

    return 0;
}
