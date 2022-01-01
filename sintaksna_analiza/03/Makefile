run: 03.o lex.yy.o
	gcc -Wall -o $@ $^
lex.yy.o: lex.yy.c token.h
	gcc -Wall -c -o $@ $<
lex.yy.c: 03.lex
	flex $<
03.o: 03.c
	gcc -Wall -c -o $@ $<

.PHONY: clean

clean:
	rm -f *.o lex.yy.*


