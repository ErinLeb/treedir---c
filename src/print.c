#include "../lib/struct.h"
#include "../lib/print.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * Effectue un parcours en largeur de l'arbre et affiche son contenu, en partant de la racine du noeud courant
 */
void print(){
    noeud *racine = courant ->racine;
    liste_noeud *fifo = init_liste_noeud(racine);

    while(fifo != NULL){
        noeud *courant = fifo->no;
        char *nomCourant = getNom(courant);
        char *nomPere = getNom(courant->pere);

        if(courant->est_dossier){ 
            printf("Noeud %s (D), père : %s, %i fils", nomCourant, nomPere, nombre_liste_noeud(courant->fils));
            if(nombre_liste_noeud(courant->fils) > 0){
                printf(" :");
            }   
            for(int i = 0; i < nombre_liste_noeud(courant->fils); ++i){
                if(get(courant->fils,i)->est_dossier){
                    printf(" %s (D)", getNom(get(courant->fils, i)));
                }
                else{
                    printf(" %s (F)", getNom(get(courant->fils, i)));
                }
                if(i != nombre_liste_noeud(courant->fils) - 1){
                    printf(",");
                }
            }
        }
        else{ 
            printf("Noeud %s (F), père : %s, 0 fils",nomCourant,nomPere);
        }
        printf("\n");
        
        for(int i = 0; i < nombre_liste_noeud(courant->fils); ++i){ 
            pushTail(fifo, get(courant->fils, i));
        }

        fifo = supprHead(fifo); 
    }
    destroy_liste_noeud(fifo); 
}