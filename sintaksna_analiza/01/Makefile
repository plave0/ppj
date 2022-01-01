run: lex.yy.o 01.o
	gcc -Wall -o $@ $^
lex.yy.o: lex.yy.c token.h
	gcc -Wall -c -o $@ $<
lex.yy.c: 01.lex
	flex $<
01.o: 01.c token.h
	gcc -Wall -c -o $@ $<

.PHONY: clean

clean: 
	rm -f *~ *.o lex.yy.*
