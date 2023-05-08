#include"../lib/parseur.h"
#include "../lib/struct.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
    if(argc < 2){
        perror("Veuillez indiquer un nom de fichier.");
        exit(EXIT_FAILURE);
    }
    if(argc > 2){
        perror("Veuillez indiquer un seul nom de fichier.");
        exit(EXIT_FAILURE);
    }
    courant = creer_racine();
    parseur_fic(argv[1]);
    destroy_arbre(courant);
    exit(EXIT_SUCCESS);
}