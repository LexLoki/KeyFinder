//
//  DFS.h
//  
//
//  Created by Pietro Ribeiro Pepe on 11/28/15.
//
//

#ifndef DF_h
#define DF_h

#include <stdio.h>
#include <stdlib.h>

typedef struct df DF;

struct df{
    char *esq;
    char *dir;
};

DF *newDF(char *esq, char *dir);

void free_DF(DF *x);

#endif /* DFS_h */
