#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hash.h"


char stringvazia[1] = {'\0'};
tipoObjeto objetn = {stringvazia,0};

#define M 989898

link tab[M];

int c2n(char c) {
    switch (c) {
    case 'a':
    case 'b':
    case 'c':
        return 2;
    case 'd':
    case 'e':
    case 'f':
        return 3;
    case 'g':
    case 'h':
    case 'i':
        return 4;
    case 'j':
    case 'k':
    case 'l':
        return 5;
    case 'm':
    case 'n':
    case 'o':
        return 6;
    case 'p':
    case 'q':
    case 'r':
    case 's':
        return 7;
    case 't':
    case 'u':
    case 'v':
        return 8;
    case 'w':
    case 'x':
    case 'y':
    case 'z':
        return 9;
    default:
        return 1;
    }
}

// int hash(string v) {
//     int i, h=v[0];
//     for (i=1; v[i]!='\0'; i++) {
//         h = (h*251+v[i]) % M;
//     }
//      //printf("%d ",h);
//     if (h<0) return 0;
//     return h;
// }

int hash(string v) {
    int size = strlen(v);
    int count=0;
    int h=0;
    for (int i=0; i<size; i++) {
        if (count>5) break;
        h += c2n(v[i]);
        h *=10;
        count++;
    }
    h/=10;
    printf(" ");
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

string* predict(int input){
    int count=0;
    link t;
    string* ans = malloc(256*sizeof(string));
    
    for (t=tab[input]; t!=NULL; t=t->next) {
        puts(t->obj->chave);
        strcpy(ans[count],t->obj->chave);
        count++;
    }

    return ans;
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

    int input; printf("Type some numbers - "); scanf("%d", &input);
    string* solution = predict(input);


    return 0;
}
