//
//  DFSet.h
//  
//
//  Created by Pietro Ribeiro Pepe on 11/28/15.
//
//

#ifndef DFSet_h
#define DFSet_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DF.h"

typedef struct dfSet DFSet;

struct dfSet{
    int n;
    DF **dfs;
    char *symbols;
};

char *copyString(char *source);

DFSet *newSetFromFile(FILE *arq);

void DFSet_print(DFSet *set);

void free_DFSet(DFSet *set);

#endif /* DFSet_h */
