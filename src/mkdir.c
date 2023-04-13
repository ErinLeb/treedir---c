#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include <stdio.h>
#include "../lib/struct.h"
#include "../lib/mkdir.h"

/*Crée un fils dossier portant le nom en paramètre*/
void mkdir(noeud * curr, char *nom){
    assert(curr->est_dossier);
    assert(is_correct(nom));
    assert(!has_son(curr, nom));

    noeud *fils = creer_noeud(true, nom, curr->racine, curr);
    curr->fils = pushTail(curr->fils, fils);
}
