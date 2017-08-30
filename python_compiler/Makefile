make: 
	yacc -d parser_icg.y
	flex tokenizer.l
	gcc lex.yy.c y.tab.c icgen.c
