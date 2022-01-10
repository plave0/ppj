run: lex.yy.o parser.o
	gcc -Wall -o $@ $^
lex.yy.o: lex.yy.c
	gcc -Wall -c -o $@ $^
lex.yy.c: lexer.lex
	flex $<
parser.o: parser.c
	gcc -Wall -c -o $@ $<

.PHONY:clean

clean: 
	rm -rf *.o run
