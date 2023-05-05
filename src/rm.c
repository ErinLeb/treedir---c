#include<stdlib.h>
#include<stdio.h>
#include "../lib/struct.h"
#include "../lib/rm.h"
#include "../lib/chemin.h"

/**
 * Détruit le noeud et toute sa descendance indiqué par path
 * @param path l'adresse du noeud à supprimer 
*/
void rm(char *path){
    noeud *s = chemin(courant, path);
    if(s == NULL){
        perror("Ce chemin n'est pas valide.");
        exit(EXIT_FAILURE);
    }

    if(est_dans_sous_arbre(s, courant)){
        perror("Le noeud à supprimer ne peut pas être un parent du noeud courant.");
        exit(EXIT_FAILURE);
    }
    
    noeud *pere = s->pere;
    liste_noeud *l = suppr_noeud_liste(s->pere->fils, s);
    pere->fils = l;
    destroy_arbre(s);
}