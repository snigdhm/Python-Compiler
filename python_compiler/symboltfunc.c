 #include "hash_stack.c"
 #include<stdio.h>
 int isempty(STACK1 * stack)
 {
     return stack->size == 0;
 }
 void enterScope(STACK1 * stack)
 {
        hashtable_t *ht = ht_create(1024);
	push1(stack,ht);
 }

    /* Exits the most recently entered scope. */
 void exitScope(STACK1 * stack) 
 {
	if (isempty(stack))
        {
	    printf("existScope: can't remove scope from an empty symbol table.");
	}
	pop1(stack);
 }

    /** Adds a new entry to the symbol table.
     *
     * @param id the symbol
     * @param info the data asosciated with id
     * */
 void addId(STACK1 * stack,char id[20], char info[20],int type,int return_type,int offset,int num_param,int i) 
 {
	if (isempty(stack))
        {
	    printf("addId: can't add a symbol without a scope.");
	}
	else
	{
	    hashtable_t *ht= peek1at(stack,i);
	    ht_put(ht,id,id,info,type,return_type,offset,num_param,i);
	}
 }

    /**
     * Looks up an item through all scopes of the symbol table.  If
     * found it returns the associated information field, if not it
     * returns <code>null</code>.
     * 
     * @param sym the symbol
     * @return the info associated with sym, or null if not found
     * */
 int lookup(STACK1 * stack,char sym[20]) 
 {
	//char* info;
	int ret_value;
	if (isempty(stack)) 
	{
	    printf("lookup: no scope in symbol table.");
	}
	int i;
	// I break the abstraction here a bit by knowing that stack is 
	// really a vector...

	for ( i = stack->size - 1; i >= 0; i--)
        {
	    hashtable_t *ht = elementAt(stack,i);
	    ret_value=ht_get(ht,sym);
	    if (ret_value != -1) return ret_value;
	}
	return -1;
 }

    /** 
     * Probes the symbol table.  Check the top scope (only) for the
     * symbol <code>sym</code>.  If found, return the information field.
     * If not return <code>null</code>.
     *
     * @param sym the symbol
     * @return the info associated with sym, or null if not found
     * */
 int probe(STACK1 * stack,char sym[20],int i) 
 {
	if (isempty(stack))
	{
	    printf("lookup: no scope in symbol table.");
	}
	else
	{
	    hashtable_t *ht=peek1at(stack,i);
	    return ht_get(ht,sym);
	}
	return -1;
 }

int probe_num(STACK1 * stack,char sym[20],char type[20], int i) 
 {
	if (isempty(stack))
	{
	    printf("lookup: no scope in symbol table.");
	}
	else
	{
	    hashtable_t *ht=peek1at(stack,i);
	    return ht_getparam(ht,sym,type);
	}
	return -1;
 }
 
 int probetype(STACK1 * stack,char sym[20],char type[20],int i) 
 {
	if (isempty(stack))
	{
	    printf("lookup: no scope in symbol table.");
	}
	else
	{
	    hashtable_t *ht=peek1at(stack,i);
	    return ht_gettype(ht,sym,type);
	}
	return -1;
 }

int probe_ret_type(STACK1 * stack,char sym[20],char type[20],int i) 
 {
	if (isempty(stack))
	{
	    printf("lookup: no scope in symbol table.");
	}
	else
	{
	    hashtable_t *ht=peek1at(stack,i);
	    return ht_get_ret_type(ht,sym,type);
	}
	return -1;
 }
    
    /** Gets the string representation of the symbol table.  
     *
     * @return the string rep
     * */
 void  printSymbol_table(STACK1 * stack,FILE *outputFile)
 {
	// I break the abstraction here a bit by knowing that stack is 
	// really a vector...

	 int ret = fprintf(outputFile, "SYMBOLS\n"
                                  "-----------------------------------\n"
                                  ""
                                  "Name       Type       Int_Typ       Return_Type        Offset/Size   Num_Param       Scope \n"
                                  "----------------------------------------------------------------------------------\n");


	
	int i,j;
	hashtable_t *ht;
	
	for ( i = stack->size - 1, j = stack->size-1; i >= 0; i--, j--)
        {
	    ht=elementAt(stack,i);
	    
	    ht_list_values(outputFile,ht,j);
	   
	}
 }
 



