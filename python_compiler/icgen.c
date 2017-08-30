#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include "icgen.h"
#include "y.tab.h"

Code *LineHead = NULL, *LineTail = NULL;

extern int yylineno;
extern int yyin;
unsigned int newTempVar = 0;
unsigned int newStringVar = 0;
int currentLine = -1;


Code *genquad(char *code){
	
	Code* newCodeLine = malloc(sizeof(Code));
	newCodeLine->code = strdup(code);
	newCodeLine->next = NULL;
	newCodeLine->gotoL = -1;
	if(LineHead == NULL){
		LineHead = newCodeLine;
		LineTail = newCodeLine;
	}
	else{
		LineTail->next = newCodeLine;
		LineTail = newCodeLine;
	}
	currentLine++;
	return newCodeLine;
}

void backpatch(BackpatchList* list, int gotoL){
	
	if(list == NULL){
		return;
	} else{
		BackpatchList* temp;
		while(list){
			if(list->entry != NULL){
				list->entry->gotoL = gotoL;
			}
			
			temp = list;
			list = list->next;
			free(temp);
		}
	}
}

BackpatchList* mergelists(BackpatchList* a, BackpatchList* b){
	
	fflush(stdout);
	if(a != NULL && b == NULL){
		return a;
	}
	else if(a == NULL && b != NULL){
		return b;
	}
	else if(a == NULL && b == NULL){
		return NULL;
	}
	else{
		BackpatchList* temp = a;
		while(a->next){
			a = a->next;
		}
		a->next = b;
		return temp;
	}
}

BackpatchList* addToList(BackpatchList* list, Code* entry){
	
	if(entry == NULL){
		return list;
	}
	else if(list == NULL){
		BackpatchList* newEntry = malloc(sizeof(BackpatchList));
		newEntry->entry = entry;
		newEntry->next = NULL;
		return newEntry;
	}
	else{
		BackpatchList* newEntry = malloc(sizeof(BackpatchList)), *temp = list;
		newEntry->entry = entry;
		newEntry->next=NULL;
		while(list->next){
			list = list->next;
		}
		list->next = newEntry;
		return temp;
	}
}


bool printCode(FILE *outputFile)
{
    Code *codeLine = LineHead;

    if(codeLine == NULL)
    {
        return false;
    }

    unsigned long lineNumber = 0;

    if(fprintf(outputFile, "\n\nCODE\n----\n\n") <= 0)
    {
	return false;
    }

    while(codeLine)
    {
    	int ret;
    	//No goto
    	if(codeLine->gotoL == -1){
    		ret = fprintf(outputFile, "%-4lu %s\n", lineNumber, codeLine->code);
    	}
    	//goto
    	else{
    		ret = fprintf(outputFile, "%-4lu %s %d\n", lineNumber, codeLine->code, codeLine->gotoL);
    	}
        if(ret <= 0)
        {
		return false;
        }

        codeLine = codeLine->next;
        ++lineNumber;
    }

    return true;
}



char* nextIntVar(){
    char buffer[10];
    sprintf(buffer,"i_%d",++newTempVar);
   
    return strdup(buffer);
}

char* nextStringVar(){
    char buffer[10];
    sprintf(buffer,"s_%d",++newStringVar);
    
    return strdup(buffer);
}

int nextquad(){
	return currentLine + 1;
}


