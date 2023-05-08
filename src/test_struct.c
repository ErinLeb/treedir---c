#include "../lib/struct.h"
#include "../lib/test_struct.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

void test_is_correct(){
    assert(!is_correct("   "));
    assert(!is_correct("    "));
    assert(!is_correct("&doss"));
    assert(!is_correct("-test"));
    assert(!is_correct("fic.1"));
    assert(is_correct("dossier123"));
    assert(is_correct("FIC"));
}

void test_creer_racine(){
    noeud *racine = creer_racine();

    assert(racine->est_dossier);
    assert(racine->fils == NULL);
    assert(strcmp(racine->nom, "") == 0);
    assert(racine->pere == racine);
    assert(racine->racine == racine);

    destroy_noeud(racine);
}

void test_creer_noeud(){
    noeud *racine = creer_racine();

    noeud *n = creer_noeud(false, "fichier", racine, racine);
    assert(!n->est_dossier);
    assert(strcmp(n->nom, "fichier") == 0);
    assert(n->fils == NULL);
    assert(n->racine == racine);
    assert(n->pere == racine);
    
    noeud *n1 = creer_noeud(true, "dossier", racine, racine);
    assert(n1->est_dossier);
    assert(strcmp(n1->nom, "dossier") == 0);
    assert(n1->fils == NULL);
    assert(n1->racine == racine);
    assert(n1->pere == racine);

    destroy_noeud(n);
    destroy_noeud(n1);
    destroy_noeud(racine);
}

void test_init_liste_noeud(){
    noeud *n = creer_noeud(false, "fic", NULL, NULL);
    liste_noeud *l = init_liste_noeud(n);
    assert(l != NULL);
    assert(l->no == n);
    assert(l->succ == NULL);

    destroy_liste_noeud(l);
    destroy_noeud(n);
}

void test_set_nom(){
    noeud *n = creer_noeud(true, "Dossier", NULL, NULL);
    assert(strcmp(n->nom, "Dossier") == 0);
    set_nom(n, "NouveauDossier");
    assert(strcmp(n->nom, "NouveauDossier") == 0);

    destroy_noeud(n);
}

void test_nombre_liste_noeud(){
    liste_noeud *l1 = malloc(sizeof(liste_noeud));
    assert(l1 != NULL);
    l1->no = NULL;
    l1->succ = NULL;
    assert(nombre_liste_noeud(l1) == 0);
    destroy_liste_noeud(l1); 

    noeud *n = creer_noeud(true, "dossier1", NULL, NULL);
    
    liste_noeud *l2 = init_liste_noeud(n);
    assert(nombre_liste_noeud(l2) == 1);

    liste_noeud *tmp = l2;
    tmp->succ = init_liste_noeud(n);
    tmp = tmp->succ;
    assert(nombre_liste_noeud(l2) == 2);

    tmp->succ = init_liste_noeud(n);
    tmp = tmp->succ;
    assert(nombre_liste_noeud(l2) == 3);
    
    tmp->succ = init_liste_noeud(n);
    tmp = tmp->succ;
    assert(nombre_liste_noeud(l2) == 4);

    destroy_liste_noeud(l2);
    destroy_noeud(n);
}

void test_pushTail(){
    liste_noeud *l = NULL;
    noeud *n1 = creer_noeud(false, "fic", NULL, NULL);
    l = pushTail(l, n1);
    assert(nombre_liste_noeud(l) == 1);
    assert(l->no == n1);

    noeud *n2 = creer_noeud(false, "fic", NULL, NULL);
    l = pushTail(l, n2);
    assert(nombre_liste_noeud(l) == 2);
    assert(l->no == n1);
    assert(l->succ->no == n2);

    destroy_liste_noeud(l);
    destroy_noeud(n1);
    destroy_noeud(n2);
}

void test_has_son(){
    noeud *racine = creer_racine();
    noeud *n1 = creer_noeud(true, "dossier1", racine, racine);
    noeud *n2 = creer_noeud(true, "dossier2", racine, racine);
    noeud *n3 = creer_noeud(false, "fic1", racine, racine);

    liste_noeud *l= init_liste_noeud(n1);
    l = pushTail(l, n2);
    l = pushTail(l, n3);
    racine->fils = l;

    assert(has_son(racine, "dossier1"));
    assert(has_son(racine, "dossier2"));
    assert(has_son(racine, "fic1"));
    assert(!has_son(racine, "fic2"));

    destroy_noeud(racine);
    destroy_noeud(n1);
    destroy_noeud(n2);
    destroy_noeud(n3);
}

void test_get(){
    noeud *racine = creer_racine();
    noeud *n1 = creer_noeud(true, "dossier1", racine, racine);
    noeud *n2 = creer_noeud(true, "dossier2", racine, racine);
    noeud *n3 = creer_noeud(false, "fic1", racine, racine);
    noeud *n4 = creer_noeud(false, "fic2", racine, racine);

    liste_noeud *l= init_liste_noeud(n1);
    l = pushTail(l, n2);
    l = pushTail(l, n3);
    l = pushTail(l, n4);
    racine->fils = l;

    assert(get(racine->fils, 0) == n1);
    assert(get(racine->fils, 1) == n2);
    assert(get(racine->fils, 2) == n3);
    assert(get(racine->fils, 3) == n4);

    destroy_noeud(racine);
    destroy_noeud(n1);
    destroy_noeud(n2);
    destroy_noeud(n3);
    destroy_noeud(n4);
}

void test_get_by_name(){
    noeud *racine = creer_racine();
    noeud *n1 = creer_noeud(true, "dossier1", racine, racine);
    noeud *n2 = creer_noeud(true, "dossier2", racine, racine);
    noeud *n3 = creer_noeud(false, "fic1", racine, racine);
    noeud *n4 = creer_noeud(false, "fic2", racine, racine);

    liste_noeud *l= init_liste_noeud(n1);
    l = pushTail(l, n2);
    l = pushTail(l, n3);
    l = pushTail(l, n4);
    racine->fils = l;

    assert(get_by_name(racine, "dossier1") == n1);
    assert(get_by_name(racine, "dossier2") == n2);
    assert(get_by_name(racine, "fic1") == n3);
    assert(get_by_name(racine, "fic2") == n4);
    assert(get_by_name(racine, "inexistant") == NULL);

    destroy_noeud(racine);
    destroy_noeud(n1);
    destroy_noeud(n2);
    destroy_noeud(n3);
    destroy_noeud(n4);
}

void test_supprHead(){
    noeud *n1 = creer_noeud(false, "fic1", NULL, NULL);
    noeud *n2 = creer_noeud(false, "fic2", NULL, NULL);
    noeud *n3 = creer_noeud(false, "fic3", NULL, NULL);

    liste_noeud *l = init_liste_noeud(n1);

    l = supprHead(l);
    assert(l == NULL);

    l = init_liste_noeud(n1);
    l = pushTail(l, n2);
    l = pushTail(l, n3);

    assert(nombre_liste_noeud(l) == 3);
    l = supprHead(l);
    assert(nombre_liste_noeud(l) == 2);
    assert(l->no == n2);
    
    destroy_noeud(n1);
    destroy_noeud(n2);
    destroy_noeud(n3);
    destroy_liste_noeud(l);
}

void test_suppr_noeud_liste(){
    noeud *racine = creer_racine();
    noeud *n1 = creer_noeud(false, "fic1", racine, racine);
    racine->fils = pushTail(racine->fils, n1);
    noeud *n2 = creer_noeud(false, "fic2", racine, racine);
    racine->fils = pushTail(racine->fils, n2);
    noeud *n3 = creer_noeud(false, "fic3", racine, racine);
    racine->fils = pushTail(racine->fils, n3);
    assert(nombre_liste_noeud(racine->fils) == 3);
    assert(get(racine->fils, 0) == n1);
    assert(get(racine->fils, 1) == n2);
    assert(get(racine->fils, 2) == n3);

    racine->fils = suppr_noeud_liste(racine->fils, n2);
    assert(n2->pere == NULL);
    assert(nombre_liste_noeud(racine->fils) == 2);
    assert(get(racine->fils, 0) == n1);
    assert(get(racine->fils, 1) == n3);

    racine->fils = suppr_noeud_liste(racine->fils, n1);
    assert(n1->pere == NULL);
    assert(nombre_liste_noeud(racine->fils) == 1);
    assert(get(racine->fils, 0) == n3);

    racine->fils = suppr_noeud_liste(racine->fils, n3);
    assert(n3->pere == NULL);
    assert(nombre_liste_noeud(racine->fils) == 0);
    assert(racine->fils == NULL);

    destroy_noeud(n3);
    destroy_noeud(n2);
    destroy_noeud(n1);
    destroy_noeud(racine);
}

void test_getNom(){
    noeud *racine = creer_racine();
    noeud *n = creer_noeud(false,"fichier",racine,racine);

    assert(strcmp(getNom(racine),"/") == 0);
    assert(strcmp(getNom(n),"fichier") == 0);

    destroy_noeud(racine);
    destroy_noeud(n);
}

void test_copie(){
    noeud *racine = creer_racine();
    noeud *n1 = creer_noeud(true,"dos1",racine,racine);
    noeud *n2 = creer_noeud(true,"dos2",racine,racine);

    liste_noeud *l = init_liste_noeud(n1);
    l = pushTail(l,n2);
    racine->fils = l;

    noeud *c = copie(racine);

    assert(strcmp(getNom(c),getNom(racine)) == 0);
    assert(racine->est_dossier == c->est_dossier);
    assert(nombre_liste_noeud(racine->fils) == nombre_liste_noeud(c->fils));
    for(int i = 0; i < nombre_liste_noeud(racine->fils); ++i){
        assert(strcmp(getNom(get(racine->fils,i)),getNom(get(c->fils,i))) == 0);
        assert(get(racine->fils,i)->est_dossier == get(c->fils,i)->est_dossier);
        assert(nombre_liste_noeud(get(racine->fils,i)->fils) == nombre_liste_noeud(get(c->fils,i)->fils));
    }

    destroy_arbre(racine);
    destroy_arbre(c);
}

void test_est_dans_sous_arbre(){
    noeud *racine = creer_racine();
    noeud *n1 = creer_noeud(true,"dos1",racine,racine);
    noeud *n2 = creer_noeud(true,"dos2",racine,racine);

    liste_noeud *l = init_liste_noeud(n1);
    l = pushTail(l,n2);

    racine->fils = l;

    assert(est_dans_sous_arbre(n1,n2) == false);
    assert(est_dans_sous_arbre(racine,n1) == true);
    
    destroy_arbre(racine);
}