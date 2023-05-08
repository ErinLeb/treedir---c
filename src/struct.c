#include "../lib/struct.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

noeud * courant;

/**
 * Modifie le nom du noeud 'n' par 'str'
 * 
 * @param n     noeud dont on veut modifier le nom
 * @param str   nouveau nom du noeud 
 */
void set_nom(noeud *n, char *str){
    if(n == n->racine && strcmp(str,"") == 0){
        n->nom[0] = '\0';
    }
    else if(!is_correct(str)){
        perror("Nom incorrect.");
        exit(EXIT_FAILURE);
    }
    else{
        for(int i = 0; i<=strlen(str); ++i){
            n->nom[i] = *(str+i);
        }
    }
}

/**
 * Renvoie le noeud à l'indice 'i' de la liste de noeuds 'l'
 * 
 * @param l liste de noeuds
 * @param i indice du noeud souhaité
 * @return  le noeud à l'indice 'i' de la liste 'l'
 */
noeud *get(liste_noeud *l, int i){
    if(i >= nombre_liste_noeud(l) || i < 0){
        perror("Indice incorrect.");
        exit(EXIT_FAILURE);
    }

    liste_noeud *courant = l;
    for(int j = 0; j < i; ++j){
        courant = courant->succ;
    }
    return courant->no;
}

/**
 * Renvoie le fils de 'n' ayant le nom 'nom'
 * 
 * @param n     noeud parent
 * @param nom   nom du fils que l'on cherche
 * @return      le noeud fils ayant le nom qu'on cherche
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
 * Vérifie si le noeud 'n' a un fils portant le nom 'nom'
 * 
 * @param n     noeud parent
 * @param nom   nom du fils 
 * @return      true si le noeud parent a un fils avec ce nom, false sinon
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
 * Vérifie que la chaine de caractères 'nom' ne comporte que des caractères alhpa-numériques, n'est pas vide et fait moins de 100 caractères
 * 
 * @param nom   chaine que l'on veut vérifier
 * @return      true si 'nom' n'est composé que de caractères alpha-numériques, n'est pas vide et fait moins de 100 caractères, false sinon
*/
bool is_correct(char *nom){
    if(strlen(nom) < 1 || strlen(nom) > 99){
        return false;
    }

    while(*nom != '\0'){
        if(!isalnum(*nom)){
            return false;
        }
        nom++;
    }
    return true;
}

/** 
 * Renvoie le nombre de noeuds de la liste 'l'
 * 
 * @param l liste de noeuds dont on veut connaitre le nombre de noeuds
 * @return  le nombre de noeuds de la liste 'l'
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
 * Crée un noeud racine 
 * 
 * @return un noeud racine
 */
noeud *creer_racine(){
    noeud * racine = malloc(sizeof(noeud));
    if(racine == NULL){
        perror("Problème d'allocation.");
        exit(EXIT_FAILURE);
    }

    racine->est_dossier = true;
    racine->pere = racine;
    racine->racine = racine;
    racine->fils = NULL;
    set_nom(racine, "");

    return racine;
}

/**
 * Initialise un noeud sans enfant
 * 
 * @param dossier   true si le noeud est un dossier, false sinon
 * @param nom       nom du noeud
 * @param racine    noeud racine du noeud
 * @param pere      père du noeud
 * @return          un noeud sans enfant 
 */
noeud *creer_noeud(bool dossier, char *nom, noeud *racine, noeud *pere){
    noeud *n = malloc(sizeof(noeud));
    if(n == NULL){
        perror("Problème d'allocation.");
        exit(EXIT_FAILURE);
    }

    n->est_dossier = dossier;
    n->pere = pere;
    n->racine = racine;
    n->fils = NULL;
    set_nom(n, nom);

    return n;
}

/**
 * Initialise une liste de noeuds de 1 élément
 * 
 * @param n premier élément de la liste
 * @return  une liste de noeuds contenant uniquement le noeud 'n' 
 */
liste_noeud *init_liste_noeud(noeud *n){
    liste_noeud *l = malloc(sizeof(liste_noeud));
    if(l == NULL){
        perror("Problème d'allocation.");
        exit(EXIT_FAILURE);
    }

    l->no = n;
    l->succ = NULL;

    return l;
}

/**
 * Libère le noeud 'n' de la mémoire et la liste de ses fils si c'est un dossier 
 */
void destroy_noeud(noeud *n){
    if(n->est_dossier){
        destroy_liste_noeud(n->fils);  
    }
    free(n);
}

/**
 * Libère la liste 'l' de la mémoire mais pas les noeuds qu'elle contient 
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
 * Lbère la mémoire allouée pour l'arbre de racine 'racine'
 * 
 * @param racine racine de l'arbre que l'on veut libérer
 */
void destroy_arbre(noeud *racine){
    if(racine->fils == NULL){
        free(racine);
    }
    else{
        for(int i = 0; i < nombre_liste_noeud(racine->fils); ++i){
            destroy_arbre(get(racine->fils,i));
        }
        destroy_liste_noeud(racine->fils);
        free(racine);
    }
}

/**
 * Supprime la tête de la liste de noeud 'l'
 * 
 * @param l liste dont on veut supprimer la tête
 * @return  la nouvelle liste dont on a supprimé la tête 
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
 * Insère le noeud 'n' à la fin de la liste 'l'
 * 
 * @param l liste à remplir
 * @param n noeud à insérer
 * @return  la liste modifiée
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

/**
 * Vérifie si le noeud 'n2' est dans le sous arbre de racine 'n1'
 * 
 * @param n1 racine du sous arbre dans lequel on cherche 'n2'
 * @param n2 noeud dont on cherche la présence dans le sous arbre de racine 'n1'
 * @return   true si 'n2' est dans le sous arbre de racine 'n1', false sinon
 */
bool est_dans_sous_arbre(noeud *n1, noeud *n2){
    noeud *tmp = n2;
    while(tmp != n2->racine){
        if(tmp == n1){
            return true;
        }
        tmp = tmp->pere;
    }
    return tmp == n1;
}

/**
 * Supprime le noeud 'n' de la liste 'l' sans libérer la mémoire qu'il occupe
 * 
 * @param l liste de noeuds dans laquelle on veut supprimer 'n'
 * @param n le noeud que l'on veut supprimer
 * @return  la liste de noeuds modifiée
*/
liste_noeud *suppr_noeud_liste(liste_noeud *l, noeud *n){
    if(l == NULL){
        return NULL;
    }

    if(l->no == n){
        l->no->pere = NULL;
        liste_noeud *tmp = l;
        l = l->succ;
        free(tmp);
        //on ne supprime pas le noeud de la mémoire
    }else{
        liste_noeud *tmp = l;
        while(tmp->succ != NULL){
            if(tmp->succ->no == n){
                liste_noeud *next = tmp->succ; //ce qu'on veut supprimer
                noeud *suppr = next->no;
                tmp->succ = next->succ;
                suppr->pere = NULL;
                free(next);
                //on ne supprime pas le noeud de la mémoire
                return l;
            }
            tmp = tmp->succ;
        }
    }
    return l;
}

/**
 * Renvoie une chaine de charactères contenant le nom du noeud 'n'

 * @param n noeud dont on veut le nom
 * @return  une chaine de caractères contenant le nom du noeud 'n'
 */
char *getNom(noeud *n){
    if(n == n->racine){
        return "/";
    }
    return n->nom;
}

/**
 * Crée une copie du noeud'n'
 * @param n noeud à copier
 * @return  une copie du noeud 'n'
 */
noeud *copie(noeud *n){
    if(n != n->racine){
        noeud *c = creer_noeud(n->est_dossier,n->nom,n->racine,n->pere);
        if(c->est_dossier && n->fils != NULL){
            c->fils = init_liste_noeud(copie(get(n->fils,0)));
            get(c->fils,0)->pere = c;
            for(int i = 1; i < nombre_liste_noeud(n->fils); ++i){
                pushTail(c->fils,copie(get(n->fils,i)));
                get(c->fils,i)->pere = c;
            }
        }
        return c;
    }
    else{
        noeud *c = creer_racine();
        if(n->fils != NULL){
            c->fils = init_liste_noeud(copie(get(n->fils,0)));
            get(c->fils,0)->pere = c;
            for(int i = 1; i < nombre_liste_noeud(n->fils); ++i){
                pushTail(c->fils,copie(get(n->fils,i)));
                get(c->fils,i)->pere = c;
            }
        }
        return c;
    } 
}