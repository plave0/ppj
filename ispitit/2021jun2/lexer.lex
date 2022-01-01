%option noyywrap
%option noinput
%option nounput

%{

#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;

#include "parser.tab.hpp"

%}

%%
[0-9]+ { 
	yylval.node_id = atoi(yytext);
	return NodeId; 
}
"graph" { return GraphType; }
"print" { return Print; }
"edges" { return Edges; }
"vertices" { return Vertices; }
"union" { return Union; }
"intersect" { return Intersect; }
"difference" { return Difference; }
"complement" { return Complement; }
"is_graph" { return IsGraph; }
"is_undirected" { return IsUndirected; }
"is_connected" { return IsConnected; }
[;=()\[\],] { return *yytext; }
[a-zA-Z]+ { return Id; }
[ \t\n] { }
. {
	cerr << "lexer error: token unknow " << yytext << endl;
	exit(EXIT_FAILURE);
}

%%
