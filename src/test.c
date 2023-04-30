#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<string.h>
#include "../lib/struct.h"
#include "../lib/chemin.h"
#include "../lib/ls.h"
#include "../lib/print.h"
#include "../lib/mkdir.h"
#include "../lib/touch.h"
#include "../lib/pwd.h"
#include "../lib/test_struct.h"
#include "../lib/rm.h"
#include "../lib/cd.h"
#include "../lib/cp.h"
#include "../lib/mv.h"

void test_ls();
void test_print();
void test_mkdir();
void test_touch();
void test_pwd();
void test_chemin();
void test_struct();
void test_rm();
void test_cd();
void test_cp();
void test_mv();

int main(){
    printf("####################################\n");
    test_struct();
    printf("####################################\n");
    test_ls();
    printf("####################################\n");
    test_print();
    printf("####################################\n");
    test_mkdir();
    printf("####################################\n");
    test_touch();
    printf("####################################\n");
    test_pwd();
    printf("####################################\n");
    test_chemin();
    printf("####################################\n");
    test_rm();
    printf("####################################\n");
    test_cd();
    printf("####################################\n");
    test_cp();
    printf("####################################\n");
    test_mv();
    printf("####################################\n");

}

void test_struct(){
    printf("-------Test de struct : début-------\n\n");

    puts("is_correct");
    test_is_correct();
    puts("");

    puts("creer_racine");
    test_creer_racine();

    puts("creer_noeud");
    test_creer_noeud();

    puts("init_liste_noeud");
    test_init_liste_noeud();

    puts("set_nom");
    test_set_nom();

    puts("nombre_liste_noeud");
    test_nombre_liste_noeud();

    puts("pushTail");
    test_pushTail();

    puts("has_son");
    test_has_son();

    puts("get");
    test_get();

    puts("get_by_name");
    test_get_by_name();

    puts("supprHead");
    test_supprHead();

    puts("suppr_noeud_liste");
    test_suppr_noeud_liste();
    
    puts("getNom");
    test_getNom();

    puts("copie");
    test_copie();

    puts("est_dans_sous_arbre");
    test_est_dans_sous_arbre();

    printf("\n-------Test de struct : fin-------\n");
}

void test_ls(){
    printf("-------Test de ls : début-------\n\n");

    noeud *n1 = creer_racine();
    noeud *n2 = creer_noeud(true, "sousDossier1", n1, n1);
    noeud *n3 = creer_noeud(true, "sousDossier2", n1, n1);
    noeud *n4 = creer_noeud(false, "fichier1", n1, n1);
    noeud *n5 = creer_noeud(true, "fichier2", n2, n1);

    liste_noeud *l = init_liste_noeud(n2);
    l = pushTail(l, n3);
    l = pushTail(l, n4);
    n1->fils = l;

    liste_noeud *l2 = init_liste_noeud(n5);
    n2->fils = l2;

    puts("Attendu : sousDossier1 sousDossier2 fichier1");
    printf ("Resultat de ls : ");
    ls(n1);

    puts("");

    puts("Attendu : fichier2");
    printf("Resultat de ls : ");
    ls(n2);

    puts("");

    destroy_noeud(n1);
    destroy_noeud(n2);
    destroy_noeud(n3);
    destroy_noeud(n4);
    destroy_noeud(n5);

    printf("-------Test de ls : fin-------\n");
}

void test_print(){
    printf("-------Test de print : début-------\n\n");

    noeud * racine = creer_racine();
    
    noeud *cours = creer_noeud(true,"Cours",racine,racine);
    noeud *td = creer_noeud(true,"Td",racine,racine);
    noeud *edt = creer_noeud(false,"edt",racine,racine);

    liste_noeud *filsRacine = init_liste_noeud(cours);
    filsRacine = pushTail(filsRacine,td);
    filsRacine = pushTail(filsRacine,edt);
    racine->fils = filsRacine;

    noeud *projetC = creer_noeud(true,"ProjetC",racine,cours);
    noeud *anglais = creer_noeud(true,"anglais",racine,cours);

    cours->fils = pushTail(cours->fils,projetC);
    cours->fils = pushTail(cours->fils,anglais);

    noeud *td1 = creer_noeud(false,"td1",racine,td);
    noeud *td2 = creer_noeud(false,"td2",racine,td);

    td->fils = pushTail(td->fils,td1);
    td->fils = pushTail(td->fils,td2);

    char * attendu = "Noeud / (D), père : /, 3 fils : Cours (D), Td (D), edt (F)\nNoeud Cours (D), père : /, 2 fils : ProjetC (D), anglais (D)\nNoeud Td (D), père : /, 2 fils : td1 (F), td2 (F)\nNoeud edt (F), père : /, 0 fils\nNoeud ProjetC (D), père : Cours, 0 fils\nNoeud anglais (D), père : Cours, 0 fils\nNoeud td1 (F), père : Td, 0 fils\nNoeud td2 (F), père : Td, 0 fils";

    printf("Attendu :\n%s\n", attendu);
    puts("");

    puts("Resultat de print : ");
    print(racine);
    puts("");

    destroy_noeud(racine);
    destroy_noeud(cours);
    destroy_noeud(td);
    destroy_noeud(edt);
    destroy_noeud(projetC);
    destroy_noeud(anglais);
    destroy_noeud(td1);
    destroy_noeud(td2);

    printf("-------Test de print : fin-------\n");
}

void test_mkdir(){ 
    printf("-------Test de mkdir : début-------\n\n");

    noeud * racine = creer_racine();

    assert(!has_son(racine, "Cours"));
    mkdir(racine, "Cours");
    assert(has_son(racine, "Cours"));
    noeud *cours = get_by_name(racine, "Cours");
    assert(cours->est_dossier);
    assert(cours->fils == NULL);
    assert(cours->racine == racine->racine);
    assert(cours->pere == racine);

    mkdir(racine, "Td");
    assert(has_son(racine, "Td"));
    assert(has_son(racine, "Cours"));
    noeud * td = get_by_name(racine, "Td");
    assert(td->est_dossier);
    assert(td->fils == NULL);
    assert(td->racine == racine->racine);
    assert(td->pere == racine);

    mkdir(cours, "ProjetC");
    assert(has_son(cours, "ProjetC"));
    noeud * projetC = get_by_name(cours, "ProjetC");
    assert(projetC->est_dossier);
    assert(projetC->fils == NULL);
    assert(projetC->racine == cours->racine);
    assert(projetC->pere == cours);

    mkdir(cours, "Anglais");
    assert(has_son(cours, "ProjetC"));
    assert(has_son(cours, "Anglais"));
    noeud *anglais = get_by_name(cours, "Anglais");
    assert(anglais->est_dossier);
    assert(anglais->fils == NULL);
    assert(anglais->racine == cours->racine);
    assert(anglais->pere == cours);

    destroy_noeud(racine);
    destroy_noeud(cours);
    destroy_noeud(td);
    destroy_noeud(projetC);
    destroy_noeud(anglais);

    printf("-------Test de mkdir : fin-------\n");
}

void test_touch(){
    printf("-------Test de touch : début-------\n\n");

    noeud * racine = creer_racine();

    touch(racine, "Texte1");
    assert(has_son(racine, "Texte1"));
    noeud *texte1 = get_by_name(racine, "Texte1");
    assert(!texte1->est_dossier);
    assert(texte1->pere == racine);
    assert(texte1->racine == racine);

    touch(racine, "Texte2");
    assert(has_son(racine, "Texte1"));
    assert(has_son(racine, "Texte2"));
    noeud *texte2 = get_by_name(racine, "Texte2");
    assert(!texte2->est_dossier);
    assert(texte1->pere == racine);
    assert(texte1->racine == racine);

    destroy_noeud(racine);
    destroy_noeud(texte1);
    destroy_noeud(texte2);

    printf("-------Test de touch : fin-------\n");
}

void test_pwd(){
    printf("-------Test de pwd : début-------\n\n");

    noeud * racine = creer_racine();
    
    noeud *cours = creer_noeud(true,"Cours",racine,racine);
    noeud *td = creer_noeud(true,"Td",racine,racine);
    noeud *edt = creer_noeud(false,"edt",racine,racine);

    liste_noeud *filsRacine = init_liste_noeud(cours);
    filsRacine = pushTail(filsRacine,td);
    filsRacine = pushTail(filsRacine,edt);
    racine->fils = filsRacine;

    noeud *projetC = creer_noeud(true,"ProjetC",racine,cours);
    noeud *anglais = creer_noeud(true,"anglais",racine,cours);

    cours->fils = pushTail(cours->fils,projetC);
    cours->fils = pushTail(cours->fils,anglais);

    noeud *td1 = creer_noeud(false,"td1",racine,td);
    noeud *td2 = creer_noeud(false,"td2",racine,td);

    td->fils = pushTail(td->fils,td1);
    td->fils = pushTail(td->fils,td2);

    puts("Attendu : /");
    printf("Résultat de pwd : ");
    pwd(racine);

    puts("\nAttendu : /Cours");
    printf("Résultat de pwd : ");
    pwd(cours);

    puts("\nAttendu : /Cours/Anglais");
    printf("Résultat de pwd : ");
    pwd(anglais);

    puts("\nAttendu : /Td/td1");
    printf("Résultat de pwd : ");
    pwd(td1);

    puts("");

    destroy_noeud(racine);
    destroy_noeud(cours);
    destroy_noeud(td);
    destroy_noeud(edt);
    destroy_noeud(projetC);
    destroy_noeud(anglais);
    destroy_noeud(td1);
    destroy_noeud(td2);

    printf("-------Test de pwd : fin-------\n");
}

void test_chemin(){
    printf("-------Test de chemin : début-------\n\n");

    noeud * racine = creer_racine();
    
    noeud *cours = creer_noeud(true,"Cours",racine,racine);
    noeud *td = creer_noeud(true,"Td",racine,racine);
    noeud *edt = creer_noeud(false,"edt",racine,racine);

    liste_noeud *filsRacine = init_liste_noeud(cours);
    filsRacine = pushTail(filsRacine,td);
    filsRacine = pushTail(filsRacine,edt);
    racine->fils = filsRacine;

    noeud *projetC = creer_noeud(true,"ProjetC",racine,cours);
    noeud *anglais = creer_noeud(true,"anglais",racine,cours);

    cours->fils = pushTail(cours->fils,projetC);
    cours->fils = pushTail(cours->fils,anglais);

    noeud *td1 = creer_noeud(false,"td1",racine,td);
    noeud *td2 = creer_noeud(false,"td2",racine,td);

    td->fils = pushTail(td->fils,td1);
    td->fils = pushTail(td->fils,td2);

    //tests de chemin
    assert(chemin(cours,"") == NULL);
    assert(chemin(cours,".") == cours);
    assert(chemin(cours,"././.") == cours);
    assert(chemin(cours,"/") == NULL);
    assert(chemin(cours,"/.") == racine);
    assert(chemin(cours,"anglais/.") == anglais);
    assert(chemin(cours,"/Td/td1") == td1);
    assert(chemin(cours,"../edt") == edt);
    assert(chemin(cours,"./ProjetC") == projetC);
    assert(chemin(cours,"math") == NULL);

    //tests de cheminPrecedent
    assert(chemin_precedent(cours,"") == NULL);
    assert(chemin_precedent(cours,"/") == NULL);
    assert(chemin_precedent(cours,"projetC") == cours);
    assert(chemin_precedent(cours,"./projetC") == cours);
    assert(chemin_precedent(cours,"math") == cours);
    assert(chemin_precedent(cours,"/Td") == racine);
    assert(chemin_precedent(cours,"/Cours/anglais") == cours);
    assert(chemin_precedent(racine,"Cours/anglais/worksheets") == anglais);
    assert(chemin_precedent(racine,"Cours/maths/Td1") == NULL);

    //tests de getLastString
    char *test = get_last_string("");
    assert(strlen(test) == 0);
    free(test);
    test = get_last_string("anglais");
    assert(strcmp(test,"anglais") == 0);
    free(test);
    test = get_last_string("/");
    assert(strlen(test) == 0);
    free(test);
    test = get_last_string("anglais/worksheets");
    assert(strcmp(test,"worksheets") == 0);
    free(test);
    test = get_last_string("/anglais");
    assert(strcmp(test,"anglais") == 0);
    free(test);
    test = get_last_string("/anglais/worksheets");
    assert(strcmp(test,"worksheets") == 0);
    free(test);
    
    destroy_noeud(racine);
    destroy_noeud(cours);
    destroy_noeud(td);
    destroy_noeud(edt);
    destroy_noeud(projetC);
    destroy_noeud(anglais);
    destroy_noeud(td1);
    destroy_noeud(td2);

    printf("-------Test de chemin : fin-------\n");
}

void test_rm(){
    printf("-------Test de rm : début-------\n");

    noeud *racine = creer_racine();
    //rm(racine, ""); //Ce chemin n'est pas valide.

    noeud *n1 = creer_noeud(true, "dos1", racine, racine);
    racine->fils = pushTail(racine->fils, n1);
    assert(has_son(racine, "dos1"));
    rm(racine, "dos1"); //ok
    assert(!has_son(racine, "dos1"));

    noeud *n1bis = creer_noeud(true, "dos1bis", racine, racine);
    racine->fils = pushTail(racine->fils, n1bis);
    assert(has_son(racine, "dos1bis"));

    noeud *n3 = creer_noeud(true, "dos2", racine, n1bis);
    n1bis->fils = pushTail(n1bis->fils, n3);
    assert(has_son(n1bis, "dos2"));

    //rm(n1bis, "/dos1bis"); //Le noeud à supprimer ne peut pas être un parent du noeud courant.

    rm(n1bis, "dos2"); //ok
    assert(!has_son(n1bis, "dos2"));

    noeud *n4 = creer_noeud(true, "dos3", racine, n1bis);
    n1bis->fils = pushTail(n1bis->fils, n4);
    assert(has_son(n1bis, "dos3"));
    rm(n1bis, "/dos1bis/dos3"); //ok
    assert(!has_son(n1bis, "dos3"));

    destroy_noeud(n1bis);
    destroy_noeud(racine);

    printf("-------Test de rm : fin-------\n");
}

void test_cd(){
    printf("-------Test de cd : début-------\n\n");

    noeud *racine = creer_racine();
    noeud *n1 = creer_noeud(true,"dos1",racine,racine);
    noeud *n2 = creer_noeud(true,"dos2",racine,racine);
    liste_noeud *l = init_liste_noeud(n1);
    l = pushTail(l,n2);
    racine->fils = l;
    noeud *courant = racine;

    courant = cd(courant,"dos1");
    assert(courant == n1);
    courant = cd(courant,"/dos2");
    assert(courant == n2);
    courant = cd(courant,"..");
    assert(courant == racine);
    courant = cd(courant,"./dos1");
    assert(courant == n1);
    courant = cd(courant,"");
    assert(courant = racine);

    destroy_noeud(racine);
    destroy_noeud(n1);
    destroy_noeud(n2);

    printf("-------Test de cd : fin-------\n");
}

void test_cp(){
    printf("-------Test de cp : début-------\n\n");

    noeud * racine = creer_racine();
    
    noeud *cours = creer_noeud(true,"Cours",racine,racine);
    noeud *td = creer_noeud(true,"Td",racine,racine);
    noeud *edt = creer_noeud(false,"edt",racine,racine);

    liste_noeud *filsRacine = init_liste_noeud(cours);
    filsRacine = pushTail(filsRacine,td);
    filsRacine = pushTail(filsRacine,edt);
    racine->fils = filsRacine;

    noeud *projetC = creer_noeud(true,"ProjetC",racine,cours);
    noeud *anglais = creer_noeud(true,"anglais",racine,cours);

    cours->fils = pushTail(cours->fils,projetC);
    cours->fils = pushTail(cours->fils,anglais);

    noeud *td1 = creer_noeud(false,"td1",racine,td);
    noeud *td2 = creer_noeud(false,"td2",racine,td);

    td->fils = pushTail(td->fils,td1);
    td->fils = pushTail(td->fils,td2);

    cp(racine,"Td","Cours");
    assert(nombre_liste_noeud(cours->fils) == 3);
    assert(has_son(cours,"Td"));
    assert(nombre_liste_noeud(get_by_name(cours,"Td")->fils) == 2);
    assert(has_son(get_by_name(cours,"Td"),"td1"));
    assert(has_son(get_by_name(cours,"Td"),"td2"));
    
    cp(racine,"Cours","Td/Maths");
    assert(nombre_liste_noeud(td->fils) == 3);
    assert(has_son(td,"Maths"));
    assert(nombre_liste_noeud(get_by_name(td,"Maths")->fils) == 3);
    assert(has_son(get_by_name(td,"Maths"),"ProjetC"));
    assert(has_son(get_by_name(td,"Maths"),"anglais"));
    assert(has_son(get_by_name(td,"Maths"),"Td"));
    assert(nombre_liste_noeud(get_by_name(get_by_name(td,"Maths"),"Td")->fils) == 2);
    assert(has_son(get_by_name(get_by_name(td,"Maths"),"Td"),"td1"));
    assert(has_son(get_by_name(get_by_name(td,"Maths"),"Td"),"td2"));

    destroy_arbre(racine);

    printf("-------Test de cp : fin-------\n");
}

void test_mv(){
    printf("-------Test de mv : début-------\n\n");

    noeud * racine = creer_racine();
    
    noeud *cours = creer_noeud(true,"Cours",racine,racine);
    noeud *td = creer_noeud(true,"Td",racine,racine);
    noeud *edt = creer_noeud(false,"edt",racine,racine);

    liste_noeud *filsRacine = init_liste_noeud(cours);
    filsRacine = pushTail(filsRacine,td);
    filsRacine = pushTail(filsRacine,edt);
    racine->fils = filsRacine;

    noeud *projetC = creer_noeud(true,"ProjetC",racine,cours);
    noeud *anglais = creer_noeud(true,"anglais",racine,cours);

    cours->fils = pushTail(cours->fils,projetC);
    cours->fils = pushTail(cours->fils,anglais);

    noeud *td1 = creer_noeud(false,"td1",racine,td);
    noeud *td2 = creer_noeud(false,"td2",racine,td);

    td->fils = pushTail(td->fils,td1);
    td->fils = pushTail(td->fils,td2);

    mv(racine,"Td","Cours");
    assert(nombre_liste_noeud(racine->fils) == 2);
    assert(!has_son(racine,"Td"));
    assert(nombre_liste_noeud(cours->fils) == 3);
    assert(has_son(cours,"Td"));
    assert(td->pere == cours);
    assert(nombre_liste_noeud(td->fils) == 2);

    mv(racine,"Cours/Td/td1","td3");
    assert(nombre_liste_noeud(td->fils) == 1);
    assert(nombre_liste_noeud(racine->fils) == 3);
    assert(strcmp(getNom(td1),"td3") == 0);
    assert(has_son(racine,"td3"));
    assert(!has_son(td,"td1"));
    assert(td1->pere == racine);

    mv(racine,"Cours/Td/td2","Cours/Td/td1");
    assert(nombre_liste_noeud(td->fils) == 1);
    assert(strcmp(getNom(td2),"td1") == 0);
    assert(has_son(td,"td1"));
    assert(!has_son(td,"td2"));
    assert(td2->pere == td);

    destroy_arbre(racine);

    printf("-------Test de mv : fin-------\n");
}
