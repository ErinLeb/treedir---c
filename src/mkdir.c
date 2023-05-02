#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include <stdio.h>
#include "../lib/struct.h"
#include "../lib/mkdir.h"

/**
 * Crée un fils dossier à curr, portant le nom en paramètre
 * @param nom nom du dossier créé au noeud courant
*/
void mkdir(char *nom){
    assert(courant->est_dossier);
    assert(is_correct(nom));
    assert(!has_son(courant, nom));

    noeud *fils = creer_noeud(true, nom, courant->racine, courant);
    courant->fils = pushTail(courant->fils, fils);
}