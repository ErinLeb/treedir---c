#include<assert.h>
 #include "../lib/struct.h"
 #include "../lib/touch.h"

/**
 * Crée un fichier fils au noeud courant , portant le nom @code nom
*/
void touch(char *nom){
  assert(courant->est_dossier);
  assert(is_correct(nom));
  assert(!has_son(courant, nom));

  noeud *fils = creer_noeud(false, nom, courant->racine, courant);
  courant->fils = pushTail(courant->fils, fils);
}