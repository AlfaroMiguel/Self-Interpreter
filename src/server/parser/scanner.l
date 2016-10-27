%{
	#include <cstdio>
	#include <cstdlib>
	#include <string>
	#include <iostream> //cout
	using namespace std ;
	#include "parser.tab.h" // output of bison on example1.y
	void yyerror(char*);
	int yyparse(void);
%}
%%
[ \t\n]+ 										{}; // do nothing on whitespace
"print" 									{std::cerr<<"[Print] ";return PRINT;}
[a-zA-Z][a-zA-Z0-9]* 			{
													//std::cerr<<"[Variable] ";
													yylval.str_val = new string (yytext);
													return VARIABLE;
													}
[0-9][0-9]*(.[0-9]+)? 		{
													//std::cerr<<"[Number] ";
													yylval.double_val = atof(yytext);
													return NUMBER ;
													}
"=" 					return EQUALS;
"+" 					{std::cerr<<"[Mas] ";return PLUS;}
"-" 					{std::cerr<<"[Menos] ";return MINUS;}
"*" 					return ASTERISK;
"/" 					return FSLASH;
"<-" 					return EQUALSMUTAL;
":" 					return SET;
"(" 					return LPAREN;
")" 					return RPAREN;
"_add" 				{//std::cerr<<"add slots ";
							return ADD;}
"(|" 					{//std::cerr<<"(| ";
							return CREATEOBJECTINIT;}
"|)" 					{//std::cerr<<"|) ";
							return CREATEOBJECTEND;}
"." 					return SEMICOLON;
%%

void yyerror (char * str){
	printf("Parse Error:-%s-\n", str );
}

int yywrap ( void ) { }

int main (int num_args , char ** args ) {
	if( num_args != 2){
		printf (" usage : ./ parser1 filename \n");
		exit (0);
	}
	FILE * file = fopen ( args [1] ,"r");
	if( file == NULL ) { printf (" couldn ’t open %s\n", args [1]); exit (0);}
	yyin = file ; // now flex reads from file
	yyparse();
	fclose(file);
}
