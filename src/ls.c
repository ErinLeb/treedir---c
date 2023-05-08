#include "../lib/struct.h"
#include "../lib/ls.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/**
 * Affiche la liste des noms des fils du noeud courant
*/
void ls(){
    liste_noeud *tmp = courant->fils;
    while(tmp != NULL){
        printf("%s ", tmp->no->nom);
        tmp = tmp->succ;
    }
    puts("");
}