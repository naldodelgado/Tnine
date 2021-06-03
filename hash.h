typedef char *string;
typedef struct {
    string chave;
    int ocorrencias;
} tipoObjeto;

typedef struct STnode *link;
struct STnode {
    tipoObjeto obj;
    link next;
} STnode;

int hash(string v);
void STinit();
void STinsert(tipoObjeto obj);
tipoObjeto STsearch(string v);