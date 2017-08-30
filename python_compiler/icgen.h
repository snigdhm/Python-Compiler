#include <stdbool.h>
#include <stdio.h>


typedef struct CodeLine
{
    char *code;
    
    int gotoL;

    struct CodeLine *next;
    
}  Code;

typedef struct _BackpatchList
{
    Code *entry;

    struct _BackpatchList *next;

}  BackpatchList;

Code *genquad(char *code);
void backpatch(BackpatchList* list, int gotoL);
BackpatchList* mergelists(BackpatchList* a, BackpatchList* b);
BackpatchList* addToList(BackpatchList* list, Code* entry);
bool printCode(FILE *outputFile);
char* nextIntVar();
char* nextStringVar();
int nextquad();

