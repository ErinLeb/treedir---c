#include "../lib/struct.h"
#include "../lib/chemin.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * renvoie le noeud, s'il existe et que c'est un dossier, au bout du chemin @code path en partant du noeud @code courant 
 * @param courant noeud de départ
 * @param path chemin vers le noeud souhaité
 * @return un pointeur vers le noeud, s'il existe et que c'est un dossier, au bout du chemin @code path en partant du noeud @code courant 
 */
noeud *cd(noeud *courant, char *path){
    if(strlen(path) == 0){
        return courant->racine;
    }
    noeud *n = chemin(courant,path);
    if(n == NULL){
        perror("Le chemin est invalide.");
        exit(1);
    }
    if(!n->est_dossier){
        perror("Le chemin ne désigne pas un dossier.");
        exit(1);
    }
    return n;
}