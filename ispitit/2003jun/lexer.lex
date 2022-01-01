%option noyywrap
%option noinput
%option nounput

%{

#include <iostream>
#include <cstdlib>
#include <vector>

#include "matrica.hpp"

using namespace std;

#include "parser.tab.hpp"
%}

%%
[0-9]+("."[0-9]+)? {
	yylval.d = atof(yytext);
	return NUM;
}
[a-zA-Z_][a-zA-Z_0-9]* {
	yylval.s = new string(yytext);
	return ID;
}
".*" {
	return PM_TOKEN;
}
[\[\];=\n+*'-] {
	return *yytext;
}
[ \t] { }

. {
	cerr << "lexer error: unknown symbol \"" << yytext << "\"" << endl;
	exit(EXIT_FAILURE);
}
%%
