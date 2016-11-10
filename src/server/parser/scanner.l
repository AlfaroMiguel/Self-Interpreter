%{
	#include <cstdio>
	#include <cstdlib>
	#include <string>
	#include <iostream> //cout
	using namespace std ;
	#include "parser.tab.h" // output of bison on example1.y
	//void yyerror( const char*);
	int yyparse(void);
%}
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
