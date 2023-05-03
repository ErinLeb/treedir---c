#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "../lib/parseur.h"
#include "../lib/struct.h"
#include "../lib/chemin.h"
#include "../lib/ls.h"
#include "../lib/print.h"
#include "../lib/mkdir.h"
#include "../lib/touch.h"
#include "../lib/pwd.h"
#include "../lib/cd.h"
#include "../lib/cp.h"
#include "../lib/rm.h"
#include "../lib/mv.h"

void commande(char *comm, char *chem1, char *chem2){
    //erreur du parseur de fichier et non d'une mauvaise ligne de commande 
    assert(comm != NULL);
    if(chem2 != NULL){
        assert(chem1 != NULL);
    }

    if(chem1 == NULL && chem2 == NULL){
        if(strcmp(comm, "ls") == 0){
            ls();
        }else if(strcmp(comm, "print") == 0){
            print();
        }else if(strcmp(comm, "pwd") == 0){
            pwd();
        }else if(strcmp(comm, "cd") == 0){
            cd(chem1);
        }else if(strcmp(comm, "mkdir") == 0 || strcmp(comm, "touch") == 0 || strcmp(comm, "cp") == 0 || strcmp(comm, "mv") == 0){
            perror("Il n'y a pas assez d'arguments.");
            exit(1);
        }else{
            perror("Cette commande n'existe pas.");
            exit(1);
        }
    }
    else if (chem2 == NULL){
        if(strcmp(comm, "mkdir") == 0){
            mkdir(chem1);
        }else if (strcmp(comm, "touch") == 0){
            touch(chem1);
        }else if(strcmp(comm, "cd") == 0){
            cd(chem1);
        }else if(strcmp(comm, "cp") == 0 || strcmp(comm, "mv") == 0){
            perror("Il n'y a pas assez d'arguments.");
            exit(1);
        }else if(strcmp(comm, "ls") == 0 || strcmp(comm, "print") == 0 || strcmp(comm, "pwd") == 0){
            perror("Il y a trop d'arguments.");
            exit(1);
        }
        else{
            perror("Cette commande n'existe pas.");
            exit(1);
        }
    }
    else{
        if(strcmp(comm, "cp") == 0){
            cp(chem1, chem2);
        }else if(strcmp(comm, "mv") == 0){
            mv(chem1, chem2);
        }else if(strcmp(comm, "ls") == 0 || strcmp(comm, "print") == 0 || strcmp(comm, "pwd") == 0 || strcmp(comm, "mkdir") == 0 || strcmp(comm, "touch") == 0){
            perror("Il y a trop d'arguments.");
            exit(1);
        }else{
            perror("Cette commande n'existe pas.");
            exit(1);
        }
    }
}