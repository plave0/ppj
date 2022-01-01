run: lex.yy.o 02.o
	gcc -Wall -o $@ $^
lex.yy.o: lex.yy.c token.h
	gcc -Wall -c -o $@ $<
lex.yy.c: 02.lex
	flex $<
02.o: 02.c token.h
	gcc -Wall -c -o $@ $<

.PHONY: clean

clean: 
	rm -f *~ *.o lex.yy.*
