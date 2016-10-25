%name Parser
%define LSP_NEEDED
%define MEMBERS \
          virtual ~Parser() {} \
          private: \
                yyFlexLexer lexer;
%define LEX_BODY {return lexer.yylex();}
%define ERROR_BODY {}


%header{
#include <iostream>
#include <fstream>
#include <FlexLexer.h>
#include <stdlib.h>
using namespace std;
%}


%union {
                int i_type;
}


%token UNKNOWN
%token <i_type> NUMBER
%type <i_type> number



%start number


%%
number
: NUMBER { $$ = atoi(lexer.YYText());std::cout << "Parser value"<<$$<<std::endl;}
;


%%
