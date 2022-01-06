#include <stdio.h>
#include <stdlib.h>

#include "token.h"

#define _debug (1)

extern int yylex();
int lookahead;

void P();
void L();
void Ae1();
void Ae1P();
void Ae2();
void Ae2P();
void Ae3();
void Ae4();
void A();

void error(char* msg) {
	fprintf(stderr, "syntax error: %s\n", msg);
	exit(EXIT_FAILURE);
}

void next_token() {
	lookahead = yylex();
}

void debug(char* from, char* to) {
#ifdef _debug
	printf("%s -> %s\n", from, to);
#endif
}

void P() {
	switch(lookahead) {
		case Id:
		case Print:
			debug("P", "L ; P");

			L();

			if(lookahead != ';') error("expected ; token");
			next_token();

			P();

			break;
		case Eof:
			debug("P", "eps");
			break;
		default:
			error("expexted Id, Print or Eof token");
			exit(EXIT_FAILURE);
	}
}

void L() {
	switch(lookahead) {
		case Id:
			debug("L", "Id = Ae1");
			
			next_token();
			if(lookahead != '=') error("expected = token");
			next_token();

			Ae1();

			break;
		case Print:
			debug("L", "Print ( Ae1 )");

			next_token();
			if(lookahead != '(') error("expected ( token");
			next_token();

			Ae1();

			if(lookahead != ')') error("expected ) token");
			next_token();

			break;
		default:
			error("expexted Id, Print or Eof token");
			exit(EXIT_FAILURE);
	}
}

void Ae1() {
	switch(lookahead) {
		case Num:
		case '<':
		case '(':
		case Id:
			debug("Ae1", "Ae2 Ae1'");
			Ae2();
			Ae1P();
			break;
		default:
			error("expected Num, Id, < or ( token");
			exit(EXIT_FAILURE);
	}
}

void Ae1P() {
	switch(lookahead) {
		case '+':
		case '-':
			debug("Ae1'", "+-Ae2 Ae1'");

			next_token();

			Ae2();
			Ae1P();
			break;
		case ')':
		case ';':
			debug("Ae1'", "eps");
			break;
		default:
			error("expected +, -, ) or ; token");
	}
}

void Ae2() {
	switch(lookahead) {
		case Num:
		case '<':
		case '(':
		case Id:
			debug("Ae2", "Ae3 Ae2'");
			Ae3();
			Ae2P();
			break;
		default:
			error("expected Num, Id, ( or < token");
	}
}

void Ae2P() {
	switch(lookahead) {
		case '*':
			debug("Ae2'", "* Num Ae2'");

			next_token();
			if(lookahead != Num) error("expected Num token");
			next_token();

			Ae2P();
			
			break;
		case '+':
		case '-':
		case ')':
		case ';':
			debug("Ae2'", "eps");
			break;
		default:
			error("expected ");
	}
}

void Ae3() {
	switch(lookahead) {
		case Num:
			debug("Ae3", "Num * Ae4");

			next_token();
			if(lookahead != '*') error("expected * token");
			next_token();

			Ae4();

			break;
		case '<':
		case '(':
		case Id:
			debug("Ae3", "Ae4");
			Ae4();
			break;
		default:
			error("expected Num, Id, < or ( token");
			exit(EXIT_FAILURE);
	}
}

void Ae4() {
	switch(lookahead) {
		case '(':
			debug("Ae4", "( Ae1 )");

			next_token();

			Ae1();

			if(lookahead != ')') error("expected ) token");			
			next_token();

			break;
		case Id:
			debug("Ae4", "Id");
			next_token();
			break;
		case '<':
			debug("Ae4", "A");
			A();
			break;
		default:
			error("expected (, < or Id token");
	}
}
void A() {
	switch(lookahead) {
		case '<':
			next_token();
			if(lookahead != Num) error("expected Num token");
			next_token();
			if(lookahead != ',') error("expected , token");
			next_token();
			if(lookahead != Num) error("expected Num token");
			next_token();
			if(lookahead != ',') error("expected , token");
			next_token();
			if(lookahead != Num) error("expected Num token");
			next_token();
			if(lookahead != '>') error("expected > token");
			next_token();
			break;
		default:
			error("expected < token");
	}
}

int main() {

	next_token();
	P();

	return 0;
}
