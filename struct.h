#ifndef STRUCT_H
#define STRUCT_H

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
extern void set_nom(noeud *, char *);

#endif