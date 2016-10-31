%{
	#include <cstdio>
	#include <cstdlib>
	#include <string>
	#include <iostream> //cout
	using namespace std ;
	#include "parser.h" // output of bison on example1.y
	void yyerror( const char*);
	int yyparse(void);
%}
%option c++
%%
[ \t]+ 										{}; // do nothing on whitespace
[ \n]+ 										{}
"print" 									{return PRINT;}
[a-zA-Z][a-zA-Z0-9]* 			{
													//std::cout<<"VARIABLE PAARA";
													yylval.str_val = new string (yytext);
													return VARIABLE;
													}
":"+[a-zA-Z]*+"." 				{
													//std::cerr<<"encontré un argumento";
													//yylval.str_val = new string (yytext);
													return ARGS;
													}
[0-9][0-9]*(.[0-9]+)? 		{
													//std::cerr<<"[Number] ";
													yylval.double_val = atof(yytext);
													return NUMBER;
													}
"=" 											{
													//std::cerr<<"=";
													return EQUALS;
													}
"//" 											{
													std::cerr<<"barra barra";
													return COMMENT;
													}
"+" 					{return PLUS;}
"-" 					{return MINUS;}
"*" 					return ASTERISK;
"/" 					return FSLASH;
"<-" 					return EQUALSMUTAL;
":" 					return SET;
"(" 					return LPAREN;
")" 					{
							//std::cerr<<")";
							return RPAREN;
							}
"_AddSlots:"	{return ADD;}
"_RemoveSlots:"	{return RM;}
"|"						{return BAR;}
"(|" 				 	{
							//std::cerr<<"(| ";
							return CREATEOBJECTINIT;}
"|)" 					{//std::cerr<<"|) ";
							return CREATEOBJECTEND;}
"." 					return SEMICOLON;
							{
							std::cerr<<"No se encontró";
							}
%%

void yyerror (const char * str)
{
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
