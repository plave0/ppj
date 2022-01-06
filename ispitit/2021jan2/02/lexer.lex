%option noyywrap
%option noinput
%option nounput

%{
#include <stdio.h>
#include "token.h"
%}

%%

("+"|"-")?(0|[1-9][0-9]*)("."[0-9]*)? { return Num; }

"print" { return Print; }
"def" { return Def; }
":=" { return AsgnOp; }

[;,<>()+-] { return *yytext; }

[a-zA-Z_][a-zA-Z0-9_]* { return Id; }

[ \t\n] { }

. {
	fprintf(stderr, "lexer error: unknow token %s\n", yytext);
	exit(1);
}

%%

