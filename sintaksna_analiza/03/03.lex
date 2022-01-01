%option noyywrap
%option noinput
%option nounput

%{
#include "token.h"
%}

%%

[0-9]+ {

	//naisli smo na broj
	return NUM;
}

[()+*] {

	//naisli smo na neki od navedenih karaktera
	// token je ASCII kod ovih simbola
	return *yytext;
}

[ \t] {
	
	// ingorisemo beline
}

\n {
	// kraj unosa
	return EOI;
}

. {
	// doslo je do greske
	fprintf(stderr, "Nije prepoznat simbol: %s\n", yytext);
	exit(EXIT_FAILURE);	
}	

%%
