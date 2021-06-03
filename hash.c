#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hash.h"
#include "input.c"


char stringvazia[1] = {'\0'};
tipoObjeto objetonulo = {stringvazia,0};

#define M 262139

link tab[M];

int hash(string v) {
    int i, h=v[0];
    for (i=1; v[i]!='\0'; i++)
        h = (h*251+v[i]) % M;
     //printf("%d ",h);
    if (h<0) return 0;
    return h;
}

// char verify_char(uint ch) {
//     if (ch>=0x00E0 && ch<=0x00E5) return 'a';
//     if (ch==0x00E7) return 'c';
//     if (ch>=0x00E8 && ch<=0x00EB) return 'e';
//     if (ch>=0x00EC && ch<=0x00EF) return 'i';
//     if (ch>=0x00F2 && ch<=0x00F6) return 'o';
//     if (ch>=0x00F9 && ch<=0x00FC) return 'u';
//     else return ch;
// }

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
        link novo = malloc(sizeof(STnode));
        novo->obj = obj;
        novo->next = tab[h];
        tab[h] = novo;
    }
}

tipoObjeto STsearch(string v) {
    link t;
    int h = hash(v);
    printf("%d ",h);
    for (t=tab[h]; t!=NULL; t=t->next){
        if (strcmp(t->obj.chave,v)==0) break;
    }
    if (t!=NULL) return t->obj;
    // puts("ok");
    return objetonulo;
}

int main(int argc, char* argv[]) {
    FILE *fp;
    fp = fopen(argv[1],"r");
    char *w = malloc(256*sizeof(char));
    STinit();
    while (fscanf(fp,"%s",w)!=EOF) {
        if (w[strlen(w)-1]==',' || w[strlen(w)-1]=='.' || w[strlen(w)-1]=='!' || w[strlen(w)-1]=='?' || w[strlen(w)-1]==')')
            w[strlen(w)-1] = '\0';
        
        tipoObjeto t = STsearch(w);
        if(!strcmp(t.chave,objetonulo.chave)){
            tipoObjeto aux = {w,1};
            STinsert(aux);
        }
        else STinsert(t);
        printf("%s -> %d\n", w, t.ocorrencias);
        
    }
    
    fclose(fp);
    puts("DONE READING FILE");

    tipoObjeto teste = STsearch("sorte");
    printf("%d %s\n",teste.ocorrencias, teste.chave);

    // int hv = hash("sorte");
    // link t;
    // for(t = tab[hv]; t!=NULL; t=t->next){
    //     printf("%d %s\n",t->obj.ocorrencias, t->obj.chave);
    // }

    // int input;
    // scanf("%d",&input);
    // string* possibilities = malloc(256*sizeof(string));
    // possibilities =  predict(input);
    return 0;
}
