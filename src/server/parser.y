%{
	#include <cstdio>
	#include <cstdlib>
	#include <string>
	#include <map>
	#include "interpreter.h"
	#include <iostream> //cout
	using namespace std ;
	map<string,double > vars ; // map from variable name to value
	extern int yylex ();
	extern void yyerror ( char *);
	void Div0Error ( void );
	void UnknownVarError ( string s );
	//Interpreter interpreter;
%}
%union{
	int int_val ;
	double double_val ;
	string* str_val ;
}
%start parse

%token <int_val> PLUS MINUS ASTERISK FSLASH EQUALS PRINT LPAREN RPAREN SEMICOLON EQUALSMUTAL SET  ADD CREATEOBJECTINIT CREATEOBJECTEND
%token <str_val> VARIABLE
%token <double_val> NUMBER
%type <double_val> expression;
%type <double_val> inner1 ;
%type <double_val> inner2 ;
%{
	Interpreter interpreter;
%}
%%
parse:	lines;

lines:		lines line
					|line
					;

line :
		PRINT expression SEMICOLON {std::cerr<<"print line"<<std::endl;}
		|VARIABLE EQUALS expression SEMICOLON {std::cerr<<"variable = line. "<<std::endl;vars[*$1] = $3;delete $1 ;}
		|VARIABLE EQUALSMUTAL expression SEMICOLON {std::cerr<<"variable <- line."<<std::endl;interpreter.crearObjetoMutable(*$1,$3);}
		|VARIABLE SET expression SEMICOLON {std::cerr<<"variable : line."<<std::endl;interpreter.setObjeto(*$1,$3);}
		|VARIABLE SEMICOLON {std::cerr<<"variable <- nill."<<std::endl;}
		|CREATEOBJECTINIT line CREATEOBJECTEND SEMICOLON {std::cerr<<"(| line |). "<<std::endl;;}
		|VARIABLE ADD line {std::cerr<<"variable _addSlot line "<<std::endl;}
		;

expression: 	expression PLUS inner1 { $$ = $1 + $3 ;}
						| expression MINUS inner1 { $$ = $1 - $3 ;}
						| inner1 { $$ = $1 ;};

inner1: 	inner1 ASTERISK inner2 { $$ = $1 * $3 ;}
		|inner1 FSLASH inner2{if( $3 == 0) Div0Error (); else $$ = $1 / $3 ;}
		|inner2 { $$ = $1 ;};
inner2: 	VARIABLE {if (! vars . count (* $1 )) UnknownVarError (* $1 ); else $$ = vars [* $1 ]; delete $1 ;}
		|NUMBER { $$ = $1 ;}
		|LPAREN expression RPAREN { $$ = $2 ;};
%%
void Div0Error ( void ) { printf (" Error : division by zero \n"); exit (0);}
void UnknownVarError ( string s ) { printf (" Error : -%s- does not exist !\n", s . c_str ()); exit (0);}
