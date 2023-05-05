#include<stdlib.h>
#include<string.h>
#include <stdio.h>
#include "../lib/struct.h"
#include "../lib/mkdir.h"

/**
 * Crée un fils dossier à curr, portant le nom en paramètre
 * @param nom nom du dossier créé au noeud courant
*/
void mkdir(char *nom){
    if(!is_correct(nom)){
        perror("Nom incorrect.");
        exit(EXIT_FAILURE);
    }
    if(has_son(courant, nom)){
        perror("Le dossier courant possède déjà un fils avec le même nom.");
        exit(EXIT_FAILURE);
    }

    noeud *fils = creer_noeud(true, nom, courant->racine, courant);
    courant->fils = pushTail(courant->fils, fils);
}