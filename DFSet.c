//
//  DFSet.c
//  
//
//  Created by Pietro Ribeiro Pepe on 11/28/15.
//
//

#include "DFSet.h"

char *copyString(char *source){
    char *dest = (char*)malloc((1+strlen(source))*sizeof(char));
    strcpy(dest,source);
    return dest;
}

DFSet *newSet(DF **dfs, int n, char *symbols){
    DFSet *new = (DFSet*)malloc(sizeof(DFSet));
    new->n = n;
    new->dfs = dfs;
    //new->symbols = (char*)malloc((strlen(symbols)+1)*sizeof(char));
    new->symbols = symbols;
    return new;
}

DFSet *newSetFromFile(FILE *arq){
    char aux[100], *auxBreak, *esq, *dir, symbols[20];
    int isFirst, quant, i;
    DF **dfs;
    
    fscanf(arq, " %[^\n]", symbols);
    fscanf(arq, "%d", &quant);
    dfs = (DF**)malloc(sizeof(DF*)*quant);
    
    for(i=0; i<quant; i++){
        fscanf(arq," %[^\n]", aux);
        isFirst = 1;
        esq = NULL;
        dir = NULL;
        auxBreak = strtok (aux," ");
        while (auxBreak != NULL){
            if(isFirst){
                if (strcmp(auxBreak, "->")==0){
                    isFirst = 0;
                }
                else{
                    esq = copyString(auxBreak);
                }
            }
            else{
                dir = copyString(auxBreak);
            }
            auxBreak = strtok (NULL, " ");
        }
        if(esq != NULL && dir != NULL)
            dfs[i] = newDF(esq,dir);
        else{
            printf("error reading");
            exit(1);
        }
    }
    return newSet(dfs, quant, copyString(symbols));
}

void DFSet_print(DFSet *set){
    int i;
    for(i=0; i<set->n; i++)
        printf("%s -> %s\n", set->dfs[i]->esq, set->dfs[i]->dir);
    printf("%s\n", set->symbols);
}

void free_DFSet(DFSet *set){
    int i;
    for(i=0; i<set->n; i++)
        free_DF(set->dfs[i]);
    free(set->dfs);
    free(set->symbols);
    free(set);
}