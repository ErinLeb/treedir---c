#ifndef STRUCT_H
#define STRUCT_H

#include<stdbool.h>

struct noeud{
    bool est_dossier; //vrai si dossier, faux si fichier, vrai pour la racine
    char nom[100];
    struct noeud *pere; //pointeur vers le père, elle-même pour la racine
    struct noeud *racine; //pointeur vers la racine
    struct liste_noeud *fils; //null si pas de fils, null si le noeud est un fichier
};

struct liste_noeud{
    struct noeud *no; 
    struct liste_noeud *succ;
};

typedef struct noeud noeud;
typedef struct liste_noeud liste_noeud;

extern noeud *creer_racine();
extern void set_nom(noeud *, const char *);
extern noeud *creer_noeud(bool, const char *, noeud *, noeud *);
extern void destroy_noeud(noeud *);
extern liste_noeud *init_liste_noeud();
extern void destroy_liste_noeud();
extern int size_liste_noeud(liste_noeud *);
extern liste_noeud *pushTail(liste_noeud *, noeud *);
extern noeud *get(liste_noeud *, int);
extern noeud *peek(liste_noeud *);
extern liste_noeud *supprHead(liste_noeud *);
extern void printList(liste_noeud *);

#endif
