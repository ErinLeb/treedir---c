#include<stdlib.h>
#include<stdbool.h>
#include<stdio.h>
#include "struct.h"
#include "ls.h"
#include "print.h"

int main(){
    // début des tests de print
    noeud * racine = creer_racine();
    
    noeud *cours = creer_noeud(true,"Cours",racine,racine);
    noeud *td = creer_noeud(true,"Td",racine,racine);
    noeud *edt = creer_noeud(false,"edt",racine,racine);

    liste_noeud *filsRacine = init_liste_noeud(cours);
    filsRacine = pushQueue(filsRacine,td);
    filsRacine = pushQueue(filsRacine,edt);
    racine->fils = filsRacine;

    noeud *projetC = creer_noeud(true,"ProjetC",racine,cours);
    noeud *anglais = creer_noeud(true,"anglais",racine,cours);

    cours->fils = pushQueue(cours->fils,projetC);
    cours->fils = pushQueue(cours->fils,anglais);

    noeud *td1 = creer_noeud(false,"td1",racine,td);
    noeud *td2 = creer_noeud(false,"td2",racine,td);

    td->fils = pushQueue(td->fils,td1);
    td->fils = pushQueue(td->fils,td2);

    print(racine);

    destroy_noeud(racine);
    destroy_noeud(cours);
    destroy_noeud(td);
    destroy_noeud(edt);
    destroy_noeud(projetC);
    destroy_noeud(anglais);
    destroy_noeud(td1);
    destroy_noeud(td2);

    // fin des tests de print
    
}