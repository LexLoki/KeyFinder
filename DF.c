//
//  DFS.c
//  
//
//  Created by Pietro Ribeiro Pepe on 11/28/15.
//
//

#include "DF.h"

DF *newDF(char *esq, char *dir){
    DF *new = (DF*)malloc(sizeof(DF));
    new->esq = esq;
    new->dir = dir;
    return new;
}

void free_DF(DF *x){
    free(x->esq);
    free(x->dir);
    free(x);
}