#include "../lib/struct.h"
#include "../lib/cp.h"
#include "../lib/chemin.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/**
 * Crée une copie du noeud situé au bout du chemin @code chem1 et la déplace dans le dossier situé au bout du chemin @code chem2 en partant du noeud @code courant
 * @param chem1 chemin vers le noeud à copier
 * @param chem2 chemin vers le dossier de destination
 */
void cp(char *chem1, char *chem2){
    noeud *src = chemin(courant, chem1);
    if(src == NULL){
        perror("Le chemin 1 n'existe pas.");
        exit(EXIT_FAILURE);
    }

    noeud *dst = chemin(courant, chem2);
    char *nom;
    bool alloc = false;
    if(dst == NULL){
        dst = chemin_precedent(courant, chem2);
        if(dst == NULL){
            perror("Le chemin 2 n'existe pas.");
            exit(EXIT_FAILURE);
        }
        nom = get_last_string(chem2);
        alloc = true;
    }
    else{
        nom = src->nom;
    }
    
    if(!dst->est_dossier){
        perror("Le chemin 2 ne désigne pas un dossier");
        exit(EXIT_FAILURE);
    }
    
    if(est_dans_sous_arbre(src,dst)){
        perror("Le dossier de destination est dans le sous arbre du dossier source.");
        exit(EXIT_FAILURE);
    }

    if(has_son(dst,nom)){
        perror("Le dossier de destination contient déjà un noeud de ce nom.");
        exit(EXIT_FAILURE);
    }

    noeud *c = copie(src);
    c->pere = dst;
    pushTail(dst->fils,c);
    set_nom(c,nom);
    if(alloc){
        free(nom);
    }
}

