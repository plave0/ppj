%option noyywrap
%option noinput
%option nounput

%{
#include "token.h"
%}

%%

[0-9]+ { return Num; }

"print" { return Print; }

[a-z][a-z0-9]* { return Id; }

[;,=<>()+*-] { return *yytext; }

[ \t\n] { }

. {
	fprintf(stderr, "lex error: unknown token %s\n", yytext);
	exit(EXIT_FAILURE);
}

%%
