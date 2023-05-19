#include "../lib/chemin.h"
#include "../lib/struct.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/**
 * Renvoie le noeud au bout du chemin 'path' en partant du noeud 'debut'
 * 
 * @param debut noeud de départ
 * @param path  chemin absolu ou relatif vers un noeud
 * @return      un pointeur vers le noeud au bout de path en partant de noeud 'debut' ou NULL si le chemin est incorrect 
 */
noeud *chemin(noeud *debut, char *path){
    if(strcmp(path,"") == 0 || strcmp(path,"/") == 0 || path[strlen(path)-1] == '/'){
        return NULL;
    }

    int lecture = 0;
    int nom_len = 0;
    int chemin_parcouru = 0;
    char *nom = malloc(sizeof(char));
    if(nom == NULL){
        perror("Problème d'allocation.");
        exit(EXIT_FAILURE);
    }

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
        nom = realloc(nom, sizeof(char *) * (nom_len + 1));
        if(nom == NULL){
            perror("Problème d'allocation.");
            exit(EXIT_FAILURE);
        }
        for(int i = 0; i < nom_len + 1; ++i){
            if(i != nom_len){
                nom[i] = path[i + chemin_parcouru];
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
            if(has_son(courant, nom)){
                courant = get_by_name(courant, nom);
            }
            else{
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

/**
 * Renvoie la chaine de caractères située à la suite du dernier '/' contenu dans 'path'
 * 
 * @param path chemin dont on veut obtenir la chaine de caratères située après le dernier '/'
 * @return     la chaine de caractères située à la suite du dernier '/' contenu dans 'path'
 */
char *get_last_string(char *path){
    int nbSlash = 0;
    for(int i = 0; i < strlen(path); ++i){
        if(path[i] == '/'){
            ++nbSlash;
        }
    }

    if(nbSlash == 0){
        char *nom = malloc(sizeof(char *) * (strlen(path) + 1));
        if(nom == NULL){
            perror("Problème d'allocation.");
            exit(EXIT_FAILURE);
        }
        for(int i = 0; i < strlen(path) + 1; ++i){
            if(i == strlen(path)){
                nom[i] = '\0';
            }
            else{
                nom[i] = path[i];
            }
        }
        return nom;
    }

    int compteur = 0;
    int indiceSlash = 0;
    for(int i = 0; i < strlen(path); ++i){
        if(path[i] == '/'){
            ++compteur;
        }
        if(compteur != nbSlash){
            ++indiceSlash;
        }
    }

    char *nom = malloc(sizeof(char *) * (strlen(path)-indiceSlash));
    if(nom == NULL){
        perror("Problème d'allocation.");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < strlen(path) - indiceSlash + 1; ++i){
        if(i == strlen(path) - indiceSlash){
            nom[i] = '\0';
        }
        else{
            nom[i] = path[i + indiceSlash + 1];
        }
    }

    return nom;
}

/**
 * Renvoie le noeud situé au bout du chemin 'path' avant le dernier '/' en partant du noeud 'départ'
 * @param debut noeud de départ
 * @param path  chemin dont on veut trouver le noeud juste avant celui qui est situé au bout
 * @return      un pointeur vers le noeud situé juste avant le noeud au bout de 'path', NULL si celui ci n'existe pas
 */
noeud *chemin_precedent(noeud *debut, char *path){
    if(strcmp(path,"") == 0 || strcmp(path,"/") == 0){
        return NULL;
    }

    int nbSlash = 0;
    for(int i = 0; i < strlen(path); ++i){
        if(path[i] == '/'){
            ++nbSlash;
        }
    }

    if(nbSlash == 0){
        return debut;
    }
    else if(nbSlash == 1 && path[0] == '/'){
        return debut->racine;
    }

    int compteur = 0;
    int indiceSlash = 0;
    for(int i = 0; i < strlen(path); ++i){
        if(path[i] == '/'){
            ++compteur;
        }
        if(compteur != nbSlash){
            ++indiceSlash;
        }
    }
    char *newPath = malloc(sizeof(char *) * indiceSlash);
    if(newPath == NULL){
        perror("Problème d'allocation.");
        exit(EXIT_FAILURE);
    }
    
    for(int i = 0; i < indiceSlash + 1; ++i){
        if(i == indiceSlash){
            newPath[i] = '\0';
        }
        else{
            newPath[i] = path[i];
        }
    }
    noeud *resultat = chemin(debut,newPath);
    free(newPath);
    return resultat;
}