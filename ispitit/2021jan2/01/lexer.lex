%option noyywrap
%option noinput
%option nounput

%{
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

#include "vec.hpp"
#include "parser.tab.hpp"
%}

%% 
("+"|"-")?(0|[1-9][0-9]*)("."[0-9]*)? {
	yylval.num = atof(yytext);
	return Num;
}

"print" { return Print; }
":=" { return AsgnOp; }
"def" { return Def; }
"sim" { return Sim; }
"refY" { return RefY; }
"refX" { return RefX; }

[A-Za-z_][A-Za-z0-9]* {
	yylval.id = new string(yytext);
	return Id;
}

[(),<>+*\n-] {
	return *yytext;
}
[ \t] {
	// no action
}
. {
	cerr << "lexer error" << endl;
	exit(EXIT_FAILURE);
}
%%
