#include "../lib/struct.h"
#include "../lib/chemin.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * Actualise le noeud courant par le noeud au bout du chemin 'path' en partant du noeud courant 
 * actuel, s'il existe et que c'est un dossier.
 * 
 * @param path chemin vers le noeud souhaité 
 */
void cd(char *path){
    if(path == NULL){
        courant = courant->racine;
    }
    else{
        noeud *n = chemin(courant, path);
        if(n == NULL){
            perror("Le chemin est invalide.");
            exit(EXIT_FAILURE);
        }
        if(!n->est_dossier){
            perror("Le chemin ne désigne pas un dossier.");
            exit(EXIT_FAILURE);
        }
        courant = n;
    }
}