run: lex.yy.o parser.tab.o
	g++ -o $@ $^
lex.yy.o: lex.yy.c parser.tab.hpp
	g++ -c -o $@ $<
lex.yy.c: lexer.lex
	flex $<
parser.tab.o: parser.tab.cpp
	g++ -c -o $@ $<
parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d $<	
	
.PHONY: clean

clean: 
	rm -rf *.o *.output *.tab.* *.yy.*
