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
        noeud *courant = peek(fifo);

        if(courant->est_dossier){ // si le noeud courant est un dossier
            if(size_liste_noeud(courant->fils)>0){ // s'il a au moins un fils
                printf("Noeud %s (D), père : %s, %i fils :",courant->nom,courant->pere->nom,size_liste_noeud(courant->fils));
                for(int i=0;i<size_liste_noeud(courant->fils)-1;++i){
                    if(get(courant->fils,i)->est_dossier){ // si le fils est un dossier
                        printf(" %s (D),",get(courant->fils,i)->nom);
                    }
                    else{ // si le fils est un fichier
                        printf(" %s (F),",get(courant->fils,i)->nom);
                    }
                }
                // on affiche le dernier fils sans virgule à la fin
                if(get(courant->fils,size_liste_noeud(courant->fils)-1)->est_dossier){
                    printf(" %s (D)",get(courant->fils,size_liste_noeud(courant->fils)-1)->nom);
                }
                else{
                    printf(" %s (F)",get(courant->fils,size_liste_noeud(courant->fils)-1)->nom);
                }
            }
            else{ // si le noeud courant n'a pas de fils 
                printf("Noeud %s (D), père : %s, %i fils",courant->nom,courant->pere->nom,size_liste_noeud(courant->fils));
            }
        }
        else{ // si le noeud courant est un fichier
            printf("Noeud %s (F), 0 fils",courant->nom);
        }
        printf("\n");
        for(int i=0;i<size_liste_noeud(courant->fils);++i){ // on remplit la file avec les fils du noeud courant
            pushTail(fifo,get(courant->fils,i));
        }
        fifo = supprHead(fifo); // on supprime la tête de la file
    }
    destroy_liste_noeud(fifo); // on libère la mémoire de la file
}