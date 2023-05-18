#include "../lib/struct.h"
#include "../lib/touch.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * Crée un fichier fils au noeud courant portant le nom 'nom'
*/
void touch(char *nom){
  if(!is_correct(nom)){
    perror("Nom incorrect.");
    exit(EXIT_FAILURE);
  }
  if(has_son(courant, nom)){
    perror("Le dossier courant possède déjà un fils avec le même nom.");
    exit(EXIT_FAILURE);
  }

  noeud *fils = creer_noeud(false, nom, courant->racine, courant);
  courant->fils = pushTail(courant->fils, fils);
}