%option noyywrap
%option noinput
%option nounput

%{

#include "token.h"

%}

%%

"print" { return Print; }
":=" { return AsgnOp; }
["]([^\\"]|\\["])*["] { return Str; }
[a-zA-Z_][a-zA-Z0-9_]* { return Id; }

[()] { return *yytext; }

[ \t\n] { }
. {
	fprintf(stderr, "lex error: unknown token %s\n", yytext);
	exit(1);
}

%%

