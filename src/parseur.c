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
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

/**
 * Appelle la fonction désignée par 'comm' avec ses arguments s'ils sont corrects.
 * 
 * @param comm  commande à exécuter
 * @param chem1 premier argument s'il y en a un, NULL sinon
 * @param chem2 deuxième argument s'il y en a un, NULL sinon
*/
void commande(char *comm, char *chem1, char *chem2){
    //erreur du parseur de fichier et non d'une mauvaise ligne de commande 
    if(comm == NULL){
        perror("Pas de commande à exécuter.");
        exit(EXIT_FAILURE);
    }
    if(chem2 != NULL && chem1 == NULL){
        perror("Arguments invalides.");
        exit(EXIT_FAILURE);
    }

    if(chem1 == NULL && chem2 == NULL){
        if(strcmp(comm, "ls") == 0){
            puts("--------------------ls--------------------");
            ls();
            puts("");
        }else if(strcmp(comm, "print") == 0){
            puts("-------------------print------------------");
            print();
            puts("");
        }else if(strcmp(comm, "pwd") == 0){
            puts("-------------------pwd--------------------");
            pwd();
            puts("");
        }else if(strcmp(comm, "cd") == 0){
            cd(chem1);
        }else if(strcmp(comm, "mkdir") == 0 || strcmp(comm, "touch") == 0 || strcmp(comm, "cp") == 0 || strcmp(comm, "mv") == 0 || strcmp(comm, "rm") == 0){
            perror("Il n'y a pas assez d'arguments.");
            exit(EXIT_FAILURE);
        }else{
            perror("Cette commande n'existe pas.");
            exit(EXIT_FAILURE);
        }
    }
    else if (chem2 == NULL){
        if(strcmp(comm, "mkdir") == 0){
            mkdir(chem1);
        }else if (strcmp(comm, "touch") == 0){
            touch(chem1);
        }else if(strcmp(comm, "cd") == 0){
            cd(chem1);
        }else if(strcmp(comm, "rm") == 0){
            rm(chem1);
        }else if(strcmp(comm, "cp") == 0 || strcmp(comm, "mv") == 0){
            perror("Il n'y a pas assez d'arguments.");
            exit(EXIT_FAILURE);
        }else if(strcmp(comm, "ls") == 0 || strcmp(comm, "print") == 0 || strcmp(comm, "pwd") == 0){
            perror("Il y a trop d'arguments.");
            exit(EXIT_FAILURE);
        }
        else{
            perror("Cette commande n'existe pas.");
            exit(EXIT_FAILURE);
        }
    }
    else{
        if(strcmp(comm, "cp") == 0){
            cp(chem1, chem2);
        }else if(strcmp(comm, "mv") == 0){
            mv(chem1, chem2);
        }else if(strcmp(comm, "ls") == 0 || strcmp(comm, "print") == 0 || strcmp(comm, "pwd") == 0 || strcmp(comm, "mkdir") == 0 || strcmp(comm, "touch") == 0 || strcmp(comm, "rm") == 0){
            perror("Il y a trop d'arguments.");
            exit(EXIT_FAILURE);
        }else{
            perror("Cette commande n'existe pas.");
            exit(EXIT_FAILURE);
        }
    }
}


/**
 * Parse une ligne en mots et fait appel à 'commande' pour parser chaque commande
 * 
 * @param ligne ligne à parser
 */
void parseur_ligne(char *ligne){
    char *comm = NULL;
    char *chem1 = NULL;
    char *chem2 = NULL;
    bool espace = true;
    int nbMots = 0;
    
    for(int i = 0; i < strlen(ligne); ++i){
        if(isspace(ligne[i])){
            espace = true;
        }
        else if(espace){
            ++nbMots;
            espace = false;
        }
    }
    
    if(nbMots > 3){
        perror("Aucune commande ne prend plus de deux arguments.");
        exit(EXIT_FAILURE);
    }

    espace = true;
    int debut_mot = 0;
    int len_mot = 0;
    for(int i = 0; i < nbMots; ++i){
        for(int j = debut_mot; j < strlen(ligne); ++j){
            if(isspace(ligne[j]) && espace){
                ++debut_mot;
            }
            else if(isspace(ligne[j])){
                break;
            }
            else{
                ++len_mot;
                espace = false;
            }
        }
        switch (i){
        case 0:
            comm = malloc(sizeof(char *) * (len_mot + 1));
            if(comm == NULL){
                perror("Problème d'allocation.");
                exit(EXIT_FAILURE);
            }
            for(int i = debut_mot; i < debut_mot + len_mot + 1; ++i){
                if(i != debut_mot + len_mot){
                    comm[i - debut_mot] = ligne[i];
                }
                else{
                    comm[i - debut_mot] = '\0';
                }
            }
            break;
        
        case 1:
            chem1 = malloc(sizeof(char *) * (len_mot + 1));
            if(chem1 == NULL){
                perror("Problème d'allocation.");
                exit(EXIT_FAILURE);
            }
            for(int i = debut_mot; i < debut_mot + len_mot + 1; ++i){
                if(i != debut_mot + len_mot){
                    chem1[i - debut_mot] = ligne[i];
                }
                else{
                    chem1[i - debut_mot] = '\0';
                }
            }
            break;

        case 2:
            chem2 = malloc(sizeof(char *) * (len_mot + 1));
            if(chem2 == NULL){
                perror("Problème d'allocation.");
                exit(EXIT_FAILURE);
            }
            for(int i = debut_mot; i < debut_mot + len_mot + 1; ++i){
                if(i != debut_mot + len_mot){
                    chem2[i - debut_mot] = ligne[i];
                }
                else{
                    chem2[i - debut_mot] = '\0';
                }
            }
            break;
        }
        espace = true;
        debut_mot += len_mot;
        len_mot = 0;
    }

    if(nbMots != 0){
        commande(comm, chem1, chem2);
        if(nbMots >= 1){
            free(comm);
        }
        if(nbMots >= 2){
            free(chem1);
        }
        if(nbMots == 3){
            free(chem2);
        }
    }
}


/**
 * Parse un fichier en lignes et fait appel à 'parseur_ligne' pour parser chaque ligne
 * 
 * @param path chemin dans le répertoire du fichier à parser
 */
void parseur_fic(char *path){
    FILE *fic = fopen(path,"r");
    if(fic == NULL){
        perror("Problème avec l'ouverture du fichier.");
        exit(EXIT_FAILURE);
    }

    char *ligne = "";
    int lecture = 0;
    int len_ligne = 0;
    int debut_ligne = 0;
    int c = 0;
    while((c = fgetc(fic)) != EOF){
        if(c != '\n'){
            ++len_ligne;
        }
        else{
            lecture = fseek(fic, debut_ligne, SEEK_SET);
            if(lecture != 0){
                perror("Problème de déplacement de la tête de lecture.");
                exit(EXIT_FAILURE);
            }
            ligne = malloc(sizeof(char *) * (len_ligne + 1));
            if(ligne == NULL){
                perror("Problème d'allocation.");
                exit(EXIT_FAILURE);
            }
            char *s = fgets(ligne, len_ligne + 1, fic);
            if(s == NULL){
                perror("Problème d'allocation.");
                exit(EXIT_FAILURE);
            }
            parseur_ligne(ligne);
            free(ligne);
            debut_ligne += len_ligne + 1;
            lecture = fseek(fic, debut_ligne, SEEK_SET);
            if(lecture != 0){
                perror("Problème de déplacement de la tête de lecture.");
                exit(EXIT_FAILURE);
            }
            len_ligne = 0;
        }
    }

    // gestion du cas où la dernière ligne ne finit pas par '\n'
    if(len_ligne != 0){
        lecture = fseek(fic, debut_ligne, SEEK_SET);
        if(lecture != 0){
            perror("Problème de déplacement de la tête de lecture.");
            exit(EXIT_FAILURE);
        }
        ligne = malloc(sizeof(char) * (len_ligne + 1));
        if(ligne == NULL){
            perror("Problème d'allocation.");
            exit(EXIT_FAILURE);
        }
        char *s = fgets(ligne, len_ligne + 1, fic);
        if(s == NULL){
            perror("Problème d'allocation.");
            exit(EXIT_FAILURE);
        }
        parseur_ligne(ligne);
        free(ligne);
    }

    lecture = fclose(fic);
    if(lecture != 0){
        perror("Problème avec la fermeture du fichier.");
        exit(EXIT_FAILURE);
    }
}