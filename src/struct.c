#include<stdbool.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<stdio.h>
#include "../lib/struct.h"

/**
 * initialise le noeud racine 
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
 * modifie le noeud du noeud donné en paramètre
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
 * initialise un noeud sans enfant
 * @param dossier vrai si le noeud est un dossier, faux sinon
 * @param nom nom du noeud
 * @param racine noeud racine du noeud
 * @param pere père du noeud
 * @return renvoie un noeud sans enfant 
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
 * libère le noeud de la mémoire et la liste de ses fils si c'est un dossier 
 */
void destroy_noeud(noeud *n){
    if(n->est_dossier){
        destroy_liste_noeud(n->fils);  
    }
    free(n);
}

/**
 * initialise une liste de noeuds de 1 élément
 * @param n premier élément de la liste
 * @return renvoie une liste de noeuds contenant uniquement le noeud n 
 */
liste_noeud *init_liste_noeud(noeud *n){
    liste_noeud *l = malloc(sizeof(liste_noeud));
    assert(l != NULL);
    l->no = n;
    l->succ = NULL;
    return l;
}

/**
 * libère la liste l de la mémoire mais pas les noeuds qu'elle contient 
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
 * renvoie le nombre de noeuds de la liste l
 * @param l liste de noeuds dont on veut connaitre le nombre de noeuds
 * @return renvoie le nombre de noeuds de la liste l 
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
 * supprime la tête d'une liste de noeud
 * @param l liste dont on veut supprimer la tête
 * @return renvoie la nouvelle liste dont on a supprimé la tête 
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
 * renvoie le noeud à l'indice i de la liste de noeuds
 * @param l liste de noeuds
 * @param i indice du noeud souhaité
 * @return renvoie le noeud à l'indice i de la liste 
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
 * insère le noeud n à la fin de la liste l
 * @param l liste à remplir
 * @param n noeud à insérer
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
 * renvoie une chaine de charactère contenant le nom du noeud donné en paramètre
 * @param n noeud dont on veut le nom
 * @return renvoie une chaine de caractère contenant le nom du noeud n
 */
char *getNom(noeud *n){
    int i = 0;
    char *nom;
    while(n->nom[i] != '\0'){
        ++i;
    }

    if(i>0){
        nom = malloc(sizeof(char)*i);
        assert(nom != NULL);

        for(int j = 0; j < i; ++j){
            nom[j] = n->nom[j];
        }
        nom[i] = '\0';
    
    }else{
        nom = malloc(sizeof(char)*2);
        assert(nom != NULL);
        nom[0] = '/';
        nom[1] = '\0';
    }
    return nom;
}

/*Vérifie si le noeud a un fils avec ce nom*/
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