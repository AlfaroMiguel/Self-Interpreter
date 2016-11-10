%{
	#include <cstdio>
	#include <cstdlib>
	#include <string>
	#include <map>
	#include "interpreter.h"
	#include <iostream> //cout
	using namespace std;
	map<string,double > vars ; // map from variable name to value
	extern int yylex ();
	extern void yyerror(const char *);
	void Div0Error(void);
	void UnknownVarError ( string s );
%}
%union{
	int int_val ;
	double double_val ;
  string* str_val;
}
%start parse
%define parse.error verbose
%token <int_val> PLUS MINUS ASTERISK FSLASH EQUALS PRINT LPAREN RPAREN SEMICOLON
EQUALSMUTAL SET BAR ADD RM CREATEOBJECTINIT CREATEOBJECTEND ARGS WORD COMMENT
%token <str_val> VARIABLE
%token <double_val> NUMBER
%type <double_val> expression;
%type <double_val> argument;
//%type <int_val> operation;
//%type <double_val> expresion_method;
//%type <double_val> line_method;
%type <double_val> atom_expression;
%type <double_val> inner1 ;
%type <double_val> inner2 ;
%{
Interpreter interpreter;
%}
%%
parse:	lines;

lines:		lines line
					{
					//std::cout << "ap" <<std::endl;
					}
					|line
					{
					//std::cout << "apa" <<std::endl;
					}
					;

line :
		PRINT expression SEMICOLON {
		interpreter.pushToken("","print","");
		}
		|CREATEOBJECTINIT lines CREATEOBJECTEND
		{
		interpreter.pushToken("","encapsulate","");
		}
		|VARIABLE ADD line SEMICOLON
		{
		interpreter.pushToken(*$1,"add","");
		}
		|VARIABLE RM line SEMICOLON
		{
		interpreter.pushToken("","remove","");
		interpreter.pushToken(*$1,"find","");
		}
		|VARIABLE EQUALS lines SEMICOLON
		{
		interpreter.pushToken((*$1),"assignation","");
		//vars[*$1] = $3;delete $1;
		}
		|CREATEOBJECTINIT argument BAR expression SEMICOLON RPAREN
		{
		std::cout << "(| :args | procedimiento)" <<std::endl;
		}
		|atom_expression{
		std::cout << "atom:_expression)" <<std::endl;
		}
		|VARIABLE VARIABLE SEMICOLON{
		std::cout << "objeto metodo." <<std::endl;
		/*Lo busco y lo guardo en el stack*/
		interpreter.pushToken(*$1,"find","");
		/*Le mando el mensaje siguiente*/
		interpreter.pushToken("",*$2,"");
		}
		|expression{
		std::cout << "Parser::expression" <<std::endl;
		}
		;


argument:/*nada*/
				{
				std::cout << "un argumento vacio" <<std::endl;
				}
				|ARGS
				{
				std::cout << "un argumento no vacio" <<std::endl;
				}
				;

line_method:
		expresion_method operation line_method
		|expresion_method
		;

expresion_method:
		VARIABLE operation NUMBER
		{
		std::cout << "variable *+/- number" <<std::endl;
		}
		|VARIABLE operation VARIABLE
		{
		std::cout << "variable *+/- variable" <<std::endl;
		//esto es redundante porque un atom_expression tiene la misma pinta, tengo que generalizar los atom_expression
		}
		|NUMBER operation NUMBER
		{
		std::cout << "number *+/- number" <<std::endl;
		}
		|NUMBER
		{
		std::cout << "number" <<std::endl;
		}
		;

operation:
		PLUS {
		std::cout << "+" <<std::endl;
		}
		|MINUS {
		std::cout << "-" <<std::endl;
		}
		|ASTERISK {
		std::cout << "*" <<std::endl;
		}
		|FSLASH {
		std::cout << "/" <<std::endl;
		}
		;

atom_expression:
							VARIABLE SEMICOLON
							{
							interpreter.pushToken((*$1),"assignation","");
							}
							|VARIABLE EQUALSMUTAL expression SEMICOLON {
							interpreter.pushToken(*$1,"assignation_mutable","");
							}
							|VARIABLE SET expression SEMICOLON{
							interpreter.pushToken(*$1,"find","");
							interpreter.pushToken("","set","");
							}
							|VARIABLE PLUS VARIABLE SEMICOLON
							{
							interpreter.pushToken(*$3,"find","");
							interpreter.pushToken("","+","");
							interpreter.pushToken(*$1,"find","");
							}
							|VARIABLE MINUS VARIABLE SEMICOLON
							{
							interpreter.pushToken(*$3,"find","");
							interpreter.pushToken("","-","");
							interpreter.pushToken(*$1,"find","");
							}
							|VARIABLE ASTERISK VARIABLE SEMICOLON
							{
							interpreter.pushToken(*$3,"find","");
							interpreter.pushToken("","*","");
							interpreter.pushToken(*$1,"find","");
							}
							|VARIABLE FSLASH VARIABLE SEMICOLON
							{
							interpreter.pushToken(*$3,"find","");
							interpreter.pushToken("","/","");
							interpreter.pushToken(*$1,"find","");
							}
							|ARGS
							{
							std::cout << "ARGS"<<std::endl;
							}
							;

expression: 	expression PLUS inner1
							{
							//$$ = $1 + $3 ;
							interpreter.pushToken("","+","");
								}
						| expression MINUS inner1 {
						//std::cout << "$$ = $1 - $3" <<std::endl;
						interpreter.pushToken("","-","");
						 //$$ = $1 - $3 ;
						 }
						| inner1 { $$ = $1 ;};

inner1: 	inner1 ASTERISK inner2 {
		//std::cout << "$$ = $1 * $3" <<std::endl;
		interpreter.pushToken("","*","");
 		//$$ = $1 * $3 ;
		}
		|inner1 FSLASH inner2{
		//std::cout << "$$ = $1 / $3" <<std::endl;
		interpreter.pushToken("","/","");
		if( $3 == 0) Div0Error (); else $$ = $1 / $3 ;}
		|inner2 { $$ = $1 ;};

inner2:
		VARIABLE {
		interpreter.pushToken(*$1,"find","");
		if (! vars . count (* $1 ))
				//UnknownVarError (* $1 );
				std::cout << "la letra no se guardó" <<std::endl;
		else
			$$ = vars [* $1 ];
			//delete $1 ;
			std::cout << "VARIABLE" <<std::endl;
			}
		|NUMBER
		{
		//std::cout << "VARIABLE" <<std::endl;
		interpreter.pushToken("","create_number",to_string($1));
		//$$ = $1 ;
		}
		|LPAREN expression RPAREN {
		//$$ = $2 ;
		}
		;
%%
void Div0Error ( void ) { printf (" Error : division by zero \n"); exit (0);}
void UnknownVarError ( string s ) { printf (" Error : -%s- does not exist !\n", s . c_str ()); exit (0);}
