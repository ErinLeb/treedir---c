#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<assert.h>
#include "../lib/struct.h"
#include "../lib/print.h"

/**
 * Effectue un parcours en largeur de l'arbre et affiche son contenu
 * @param racine noeud racine de l'arbre
 */
void print(noeud *racine){
    liste_noeud *fifo = init_liste_noeud(racine);

    while(fifo != NULL){
        noeud *courant = fifo->no;

        if(courant->est_dossier){ 
            if(nombre_liste_noeud(courant->fils) > 0){ 
                printf("Noeud %s (D), père : %s, %i fils :", courant->nom, courant->pere->nom, nombre_liste_noeud(courant->fils));
                
                for(int i = 0; i < nombre_liste_noeud(courant->fils); ++i){
                    if(get(courant->fils, i)->est_dossier){ 
                        printf(" %s (D)", get(courant->fils, i)->nom);
                    }else{
                        printf(" %s (F)", get(courant->fils, i)->nom);
                    }

                    if(i != nombre_liste_noeud(courant->fils) - 1){
                        printf(",");
                    }
                }

            }else{ 
                printf("Noeud %s (D), père : %s, 0 fils",courant->nom,courant->pere->nom);
            }

        }else{ 
            printf("Noeud %s (F), père : %s, 0 fils", courant->nom,courant->pere->nom);
        }
        printf("\n");
        
        for(int i = 0; i < nombre_liste_noeud(courant->fils); ++i){ 
            pushTail(fifo, get(courant->fils, i));
        }

        fifo = supprHead(fifo); 
    }
    destroy_liste_noeud(fifo); 
}