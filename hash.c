#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

char stringvazia[1] = {'\0'};
tipoObjeto objetonulo = {stringvazia,0};

#define M 1021

link tab[M];

int hash(string v) {
    int i, h=v[0];
    for (i=1; v[i]!='\0'; i++)
        h = (h*251+v[i]) % M;
    return h;
}

void STinit() {
    int h;
    for (h=0; h<M; h++)
        tab[h]=NULL;
}

void STinsert(tipoObjeto obj) {
    string v = obj.chave;
    int h = hash(v);
    link t;
    for (t=tab[h]; t!=NULL; t=t->next)
        if (strcmp(t->obj.chave,v)==0) break;
    if (t!=NULL)
        t->obj.ocorrencias++;
    else {
        obj.ocorrencias = 1;
        link novo = malloc(sizeof(STnode));
        novo->obj = obj;
        novo->next = tab[h];
        tab[h] = novo;
    }
}

tipoObjeto STsearch(string v) {
    link t;
    int h = hash(v);
    for (t=tab[h]; t!=NULL; t=t->next)
        if (strcmp(t->obj.chave,v)==0) break;
    if (t!=NULL) return t->obj;
    return objetonulo;
}

int main(int argc, char* argv[]) {
    FILE *fp;
    fp = fopen(argv[1],"r");
    char ch;
    while ((ch=fgetc(fp))!=EOF) {
        
    }
    return 0;
}
