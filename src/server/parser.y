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

%token <int_val> PLUS MINUS ASTERISK FSLASH EQUALS PRINT LPAREN RPAREN SEMICOLON EQUALSMUTAL SET  ADD CREATEOBJECTINIT CREATEOBJECTEND
%token <str_val> VARIABLE
%token <double_val> NUMBER
%type <double_val> expression;
%type <double_val> inner1 ;
%type <double_val> inner2 ;
%{
	Interpreter interpreter;
%}
%start parsetree
%%
parsetree:	lines;

lines:		lines line
					|line
					;

line :		PRINT expression SEMICOLON {printf ("%lf\n", $2 );}
		|VARIABLE EQUALS expression SEMICOLON {vars[*$1] = $3;std::cerr<<"variable = line. ";delete $1 ;}
		|VARIABLE EQUALSMUTAL expression SEMICOLON {interpreter.crearObjetoMutable(*$1,$3);}
		|VARIABLE SET expression SEMICOLON {interpreter.setObjeto(*$1,$3);}
		|VARIABLE SEMICOLON {interpreter.crearObjetoMutable(*$1,0.0);}
		|CREATEOBJECTINIT line CREATEOBJECTEND SEMICOLON {std::cerr<<"(| line |). ";}
		|VARIABLE ADD line {std::cerr<<"variable _addSlot line ";}
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
