#include<assert.h>
#include<stdlib.h>
#include<stdio.h>
#include <stdbool.h>
#include<string.h>
#include "../lib/struct.h"
#include "../lib/ls.h"

/* Affiche sur le terminal la liste des noms des fils du noeud courant*/
void ls(noeud *n){
    liste_noeud *tmp = n->fils;
    while(tmp != NULL){
        printf("%s ", tmp->no->nom);
        tmp = tmp->succ;
    }
    puts("");
}