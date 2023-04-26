#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "../lib/chemin.h"
#include "../lib/struct.h"

/**
 * fonction renvoyant le noeud au bout du chemin path en partant du noeud debut
 * @param debut noeud de départ
 * @param path chemin absolu ou relatif vers un noeud
 * @return un pointeur vers le noeud au bout de path en partant de noeud debut ou NULL si le chemin est incorrect 
 */
noeud *chemin(noeud *debut, char *path){
    if(strcmp(path,"") == 0 || strcmp(path,"/") == 0){
        return NULL;
    }
    int lecture = 0;
    int nom_len = 0;
    int chemin_parcouru = 0;
    char *nom = malloc(sizeof(char));
    noeud *courant;
    if(path[lecture] == '/'){
        courant = debut->racine;
        ++lecture;
        ++chemin_parcouru;
    }
    else{
        courant = debut;
    }
    while(path[lecture] != '\0'){
        while(path[lecture] != '/' && path[lecture] != '\0'){
            ++nom_len;
            ++lecture;
        }
        nom = realloc(nom,sizeof(char)*nom_len+1);
        for(int i=0; i < nom_len+1; ++i){
            if(i != nom_len){
                nom[i] = path[i+chemin_parcouru];
            }
            else{
                nom[i] = '\0';
            }
        }
        if(strcmp(nom,"..") == 0){
            courant = courant->pere;
        }
        else if(strcmp(nom,".") == 0){
            if(path[lecture] != '\0'){
                ++lecture;
            }
            chemin_parcouru += nom_len + 1;
            nom_len = 0;
            continue;
        }
        else{
            bool fils = false;
            for(int i = 0; i < nombre_liste_noeud(courant->fils); ++i){
                if(strcmp((get(courant->fils, i))->nom,nom) == 0){
                    courant = get(courant->fils, i);
                    fils = true;
                    break;
                }
            }
            if(!fils){
                free(nom);
                return NULL;
            }
        }
        if(path[lecture] != '\0'){
            ++lecture;
        }
        chemin_parcouru += nom_len + 1;
        nom_len = 0;
    }
    free(nom);
    return courant;
}