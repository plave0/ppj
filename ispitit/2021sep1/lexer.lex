%option noyywrap
%option noinput
%option nounput

%{
#include <iostream>
#include <string>
#include <vector>

#include "mat.hpp"

using namespace std;

#include "parser.tab.hpp"
%}

%%
[0-9]+("."[0-9]+)? {
	yylval.d = atof(yytext);
	return Num;
}
[\[\];,()+*-] {
	return *yytext;
}
"array" { return Array; }
":=" { return Asgn; }
"==" { return Eq; }
"print" { return Print; }
"reshape" { return Reshape; }
"count" { return Count; }
"link" { return Link; }
"fork" { return Fork; }
"subarray" { return Subarray; }
"sum" { return Sum; }
"lenght" { return Length; }
[ \t\n] { }
[a-zA-Z]+ { return Id; }
. {
	cerr << "lexer error: undefined token " << yytext << endl;
	exit(EXIT_FAILURE);
}
%%
