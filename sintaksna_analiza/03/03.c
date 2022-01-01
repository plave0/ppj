#include <stdio.h>
#include <stdlib.h>

#include "token.h"

#define MAX_STACK (256)
#define DEBUG

// State macroes

#define E	(300)
#define EP	(301)
#define T	(302)
#define TP	(303)
#define F	(304)

// External linking
//
extern int yylex();
extern char* yytext;

int lookahead = 0;
int stack[MAX_STACK];
int sp = 0;

// Useful functions

void error(char* msg) {
	fprintf(stderr, "%s\n", msg);
	exit(EXIT_FAILURE);
}

void next_token() {
	lookahead = yylex();
#ifdef DEBUG
	printf("%d\n", lookahead);
#endif
}

int match(int x) {
	return x == lookahead;
}

// Stack functions

int empty() {
	return sp == 0;
}

int full() {
	return sp >= MAX_STACK;
}

void pop() {
	if(empty()) {
		error("stack underflow");
	}
	sp -= 1;
}

int top() {
	if(empty()) {
		error("stack empty");
	}
	return stack[sp - 1];
}

void push(int x) {
	if(full()) {
		error("stack overflow");
	}
	stack[sp] = x;
	sp += 1;
}

// Main program

int main() {
	
	next_token();
	push(E);

	while(!empty()) {

		switch(top()) {

			case E:
				if(match('(') || match(NUM)) {
					
					printf("E -> TE'\n");
					pop();
					push(EP);
					push(T);
				}
				else {
					error("syntax error: NUM or ( expected");
				}
				break;
			case EP:
				if(match('+')) {

					printf("E' -> +TE'\n");
					pop();
					push(EP);
					push(T);
					push('+');
				}
				else if(match(')') || match(EOI)) {

					printf("E' -> eps\n");
					pop();
				}
				else {
					error("syntax error: +, ), or EOI expected");
				}
				break;
			case T:
				if(match('(') || match(NUM)) {
					
					printf("T -> FT'\n");
					pop();
					push(TP);
					push(F);
				}
				else {
					error("syntax error: NUM or ( expected");
				}
				break;
			case TP:
				if(match('*')) {

					printf("T' -> *FT'\n");
					pop();
					push(TP);
					push(F);
					push('*');
				}
				else if(match('+') || match(')') || match(EOI)) {

					printf("T' -> eps\n");
					pop();
				}
				else {
					error("syntax error: *, +, ), or EOI expected");
				}
				break;
			case F:
				if(match(NUM)) {
					
					printf("F -> num\n");
					pop();
					push(NUM);
				}
				else if(match('(')) {

					printf("F -> (E)\n");
					pop();
					push(')');
					push(E);
					push('(');
				}
				else {
					error("syntax error: expexted ( or NUM");
				}
				break;
			default:
				if(match(top())) {
					pop();
					next_token();
				}
				else {
					error("syntax error: unexpected token");
				}
		}
	}

	if(match(EOI)) {
		printf("correct syntax\n");
	}
	else {
		error("syntax error: unexpexted token");
	}

	return 0;
		
}
