#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<assert.h>
#include "struct.h"
#include "print.h"

/**
 * effectue un parcours en largeur de l'arbre et affiche son contenu
 * @param racine noeud racine de l'arbre
 */
void print(noeud *racine){
    // initialisation de la file de noeuds
    liste_noeud *fifo = init_liste_noeud(racine);

    //parcours en largeur et affichage du contenu de l'arbre
    while(fifo != NULL){
        noeud *courant = fifo->no;
        char *nomCourant = getNom(courant);
        char *nomPere = getNom(courant->pere);

        if(courant->est_dossier){ 
            if(nombre_liste_noeud(courant->fils) > 0){ 
                printf("Noeud %s (D), père : %s, %i fils :", nomCourant, nomPere, nombre_liste_noeud(courant->fils));
                
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
            }

            else{ 
                printf("Noeud %s (D), père : %s, 0 fils",nomCourant,nomPere);
            }
        }
        
        else{ 
            printf("Noeud %s (F), père : %s, 0 fils",nomCourant,nomPere);
        }

        printf("\n");
        
        for(int i = 0; i < nombre_liste_noeud(courant->fils); ++i){ // on remplit la file avec les fils du noeud courant
            pushTail(fifo, get(courant->fils, i));
        }

        fifo = supprHead(fifo); // on supprime la tête de la file
        free(nomCourant);
        free(nomPere);
    }

    destroy_liste_noeud(fifo); 
}
