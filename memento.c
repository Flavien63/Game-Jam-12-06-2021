#include <stdio.h>
#include <string.h>
#include <math.h>

#include <stdlib.h>

// gcc main.c -o prog -Wall -Wextra

/* ------------------------------- XXXXXXXX ------------------------------- */
/* ------------------------------------------------------------------------ */

/* -------------------------------- AUTRES -------------------------------- */
/*
#ifndef __NOM__     // Si la constante n'a pas déjà été défini
#define             // on la définie
#endif              // 
*/
/* ------------------------------------------------------------------------ */

/* ------------------------- ALLOCATION DYNAMIQUE ------------------------- */

    #include <stdlib.h>

    sizeof(<type>);           // Retourne la taille en octets d'une donnée

    malloc(<taille_en_octets>);              // Allouer dynamiquement une zone mémoire
    calloc(<nb_donnee>, <taille_en_octets>); // Allouer et initialiser tout à 0
    realloc(<donnee>, <nouvelle_taille>);    // Réallouer un espace mémoire
    free(<donnee_alloue>);                   // Libère la mémoire allouée dynamiquement



    int* tab = NULL;
    tab = (int*)malloc(sizeof(int) * 5);       // Après une allocation dynamique (tableau de 5 entiers)
    tab = (int*)calloc(5, sizeof(int));        // Allocation dynamique (tableau de 5 entiers, initialisés à 0)
    if (tab == NUL)                             // Tester si l'allocation a pu se faire
        exit(1);                                // Quitter le prog si echec
    tab = realloc(tab, sizeof(int) * 8);        // Réallouer la mémoire 
    if (tab == NUL) { exit(1); }                // Tester
    free(tab);                                  // Liberer la mémoire (sinon fuite de mémoire)


/* ------------------------------------------------------------------------ */



/* -------------------------- STRUCURES ET TYPES -------------------------- */

    [STRUCTURES]
        typedef struc maStructure
        {
            char chaîne[256];
            int entier;
        } nomTypeStruct;

        nomTypeStruct maVariable = {"chaîne de caractères", 5}

        (*monPointeur).un_champ = X;    <=>    monPointeur->un_champ = X;

    [ENUMERATIONS]
        typedef enum monEnumeration         // liste_couleurs
        {
            NOM_1 = 10,  // par defaut 0    // ROUGE
            NOM_2 = 20,  // par defaut 2    // VERT
            NOM_3 = 30   // par defaut 3    // BLEU
        } nomTypeEnum;                      // couleur

        nomTypeEnum maVariable = NOM_2;    <=>    nomTypeEnum maVariable = 20;
        //(Rend le code plus lisible en manipulant un NOM au lieu d'un nombre)

    [UNIONS]
    /* Permet de reserver un seul espace mémoire au même endroit suivant le
    type utilisé. (...) */

        union Nombre 
        {
            int entier;
            float reel;
        }
        union Nombre nb1;
        nb1.entier = 3;
        nb1.reel = 3.14;


/* ------------------------------------------------------------------------ */


/* ------------------------------- POINTEUR ------------------------------- */
/*
    Pointeur : variable contenant l'adresse d'une autre variable
    %p -> affiche de variable ou d'un pointeur

    [VARIALBES]
        maVariable  : valeur de la variable
        &maVariable : adresse de la variable

    [POINTEURS]     
        *monPointeur = NULL    ou     *monPointeur = &maVariable
        (déclaration et initialisation d'un pointeur)

        monPointeur  : adresse de la variable pointée
        *monPointeur : valeur de la variable pointée
        &monPointeur : adresse du pointeur
*/
/* ------------------------------------------------------------------------ */



/* ------------------------------- TABLEAU ------------------------------- */

    [Déclaration tableau]
        <type> <nom_tableau>[X];    //Déclare avec des valeurs aléatoires
    
    [Initialisation]
        char tableau[5] = {"valeur1", "valeur2", "valeur3", "valeur4", "valeur5"};
        int tableau[5] = {0};   //Toutes les cases valent 0
        int tableau[5] = {4};   //Première case vaut 4 et les autres valent 0

    [Accès au tableau]
        tableau[X] : élément d'indice X (X+1 ème élément, commence à l'indice 0)

    tableau        : adresse du tableau
    *tableau       : premier élément du tableau
    *(tableau + X) : élément d'indice X     <=>     tableau[X]

/* ------------------------------------------------------------------------ */

/* ------------------------- CHAINE DE CARACTERES ------------------------- */

    #include <string.h>

    [Chaîne de caractères]  
    Une chaîne de caratères est un tableau de char dont le dernier caractères est '\0'
        char mot[] = "texte";
        char mot[256];

    [Fonction des chaînes]
        strcpy(s_dst, s_src) : copie une chaîne dans une autre
        strlen(chaîne)   : longueur d'une chaîne (sans caractère '\0')
        strcmp(s1, s2)   : comparer 2 chaînes (lexicographiquement) [s1<s2 -> -1; s1=c2 -> 0; s1>s2 -> 1]
        strcat(s1, s2)   : concaténer 2 chaînes (fusionner)
        strstr(txt, mot) : chercher une chaine dans une autre
        strchr(txt, c)   : chercher 1ère occurence du caractère (renvoie un pointeur vers ce char)

        sprintf(mot, "hello", 5) : écrire dans une chaîne de caractères

/* ------------------------------------------------------------------------ */

/* ----------------------- Argument fonction main() ----------------------- */

    #include <stdio.h>

    /*              $ ./prog arg1 arg2 arg3 arg4 ...
        Les arguments sont des chaines de caractères. Utiliser atoi() pour avoir des entiers.
        argc est le nb d'arguments entrés dans le shell
            ./prog arg1  =>  2 arguments (le nom du programme compte comme un argument)
        argv est tableau contenant les arguments (sous formes de chaine)  
    */
    

int main(int argc, char ** argv)
{
    if(argc != 3)
    {
        printf(stderr, "Format : programme <txt1> <txt2>\n");
    }else{
        printf("Le programme %s est lancé avec les arguments %s et %s\n", argv[0]n argv[1], argv[2]);
    }
   return 0;
}

    $ ./prog 12 hello
    Le programme prog est lancé avec les arguments 12 et hello

/* ------------------------------------------------------------------------ */