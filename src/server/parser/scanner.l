%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string>
	#include "interpreter.h"
	#include <iostream> //cout
	using namespace std ;
	#include "parser.h" // output of bison on example1.y
	//void yyerror( const char*);
	int yyparse(void);
%}
%%
[ \t]+ 										{}; // do nothing on whitespace
[ \n]+ 										{}
"print" 									{return PRINT;}
[a-zA-Z][a-zA-Z0-9]* 			{


													yylval.str_val = new string (yytext);


													return VARIABLE;
													}
":"+[a-zA-Z]*+"." 				{

													yylval.str_val = new string (yytext);
													return ARGS;
													}
[0-9][0-9]*(.[0-9]+)? 		{

													yylval.double_val = atof(yytext);
													return NUMBER;
													}
"=" 											{

													return EQUALS;
													}
"//" 											{

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

void yyerror (Interpreter* interpreter,const char * str)
{
	//printf("Parse Error:-%s-\n", str );
}

int yywrap ( void ) { }
