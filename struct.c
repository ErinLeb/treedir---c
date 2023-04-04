#include<stdbool.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include "struct.h"

noeud *creer_racine(){
    noeud * racine = malloc(sizeof(noeud));
    set_nom(racine, "");
    racine->est_dossier = true;
    racine->pere = racine;
    racine->racine = racine;

    return racine;
}

void set_nom(noeud *n, char *str){
    assert(strlen(str) < 100);

    for(int i = 0; i<=strlen(str); ++i){
        n->nom[i] = *(str+i);
    }
}