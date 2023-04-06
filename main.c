#include<stdlib.h>
#include<stdbool.h>
#include<stdio.h>
#include "struct.h"
#include "ls.h"
#include "pwd.h"

int main(){
    // début des tests de pwd
    noeud * racine = creer_racine();
    
    noeud *cours = creer_noeud(true,"Cours",racine,racine);
    noeud *td = creer_noeud(true,"Td",racine,racine);
    noeud *edt = creer_noeud(false,"edt",racine,racine);

    liste_noeud *filsRacine = init_liste_noeud(cours);
    filsRacine = pushTail(filsRacine,td);
    filsRacine = pushTail(filsRacine,edt);
    racine->fils = filsRacine;

    noeud *projetC = creer_noeud(true,"ProjetC",racine,cours);
    noeud *anglais = creer_noeud(true,"anglais",racine,cours);

    cours->fils = pushTail(cours->fils,projetC);
    cours->fils = pushTail(cours->fils,anglais);

    noeud *td1 = creer_noeud(false,"td1",racine,td);
    noeud *td2 = creer_noeud(false,"td2",racine,td);

    td->fils = pushTail(td->fils,td1);
    td->fils = pushTail(td->fils,td2);

    pwd(racine);
    pwd(cours);
    pwd(anglais);
    pwd(td1);

    destroy_noeud(racine);
    destroy_noeud(cours);
    destroy_noeud(td);
    destroy_noeud(edt);
    destroy_noeud(projetC);
    destroy_noeud(anglais);
    destroy_noeud(td1);
    destroy_noeud(td2);

    // fin des tests de pwd
    
}
