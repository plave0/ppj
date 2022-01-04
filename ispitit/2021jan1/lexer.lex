%option noyywrap
%option noinput
%option nounput

%{

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

#include "angle.hpp"
#include "parser.tab.hpp"

%}

%%
[0-9]+ { 
	yylval.num = atoi(yytext);
	return Num;
}
[\[\]=<>,();+*-] {
	return *yytext;
}
[ \t\n] { 
	// no action 
}

"print" { return Print; }

[a-z][a-z1-9]* {
	yylval.id = new string(yytext);
	return AngleId;
}
[A-Z]+ {
	yylval.id = new string(yytext);
	return ListId;
}
. {
	cerr << "lex error" << endl;
	exit(EXIT_FAILURE);
}
%%
