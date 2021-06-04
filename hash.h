typedef char *string;
typedef struct {
    string chave;
    int ocorrencias;
} tipoObjeto;

typedef struct STnode *link;
struct STnode {
    tipoObjeto* obj;
    link next;
} STnode;

int c2n(char c);
int hash(string v);
void STinit();
void STinsert(tipoObjeto* obj);
tipoObjeto* STsearch(string v);
string* predict(int input);