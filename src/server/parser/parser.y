%{
	#include <cstdio>
	#include <cstdlib>
	#include <string>
	#include <map>
	#include "tokenizer.h"
	#include <iostream> //cout
	using namespace std ;
	map<string,double > vars ; // map from variable name to value
	extern int yylex ();
	extern void yyerror (const char *);
	void Div0Error ( void );
	void UnknownVarError ( string s );
%}
%union{
	int int_val ;
	double double_val ;
	string* str_val ;
}
%start parse
%define parse.error verbose
%token <int_val> PLUS MINUS ASTERISK FSLASH EQUALS PRINT LPAREN RPAREN SEMICOLON
EQUALSMUTAL SET BAR ADD RM CREATEOBJECTINIT CREATEOBJECTEND ARGS WORD
%token <str_val> VARIABLE
%token <double_val> NUMBER
%type <double_val> expression;
%type <int_val> operation;
%type <double_val> expresion_method;
%type <double_val> line_method;
%type <double_val> atom_expression;
%type <double_val> inner1 ;
%type <double_val> inner2 ;
%{
Tokenizer tokenizer;
%}
%%
parse:	lines;

lines:		lines line
					|line
					;

line :
		PRINT expression SEMICOLON {
		tokenizer.pushToken("","print","");
		}
		|CREATEOBJECTINIT lines CREATEOBJECTEND
		{
		tokenizer.pushToken("","encapsulate","");
		}
		|VARIABLE ADD line SEMICOLON
		{
		tokenizer.pushToken("","add","");
		tokenizer.pushToken(*$1,"find","");
		}
		|VARIABLE RM line SEMICOLON
		{
		tokenizer.pushToken("","remove","");
		tokenizer.pushToken(*$1,"find","");
		}
		|VARIABLE EQUALS lines SEMICOLON
		{
		tokenizer.pushToken((*$1),"assignation","");
		//vars[*$1] = $3;delete $1;
		}
		|CREATEOBJECTINIT ARGS BAR line_method  SEMICOLON RPAREN
		{
		std::cout << "(| :args | procedimiento)" <<std::endl;
		}
		|atom_expression
		|expression
		;



line_method:
		expresion_method operation expresion_method
		|expresion_method
		;

expresion_method:
		VARIABLE operation NUMBER
		{
		}
		|VARIABLE operation VARIABLE
		{
		//esto es redundante porque un atom_expression tiene la misma pinta, tengo que generalizar los atom_expression
		}
		;
operation:
		PLUS {
		std::cout << "algo + algo" <<std::endl;
		}
		|MINUS {
		std::cout << "algo - algo" <<std::endl;

		}
		|ASTERISK {
		std::cout << "algo * algo" <<std::endl;

		}
		|FSLASH {
		std::cout << "algo / algo" <<std::endl;
		}
		;

atom_expression:
							VARIABLE SEMICOLON
							{
							tokenizer.pushToken((*$1),"assignation","");
							}
							|VARIABLE EQUALSMUTAL expression SEMICOLON {
							tokenizer.pushToken(*$1,"assignation_mutable","");
							}
							|VARIABLE SET expression SEMICOLON{
							tokenizer.pushToken(*$1,"find","");
							tokenizer.pushToken("","set","");
							}
							|VARIABLE PLUS VARIABLE SEMICOLON
							{
							tokenizer.pushToken(*$3,"find","");
							tokenizer.pushToken("","+","");
							tokenizer.pushToken(*$1,"find","");
							}
							|VARIABLE MINUS VARIABLE SEMICOLON
							{
							tokenizer.pushToken(*$3,"find","");
							tokenizer.pushToken("","-","");
							tokenizer.pushToken(*$1,"find","");
							}
							|VARIABLE ASTERISK VARIABLE SEMICOLON
							{
							tokenizer.pushToken(*$3,"find","");
							tokenizer.pushToken("","*","");
							tokenizer.pushToken(*$1,"find","");
							}
							|VARIABLE FSLASH VARIABLE SEMICOLON
							{
							tokenizer.pushToken(*$3,"find","");
							tokenizer.pushToken("","/","");
							tokenizer.pushToken(*$1,"find","");
							}
							|ARGS
							{
							std::cout << "ARGS"<<std::endl;
							}
							;

expression: 	expression PLUS inner1 SEMICOLON
							{
							$$ = $1 + $3 ;
							tokenizer.pushToken("","+","");
							}
						| expression MINUS inner1 { $$ = $1 - $3 ;}
						| inner1 { $$ = $1 ;};

inner1: 	inner1 ASTERISK inner2 { $$ = $1 * $3 ;}
		|inner1 FSLASH inner2{if( $3 == 0) Div0Error (); else $$ = $1 / $3 ;}
		|inner2 { $$ = $1 ;};
inner2:
		VARIABLE {
		tokenizer.pushToken(*$1,"find","");
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
		tokenizer.pushToken("","create_number",to_string($1));
		//$$ = $1 ;
		}
		|LPAREN expression RPAREN {
		//$$ = $2 ;
		}
		;
%%
void Div0Error ( void ) { printf (" Error : division by zero \n"); exit (0);}
void UnknownVarError ( string s ) { printf (" Error : -%s- does not exist !\n", s . c_str ()); exit (0);}
