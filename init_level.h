#ifndef _INITNIVEAU_H_
#define _INITNIVEAU_H_

#include <stdlib.h>
#include <stdio.h>
#include "perso.h"

void import_level(int mat[200][300], FILE * level_file,int chargerpos,etat_perso_t *etat);

void import_file(int mat[200][300], const char * level_file,int chargerpos,etat_perso_t* etat);

#endif
