#include<stdbool.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<stdio.h>
#include<ctype.h>
#include "../lib/struct.h"

/**
 * Modifie le nom du noeud donné en paramètre
 * @param n noeud dont on veut modifier le nom
 * @param str nouveau nom du noeud 
 */
void set_nom(noeud *n, const char *str){
    assert(strlen(str) < 100);

    for(int i = 0; i<=strlen(str); ++i){
        n->nom[i] = *(str+i);
    }
}

/**
 * Renvoie le noeud à l'indice i de la liste de noeuds
 * @param l liste de noeuds
 * @param i indice du noeud souhaité
 * @return le noeud à l'indice i de la liste 
 */
noeud *get(liste_noeud *l, int i){
    assert(i < nombre_liste_noeud(l) && i >= 0);
    liste_noeud *courant = l;
    for(int j = 0; j < i; ++j){
        courant = courant->succ;
    }
    return courant->no;
}

/**
 * Renvoie le fils de n ayant le nom 'nom'
 * @param n noeud parent
 * @param nom nom du fils que l'on cherche
 * @return le noeud fils ayant le nom qu'on cherche
 */
noeud *get_by_name(noeud *n, char* nom){
    if(!has_son(n, nom)){
        return NULL;
    }

    liste_noeud *tmp = n->fils; 
    while(tmp != NULL){
        if(strcmp(tmp->no->nom, nom) == 0){
            return tmp->no;
        }
        tmp = tmp->succ;
    }
    return NULL;
}

/**
 * Vérifie si le noeud a un fils portant le nom que l'on cherche
 * @param n noeud parent
 * @param nom nom du fils 
 * @return true si le noeud parent a un fils avec ce nom, false sinon
*/
bool has_son(noeud *n,  char *nom){
    liste_noeud *enfants = n->fils;
    while(enfants != NULL){
        char *tmp = nom;
        int i = 0;
        while(*tmp != '\0'){
            if(enfants->no->nom[i] == '\0' || *tmp != enfants->no->nom[i]){
                break;
            }
            i++;
            tmp = tmp + 1;
        }
        if(i == strlen(nom)){
            return true;
        }
        enfants = enfants->succ;
    }
    return false;
}

/**
 * Vérifie que la chaine de caractère ne comporte que des caractères alhpa-numériques
 * @param nom chaine que l'on veut vérifier
 * @return true si nom n'est composé que de caractères alpha-numériques, n'est pas vide et fait moins de 100 caractères, false sinon
*/
bool is_correct(char *nom){
    assert(strlen(nom) > 0);
    assert(strlen(nom) < 100 );

    while(*nom != '\0'){
        if(!isalnum(*nom)){
            puts("not alhpa-numeric");
            return false;
        }
        if(isspace(*nom)){
            puts("is space");
            return false;
        }
        nom++;
    }
    return true;
}

/**
 * Renvoie le nombre de noeuds de la liste l
 * @param l liste de noeuds dont on veut connaitre le nombre de noeuds
 * @return le nombre de noeuds de la liste l 
 */
int nombre_liste_noeud(liste_noeud *l){
    if(l != NULL){ 
        if(l->no != NULL){ 
            return 1 + nombre_liste_noeud(l->succ);
        }
    }
    return 0; 
}

/**
 * Initialise le noeud racine 
 * @return un noeud racine
 */
noeud *creer_racine(){
    noeud * racine = malloc(sizeof(noeud));
    set_nom(racine, "");
    racine->est_dossier = true;
    racine->pere = racine;
    racine->racine = racine;
    racine->fils = NULL;

    return racine;
}

/**
 * Initialise un noeud sans enfant
 * @param dossier vrai si le noeud est un dossier, faux sinon
 * @param nom nom du noeud
 * @param racine noeud racine du noeud
 * @param pere père du noeud
 * @return un noeud sans enfant 
 */
noeud *creer_noeud(bool dossier, const char *nom, noeud *racine, noeud *pere){
    noeud *n = malloc(sizeof(noeud));
    assert(n != NULL);
    n->est_dossier = dossier;
    set_nom(n, nom);
    n->pere = pere;
    n->racine = racine;
    n->fils = NULL;
    return n;
}

/**
 * Initialise une liste de noeuds de 1 élément
 * @param n premier élément de la liste
 * @return une liste de noeuds contenant uniquement le noeud n 
 */
liste_noeud *init_liste_noeud(noeud *n){
    liste_noeud *l = malloc(sizeof(liste_noeud));
    assert(l != NULL);
    l->no = n;
    l->succ = NULL;
    return l;
}

/**
 * Libère le noeud de la mémoire et la liste de ses fils si c'est un dossier 
 */
void destroy_noeud(noeud *n){
    if(n->est_dossier){
        destroy_liste_noeud(n->fils);  
    }
    free(n);
}

/**
 * Libère la liste l de la mémoire mais pas les noeuds qu'elle contient 
 */
void destroy_liste_noeud(liste_noeud *l){
    liste_noeud *tmp;
    while(l != NULL){
        tmp = l;
        l = l->succ;
        free(tmp);
    }
}

/**
 * Supprime la tête d'une liste de noeud
 * @param l liste dont on veut supprimer la tête
 * @return la nouvelle liste dont on a supprimé la tête 
 */
liste_noeud *supprHead(liste_noeud *l){
    if(l == NULL){
        return NULL;
    }
    if(l->succ == NULL){
        destroy_liste_noeud(l);
        return NULL;
    }
    liste_noeud *tmp = l;
    l = l->succ;
    free(tmp);
    return l;
}

/**
 * Insère le noeud n à la fin de la liste l
 * @param l liste à remplir
 * @param n noeud à insérer
 * @return retourne la liste modifiée
 */
liste_noeud *pushTail(liste_noeud *l, noeud *n){
    if(l != NULL){
        liste_noeud *queue = init_liste_noeud(n); 
        liste_noeud *tmp = l;
        while(tmp->succ != NULL){
            tmp = tmp->succ;
        }
        tmp->succ = queue;
        return l;
    }
    else{
        return init_liste_noeud(n);
    }
}