%option noyywrap
%option noinput
%option nounput

%{
#include <iostream>
#include <cstdlib>

using namespace std;

#include "parser.tab.hpp"
%}

%%
[0-9]* { 
	yylval.num = atoi(yytext);
	return Num;
}

"print" { return Print; }
"lower" { return Lower; }
"upper" { return Upper; }
"reverse" { return Reverse; }
"index" { return Index; }
":=" { return AsgnOp; }

[a-zA-Z_][a-zA-Z0-9_]* {
	yylval.s = new string(yytext);
	return Id;
}

["]([^\\"]|\\["]|\\n|\\t)*?["] {
	string* str = new string("");
	int pt = 1;
	while(yytext[pt] != '\0') {
		if(yytext[pt] == '"' and yytext[pt-1] != '\\') {}
		else if(yytext[pt] == '\\') {}
		else if((yytext[pt]=='n' || yytext[pt]=='N') and yytext[pt-1]=='\\') {
			str->push_back('\n');
		}
		else if((yytext[pt]=='t' || yytext[pt]=='T') and yytext[pt-1]=='\\') {
			str->push_back('\t');
		}
		else { str->push_back(yytext[pt]); }
		pt += 1;
	}
		
	yylval.s = str;
	return Str;
}

[\n()+*\[\]:,|] { return *yytext;}
[ \t] { }

. {
	cerr << "lex error: unknown token " << yytext << endl;
	exit(1);
}
%%
