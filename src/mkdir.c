#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include <stdio.h>
#include<ctype.h>
#include "../lib/mkdir.h"

/*Crée un fils dossier portant le nom en paramètre*/
void mkdir(noeud * curr, char *nom){
    assert(curr->est_dossier);
    assert(is_correct(nom));
    assert(!has_son(curr, nom));

    noeud *fils = creer_noeud(true, nom, curr->racine, curr);
    curr->fils = pushTail(curr->fils, fils);
}

/*Vérifie que la chaine de caractère ne comporte que des caractères alhpa-numériques*/
bool is_correct( char *nom){
    assert(strlen(nom) > 0);
    assert(strlen(nom) < 100 );

    while(*nom != '\0'){
        if(!isalnum(*nom)){
            puts("not alhpa-numeric");
            return false;
        }
        if (isspace(*nom)){
            puts("is space");
            return false;
        }
        nom++;
    }
    return true;
}