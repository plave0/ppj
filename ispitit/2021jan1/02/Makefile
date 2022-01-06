run: lex.yy.o parser.o
	gcc -o $@ $^
lex.yy.o: lex.yy.c token.h
	gcc -c -o $@ $<
lex.yy.c: lexer.lex
	flex $<
parser.o: parser.c token.h
	gcc -c -o $@ $<
