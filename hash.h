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

