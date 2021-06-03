#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hash.h"
#include "input.c"


char stringvazia[1] = {'\0'};
tipoObjeto objetn = {stringvazia,0};

#define M 262139

link tab[M];

int hash(string v) {
    int i, h=v[0];
    for (i=1; v[i]!='\0'; i++) {
        h = (h*251+v[i]) % M;
    }
     //printf("%d ",h);
    if (h<0) return 0;
    return h;
}

void STinit() {
    int h;
    for (h=0; h<M; h++)
        tab[h]=NULL;
}

void STinsert(tipoObjeto* obj) {
    string v = obj->chave;
    int h = hash(v);
    link t;
    for (t=tab[h]; t!=NULL; t=t->next)
        if (strcmp(t->obj->chave,v)==0) break;
    if (t!=NULL)
        t->obj->ocorrencias++;
    else {
        link novo = malloc(sizeof(STnode));
        novo->obj = obj;
        novo->next = tab[h];
        tab[h] = novo;
    }
}

tipoObjeto* STsearch(string v) {
    link t;
    int h = hash(v);
    for (t=tab[h]; t!=NULL; t=t->next){
        if (strcmp(t->obj->chave,v)==0) break;
    }
    if (t!=NULL) return t->obj;
    // puts("ok");
    return NULL;
}

int main(int argc, char* argv[]) {
    FILE *fp;
    fp = fopen(argv[1],"r");
    char *w = malloc(256*sizeof(char));
    STinit();
    while (fscanf(fp,"%s",w)!=EOF) {
        if (w[strlen(w)-1]==',' || w[strlen(w)-1]=='.' || w[strlen(w)-1]=='!' || w[strlen(w)-1]=='?' || w[strlen(w)-1]==')')
            w[strlen(w)-1] = '\0';
        
        int size_w = strlen(w);
        for (int i=0; i<size_w; i++) {
            w[i] = tolower((int)w[i]);
        }

        tipoObjeto* t = malloc(sizeof(tipoObjeto));
        tipoObjeto* aux= malloc(sizeof(tipoObjeto));
        t = STsearch(w);
        if(t==NULL){
            aux->chave = malloc(30);
            strcpy(aux->chave,w);
            aux->ocorrencias = 1;
            STinsert(aux);
            // printf("%s -> %d\n", w, aux->ocorrencias);
        }
        else { 
            STinsert(t);
            // printf("%s -> %d\n", w, t->ocorrencias);
        }
    }
    
    fclose(fp);
    puts("DONE READING FILE");

    int input; scanf("%d", &input);
    string* solution = predict(input);

    return 0;
}
