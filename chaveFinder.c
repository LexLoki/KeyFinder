//
//  chaveFinder.c
//  
//
//  Created by Pietro Ribeiro Pepe on 11/28/15.
//
//

#include <stdio.h>

#include "DFSet.h"
#include <math.h>


typedef struct keySet KeySet;
struct keySet{
    int n;
    char **keys;
};

KeySet *getKeys(DFSet *set);
//KeySet *optimzeKeys(KeySet *set);

int main(void){
    
    int i;
    FILE *arq = fopen("dfs.txt","rt");
    if(arq == NULL){
        printf("Error opening file");
        exit(1);
    }
    DFSet *set = newSetFromFile(arq);
    fclose(arq);
    DFSet_print(set);
    
    KeySet *ks = getKeys(set);
    for(i=0; i<ks->n; i++){
        printf("key: %s\n", ks->keys[i]);
        free(ks->keys[i]);
    }
    free(ks->keys);
    free(ks);
    
    free_DFSet(set);
    
    exit(0);
    
}

int generateWithKey(DFSet *set, char *keys){
    char a, *esq, *dir, foundSymbols[20];
    DF *aux;
    int flag, n=0;
    int findKey, findAllKeys;
    int i, j, k;
    for(i=0; i<set->n; i++){
        aux = set->dfs[i];
        esq = aux->esq;
        //printf("esq: %s\n", esq);
        flag = 0;
        findAllKeys = 1;
        for(j=0; esq[j] != '\0'; j++){
            findKey = 0;
            for(k=0; keys[k] != '\0'; k++){
                if(keys[k] == esq[j]){
                    //printf("mfound: %c\n", esq[j]);
                    findKey = 1;
                    break;
                }
            }
            if(!findKey){
                findAllKeys = 0;
                break;
            }
        }
        if(findAllKeys){
            //printf("found: %s\n", esq);
            dir = aux->dir;
            for(j=0; dir[j] != '\0'; j++){
                findKey = 0;
                for(k=0; keys[k] != '\0'; k++){
                    if(keys[k] == dir[j]){
                        findKey = 1;
                        break;
                    }
                }
                if(!findKey){
                    foundSymbols[n++] = dir[j];
                    foundSymbols[n] = '\0';
                }
            }
        }
    }
    if(n>0){
        int quantKeys = strlen(keys)+n;
        if(quantKeys == strlen(set->symbols)){
            return 1;
        }
        else{
            char *new = (char*)malloc((quantKeys+1)+sizeof(char));
            strcpy(new,keys);
            strcat(new,foundSymbols);
            int v = generateWithKey(set, new);
            free(new);
            return v;
        }
    }
    else{
        return 0;
    }
}

void freeChar(char **ch, int n){
    int i;
    for (i=0; i<n; i++)
        if(ch[i]!=NULL)
            free(ch[i]);
    free(ch);
}

char **testeKeys(DFSet *set, char *key, int n, int doIt, int *quant){
    //int gen;
    int flag;
    char *aux, **result;
    if(doIt && strlen(key) != 0){
        flag = !generateWithKey(set, key);
    }
    else{
        flag = 1;
    }
    if(flag){
        if(set->symbols[n]!='\0'){
            int nn = strlen(key);
            aux = (char*)malloc((nn+2)*sizeof(char));
            strcpy(aux, key);
            aux[nn++] = set->symbols[n];
            aux[nn] = '\0';
            char **c1 = testeKeys(set, aux, n+1, 1, quant);
            int q1 = *quant;
            char *aux2 = copyString(key);
            char **c2 = testeKeys(set, aux2, n+1, 0, quant);
            int q2 = *quant;
            (*quant)+=q1;
            result = (char**)malloc((*quant)*sizeof(char*));
            int i,j;
            for(i=0; i<q1; i++){
                result[i] = copyString(c1[i]);
            }
            for(j=i,i=0;i<q2;i++,j++){
                result[j] = copyString(c2[i]);
            }
            if(c1!=NULL)
                freeChar(c1,q1);
            if(c2!=NULL)
                freeChar(c2,q2);
            free(aux);
            free(aux2);
            
            return result;
        }
        else{
            *quant = 0;
            return NULL;
        }
    }
    else{
        *quant = 1;
        result = (char **)malloc(sizeof(char*));
        result[0] = copyString(key);
        return result;
        //return &key;
    }
}

int strSubset(char *d, char *s){
    int i, j=0, didFind;
    for(i=0; s[i]!='\0'; i++){
        didFind = 0;
        while(d[j] != '\0')
            if(s[i]==d[j++]){
                didFind = 1;
                break;
            }
        if(!didFind)
            return 0;
    }
    return 1;
}

KeySet *getKeys(DFSet *set){
    KeySet *ks = (KeySet*)malloc(sizeof(KeySet));
    char *firstKey = (char*)malloc(sizeof(char));
    firstKey[0] = '\0';
    char **poorKeys = testeKeys(set, firstKey, 0, 1, &(ks->n));
    char **richKeys = (char**)malloc((ks->n)*sizeof(char*));
    int i,j,k,l=0,s1,s2,flag;
    for(i=0;i<ks->n;i++){
        flag = 1;
        s1 = strlen(poorKeys[i]);
        for(j=0;j<ks->n;j++){
            s2 = strlen(poorKeys[j]);
            if(s2<s1 && strSubset(poorKeys[i],poorKeys[j])){
                flag = 0;
                break;
            }
        }
        if(flag){
            richKeys[l++] = copyString(poorKeys[i]);
        }
    }
    freeChar(poorKeys,ks->n);
    ks->n = l;
    ks->keys = richKeys;
    free(firstKey);
    return ks;
}