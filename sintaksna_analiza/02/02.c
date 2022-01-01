#include <stdio.h>
#include <stdlib.h>

#include "token.h"

#define DEBUG

extern int yylex();
extern char* yytext;

void NN(void);
void NNP(void);
void N(void);
void U(void);
void I(void);

int lookahead;

void error(char* msg) {
	fprintf(stderr, "%s\n", msg);
	exit(EXIT_FAILURE);
}

int next_token() {
	int token = yylex();
#ifndef DEBUG
	if(token != EOI) {
		printf("%d\n", token);
	}
#endif
	return token;
}

int main() {

	lookahead = next_token();	

	NN();

	if((lookahead = next_token()) != EOI) {
		error("syntax error: unexpexted symbol after expression");
		exit(EXIT_FAILURE);
	}
	else {
		printf("correct syntax\n");
		exit(EXIT_FAILURE);
	}
	
}

void NN(void) {

	switch(lookahead) {
		
		case WHILE:
		case IF:
		case BEG:
			printf("NN -> N NN'\n");
			N();
			NNP();
			break;
		default:
			error("syntax error: expected while, if, id, begin, end or eof");
			break;
	}
}

void NNP(void) {

	switch(lookahead) {
		
		case WHILE:
		case IF:
		case BEG:
		case ID:
			printf("NN' -> N NN'\n");
			N();
			NNP();
			break;
		case EOI:
		case END:
			printf("NN' -> eps\n");
			break;
		default:
			error("syntax error: expected while, if, id, begin, end or eof");
			break;
	}
}

void N(void) {
	
	switch(lookahead) {
		
		case WHILE:
			printf("N -> while U do N\n");

			lookahead = next_token();
			U();

			if(lookahead != DO) {
				error("syntax error: expected do");
			}
			
			lookahead = next_token();
			N();
			break;
		case IF:
			printf("N -> if U then N\n");

			lookahead = next_token();
			U();

			if(lookahead != THEN) {
				error("syntax error: extected then");
			}
			
			lookahead = next_token();
			N();

			break;
		case BEG:
			printf("N -> begin NN' end\n");

			lookahead = next_token();
			NNP();

			if(lookahead != END) {
				error("syntax error: expected end");
			}
			
			lookahead = next_token();
			break;
		case ID:
			printf("N -> id asgn I;\n");

			lookahead = next_token();
			if(lookahead != ASGN) {
				error("syntax error: expexted asignment");
			}

			lookahead = next_token();
			I();

			if(lookahead != ';') {
				error("syntax error: expexted ;");
			}
			lookahead = next_token();
			break;
	}

}	

void U(void) {
	if(lookahead == '(') {
		
		printf("U -> (I rop I)\n");
		
		lookahead = next_token();
		I();
		
		if(lookahead != ROP) {
			error("syntax error: expexted relational operator");
		}

		lookahead = next_token();
		I();

		if(lookahead != ')') {
			error("syntax error: expexted )");
		}
		lookahead = next_token();	
	}
	else {
		error("syntax error: expected (");
	}
}

void I(void) {
	switch(lookahead) {
		case ID:
			printf("I -> id\n");
			lookahead = next_token();	
			break;
		case NUM:
			printf("I -> num\n");
			lookahead = next_token();	
			break;
	}
}
