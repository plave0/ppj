// Implementacija rekurzivnog spusta za prepoznavanje gramatiku algebarskih izraza

#include <stdio.h>
#include <stdlib.h>

#include "token.h"

extern int yylex();
extern char* yytext;

int lookahead = 0;

// Neterminali gramatike
void e();
void ep();
void t();
void tp();
void f();

// Pomocne funkcije
void error(char* msg) {
	fprintf(stderr, "%s\n", msg);
	exit(EXIT_FAILURE);	
}

void debug(char* from, char* to) {
		
	printf("%s -> %s\n", from, to);
}

int main() {

	lookahead = yylex();
	printf("%d\n", lookahead);
	e();

	if(lookahead != EOI) {
		error("Syntax error");
	}
	return 0;
}

void e(void) {

	switch(lookahead){
		case NUM:
		case '(':
			debug("e", "te'");
			t();
			ep();
			break;
		default:
			error("Syntax error: expext NUM or (");
			break;
	}
}

void ep() {
	
	switch(lookahead) {
		case '+':
			debug("e'", "+te'");
			lookahead = yylex();
			printf("%d\n", lookahead);
			t();
			ep();
			break;
		case ')':
		case EOI:
			debug("e'", "eps");
			break;
		default:
			error("Syntax error: expext +, ) or EOI");
			break;
	}
}

void t(void) {

	switch(lookahead){
		case NUM:
		case '(':
			debug("t", "ft'");
			f();
			tp();
			break;
		default:
			error("Syntax error: expext NUM or (");
			break;
	}
}

void tp() {
	
	switch(lookahead) {
		case '*':
			debug("t'", "*ft'");
			lookahead = yylex();
			printf("%d\n", lookahead);
			f();
			tp();
			break;
		case ')':
		case EOI:
		case '+':
			debug("t'", "eps");
			break;
		default:
			error("Syntax error: expext *, ) or EOI");
			break;
	}
}

void f(void) {

	switch(lookahead) {
		case '(':
			lookahead = yylex();
			printf("%d\n", lookahead);
			debug("f", "(e)");
			e();
			if(lookahead != ')') {
				error("Syntax error: expexted )");
			}
			lookahead = yylex();
			printf("%d\n", lookahead);
			break;
		case NUM:
			lookahead = yylex();
			debug("f", "NUM");
			printf("%d\n", lookahead);
			break;
		default:
			error("Syntax error: expected NUM or (");
			break;
	}
}

