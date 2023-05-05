#include<stdlib.h>
#include<stdio.h>
#include <stdbool.h>
#include<string.h>
#include "../lib/struct.h"
#include "../lib/ls.h"

/**
 * Affiche le chemin absolu du noeud courant depuis sa racine
*/
void pwd(){
    if(courant != courant->racine){ 

        noeud *tmp = courant;
        char *chemin = malloc(sizeof(char) * (strlen(tmp->nom) + 2)); // on alloue une chaine de caractère qui contiendra le nom du noeud courant précédé d'un '/' et suivi d'un '\0'
        if(chemin == NULL){
            perror("Problème d'allocation.");
            exit(EXIT_FAILURE);
        }
        int taille_chemin = strlen(tmp->nom) + 2;
        chemin[0] = '/';

        for(int i = 0; i < strlen(tmp->nom); ++i){
            chemin[i+1] = tmp->nom[i];
        }

        chemin[strlen(tmp->nom) + 1] = '\0';

        while(tmp->pere != courant->racine){ 
            tmp = tmp->pere;
            chemin = realloc(chemin, taille_chemin + strlen(tmp->nom) + 1); // on réalloue la chaine de caractère en lui ajoutant la taille du nom du nouveau noeud tmp +1 pour le '/'
            if(chemin == NULL){
                perror("Problème d'allocation.");
                exit(EXIT_FAILURE);
            }
            memmove(chemin + strlen(tmp->nom) + 1, chemin, taille_chemin); // on décale l'ancien chemin pour pouvoir ensuite ajouter le nom du noeud tmp au début
            chemin[0] = '/';
            for(int i = 0; i < strlen(tmp->nom); ++i){
                chemin[i+1] = tmp->nom[i];
            }
            taille_chemin += strlen(tmp->nom) + 1;
        }
        // on affiche le chemin
        printf("%s\n", chemin);
        free(chemin);
    }
    else{
        printf("/\n");
    }
}