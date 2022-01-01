run: 04.tab.o lex.yy.o
	g++ -Wall -o $@ $^
04.tab.o: 04.tab.cpp
	g++ -c -Wall -o $@ $<
04.tab.cpp 04.tab.hpp: 04.ypp
	bison -d -v $<
lex.yy.o: lex.yy.c 04.tab.hpp
	g++ -c -Wall -o $@ $<
lex.yy.c: 04.lex
	flex $<


.PHONY: clean

clean:
	rm -f *.tab.* *.yy.* *.o *.output
