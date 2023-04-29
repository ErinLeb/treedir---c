#include<stdlib.h>
#include<stdio.h>
#include "../lib/struct.h"
#include "../lib/rm.h"
#include "../lib/chemin.h"

/**
 * Détruit le noeud et toute sa descendance indiqué par path
 * @param n noeud courant
 * @param path l'adresse du noeud à supprimer 
*/
void rm(noeud *n, char *path){
    noeud *s = chemin(n, path);
    if(s == NULL){
        perror("Ce chemin n'est pas valide.");
        exit(1);
    }

    if(est_dans_sous_arbre(s, n)){
        perror("Le noeud à supprimer ne peut pas être un parent du noeud courant.");
        exit(1);
    }
    
    noeud *pere = s->pere;
    liste_noeud *l = suppr_noeud_liste(s->pere->fils, s);
    pere->fils = l;
    destroy_arbre(s);
}