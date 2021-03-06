typedef enum { typeCon, typeId, typeOpr, typeStr} nodeEnum; 
/* constants */ 
typedef struct { 
    int value;                  /* value of constant */ 
} conNodeType; 
typedef struct { 
    char i[20];                  /* value of constant */ 
} strNodeType; 
/* identifiers */ 
typedef struct { 
    char i[20];                      /* subscript to sym array */ 
} idNodeType; 
/* operators */ 
typedef struct { 
    union{
    int opr;                   /* operator */ 
    char opa[20];
   };
    int nops;                   /* number of operands */ 
    struct nodeTypeTag *op[1];  /* operands, extended at runtime 
*/ 
} oprNodeType; 
typedef struct nodeTypeTag { 
    nodeEnum type;              /* type of node */ 
    union { 
        conNodeType con;        /* constants */ 
        idNodeType id;          /* identifiers */ 
        oprNodeType opr;        /* operators */ 
        strNodeType str;
    }; 
} nodeType; 
extern int sym[26]; 
