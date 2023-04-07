#include<assert.h>
#include<stdlib.h>
#include<stdio.h>
#include <stdbool.h>
#include<string.h>
#include "struct.h"
#include "ls.h"

void pwd(noeud *n){

    if(n != n->racine){ 

        noeud *courant = n;
        char *chemin = malloc(sizeof(char) * (strlen(courant->nom) + 2)); // on alloue une chaine de caractère qui contiendra le nom du noeud n précédé d'un '/' et suivi d'un '\0'
        assert(chemin != NULL);
        int taille_chemin = strlen(courant->nom) + 2;
        chemin[0] = '/';

        for(int i = 0; i < strlen(courant->nom); ++i){
            chemin[i+1] = courant->nom[i];
        }

        chemin[strlen(courant->nom) + 1] = '\0';

        while(courant->pere != n->racine){ 
            courant = courant->pere;
            chemin = realloc(chemin, taille_chemin + strlen(courant->nom) + 1); // on réalloue la chaine de caractère en lui ajoutant la taille du nom du nouveau noeud courant +1 pour le '/'
            assert(chemin != NULL);
            memmove(chemin + strlen(courant->nom) + 1, chemin, taille_chemin); // on décale l'ancien chemin pour pouvoir ensuite ajouter le nom du noeud courant au début
            chemin[0] = '/';
            for(int i = 0; i < strlen(courant->nom); ++i){
                chemin[i+1] = courant->nom[i];
            }
            taille_chemin += strlen(courant->nom) + 1;
        }
        // on affiche le chemin
        printf("%s\n", chemin);
        free(chemin);
    }
    else{
        printf("/\n");
    }
}