#include <stdio.h>
#include <stdlib.h>

#include "token.h"

#define _debug 1
#define _max_stack 256

#define P (300)
#define L (301)
#define Ve1 (302)
#define Ve1P (303)
#define Ve2 (304)
#define Ve3 (305)
#define V (306)

int lookahead;
extern int yylex();

void error(char* msg) {
	fprintf(stderr, "syntax error: %s\n", msg);
	exit(1);
}

void debug(char* from, char* to) {
#ifdef _debug
	printf("%s -> %s\n", from , to);
#endif
}

int match(int token) {
	return token == lookahead;
}

void next_token() {
	lookahead = yylex();
	if(lookahead >= 0 && lookahead <=255)
		printf("next token: %c\n", lookahead);
	else
		printf("next token: %d\n", lookahead);

}

int stack[_max_stack];
int sp = 0;

int empty() {
	return sp == 0;
}

int full() {
	return sp == _max_stack;
}

int push(int x) {
	if(full()) 
		error("stack overflow");
	stack[sp] = x;
	sp += 1;
}

int top() {
	if(empty())
		error("stack undeflow");
	return stack[sp-1];
}

int pop() {
	if(empty())
		error("stack underflow");
	sp -= 1;
}

int main() {
	
	next_token();
	printf("%d\n", lookahead);
	push(P);
	
	while(!empty()) {
		
		switch(top()) {
			case P :
				if(match(Print) || match(Id)) {

					debug("P", "L ; P");
					pop();
					
					push(P);
					push(';');
					push(L);
				}
				else if (match(Eof)) {

					debug("P", "eps");
					pop();
				}
				else error("expected Print or Id token");
				break;
			case L :
				if(match(Id)) {
					debug("L", "Id := Ve1");
					pop();

					push(Ve1);
					push(AsgnOp);
					push(Id);
				}
				else if(match(Print)) {
					debug("L", "Print ( Ve1 )");
					pop();

					push(')');
					push(Ve1);
					push('(');
					push(Print);
				}
				else error("could not reduce L");
				break;
			case Ve1: 
				if(match('-') || match('(') || match(Def) || match(Id)) {
					debug("Ve1", "Ve2 Ve1'");
					pop();

					push(Ve1P);
					push(Ve2);
				}
				else error("could not reduce Ve1");
				break;
			case Ve1P:
				if(match('+')) {
					debug("Ve1'", "+ Ve2 Ve1P");
					pop();

					push(Ve1P);
					push(Ve2);
					push('+');
				}
				else if(match('-')) {
					debug("Ve1'", "- Ve2 Ve1P");
					pop();

					push(Ve1P);
					push(Ve2);
					push('-');
				}
				else if(match(')') || match(';')) {
					debug("Ve1'", "eps");
					pop();
				}
				else error("could not resolve Ve1'");
				break;
			case Ve2:
				if(match('-')) {
					debug("Ve2", "-Ve2");
					pop();

					push(Ve2);
					push('-');
				}
				else if(match(Def) || match(Id) || match('(')) {
					debug("Ve2", "Ve3");
					pop();

					push(Ve3);
				}
				else error("could not reduce Ve2");
				break;
			case Ve3:
				if(match('(')) {
					debug("Ve3", "( Ve1 )");
					pop();

					push(')');
					push(Ve1);
					push('(');
				}
				else if(match(Id)) {
					debug("Ve3", "Id");
					pop();

					push(Id);
				}
				else if(match(Def)) {
					debug("Ve3", "V");
					pop();

					push(V);
				}
				else error("could not reduce Ve3");
				break;
			case V:
				if(match(Def)) {
					debug("V", "Def(<num,num>,<num,num>)");
					pop();

					push(')');
					push('>');
					push(Num);
					push(',');
					push(Num);
					push('<');
					push(',');
					push('>');
					push(Num);
					push(',');
					push(Num);
					push('<');
					push('(');
					push(Def);
				}
				else error("could not reduce V");
				break;
			default:
				if(match(top())) {
					pop();
					next_token();
				}
				else error("unexpected token");
		}
	}

	if(!match(Eof)) {
		error("unexpected token at the end");
	}
	return 0;
}
