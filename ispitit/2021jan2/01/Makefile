run: parser.tab.o lex.yy.o vec.o
	g++ -o $@ $^
lex.yy.o: lex.yy.c parser.tab.hpp 
	g++ -c -o $@ $<
lex.yy.c: lexer.lex
	flex $<
parser.tab.o: parser.tab.cpp
	g++ -c -o $@ $<
parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d -v $<
vec.o: vec.cpp vec.hpp
	g++ -c -o $@ $<

.PHONY: clena

clean:
	rm -rf *.tab.* *.yy.* *.o *.output
