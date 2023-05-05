#include "../lib/struct.h"
#include "../lib/mv.h"
#include "../lib/chemin.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void mv(char *chem1, char *chem2){
    noeud *src = chemin(courant, chem1);
    if(src == NULL){
        perror("Le chemin 1 n'est pas valide.");
        exit(EXIT_FAILURE);
    }

    noeud *dst = chemin(courant, chem2);
    char *nom;
    bool alloc = false;
    
    if(dst == NULL){
        dst = chemin_precedent(courant, chem2);
        if(dst == NULL){
            perror("Le chemin 2 n'est pas valide.");
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
    
    if(est_dans_sous_arbre(src, dst)){
        perror("Le dossier de destination est dans le sous arbre du dossier source.");
        exit(EXIT_FAILURE);
    }

    if(has_son(dst, nom)){
        perror("Le dossier de destination contient déjà un noeud de ce nom.");
        exit(EXIT_FAILURE);
    }

    noeud *pere = src->pere;
    liste_noeud *l = suppr_noeud_liste(src->pere->fils, src);
    pere->fils = l;
    src->pere = dst;
    dst->fils = pushTail(dst->fils, src);
    set_nom(src, nom);
    if(alloc){
        free(nom);
    }
}