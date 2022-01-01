%option noyywrap
%option noinput
%option nounput

%{
#include "token.h"
%}


%%

"while" { return WHILE;}
"if" { return IF; }
"begin" { return BEG;}
"then" { return THEN; }
"do" { return DO; }
"end" { return END; }
":=" { return ASGN; }

"<="|">="|"!="|[<>] { return ROP; }
[0-9]+ { return NUM;}
[();] { return *yytext; }
[a-zA-Z]+ { return ID; }

[ \t\n] { }

%%

