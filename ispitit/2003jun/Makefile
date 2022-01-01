run: parser.tab.o lex.yy.o matrica.o
	g++ -Wall -o $@ $^
parser.tab.o: parser.tab.cpp matrica.hpp
	g++ -c -Wall -o $@ $<
parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d -v $<
lex.yy.o: lex.yy.c parser.tab.hpp
	g++ -c -Wall -o $@ $<
lex.yy.c: lexer.lex
	flex $<
matrica.o : matrica.cpp matrica.hpp
	g++ -Wall -o $@ -c $<


.PHONY: clean

clean:
	rm -f *.tab.* *.yy.* *.o *.output
