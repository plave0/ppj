#include <stdio.h>
#include <stdlib.h>

#include "token.h"

int lookahead;
extern int yylex();

void error(char* msg) {
	fprintf(stderr, "syntax error: %s\n", msg);
	exit(1);
}

void next_token() {
	lookahead = yylex();
}

int match(int token) {
	if(token == lookahead) 
		return 1;
	else
		return 0;
}

void Prog();
void Line();
void StrExp();

int main() {
	next_token();
	Prog();
	return 0;
}

void Prog() {
	if(match(Id)||match(Print)) {
		Line();
		Prog();
	}
	else if(match(Eof)) { }
	else error("could not reduce Prog");
}

void Line() {
	if(match(Id)) {
		next_token();
		if(!match(AsgnOp)) error("expected := after Id token");
		next_token();
		StrExp();
	}
	else if(match(Print)) {
		next_token();
		if(!match('(')) error("expected ( after Print token");
		next_token();
		StrExp();
		if(!match(')')) error("expected ) after string expresion");
		next_token();
	}
	else error("could not reduce Line");
}

void StrExp() {
	if(!match(Str)&&!match(Id)) error("could not reduce StrExp");
	else next_token();
}
		
