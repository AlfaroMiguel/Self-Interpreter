%option c++
%option noyywrap


%{
#include <sstream>
#include "parser.h"
#include <cstdlib>
%}


DIGIT  [0-9]
DIGIT1 [1-9]
LETTER [aA-zZ]
WORD {LETTER}{LETTER}*
IMPRIMIR "print "|" print"
TRUE "true "|" true"|"true"
FALSE "false "|" false"|"false"
CLONE "clone "|" clone"
LOBBY "lobby "|" lobby"
COLLECT "collect "|" collect"
ARGUMENTGENERIC ":arg."|" :arg."|"arg"|" arg"|"arg "
METHOD {WORD}:
FINISH "exit "|"quit "|"exit"|"quit"
%%
{FINISH}                             {	std::cout<<"Fin"<<std::endl;
                                        yyterminate();
                                    }
{TRUE}                             {	
                                      std::cout <<"Boolean ";
                                   }
{FALSE}                             {	
                                      std::cout <<"Boolean ";
                                   }
{DIGIT}	                            {	
                                      std::cout <<"Numero ";
                                    }
{LOBBY}	                            {	
                                      std::cout <<"Lobby ";
                                    }
{LETTER}                           {	
                                      std::cout <<"Letra ";
                                    }
{DIGIT1}{DIGIT}* {
                                      std::cout <<"Number "<< yytext <<std::endl;
                                    }
"."                                 {
					std::cout <<"End ";
                                    }
"("                                 {
					std::cout <<"Open ";
                                    }
")"                                 {
					std::cout <<"Close ";
                                    }
" "                                 { }
"nil"                                {
					std::cout <<"Null Object ";
                                    }
{WORD}                              {

                                      std::cout <<"Palabra ";
                                    }
{IMPRIMIR}                          {	
                                      std::cout <<"[Print] ";
                                    }
"="                               {	
                                      std::cout <<"[Create No Mutable Object]  ";
                                    }
"<-"                               {	
                                      std::cout <<"[Create Mutable Object] ";
                                    }
":"                               {	
                                      std::cout <<"[Set value] ";
                                   }
"+"                               {	
                                      std::cout <<"[Sum] ";
                                   }
"/"                               {	
                                      std::cout <<"[Division] ";
                                   }
"*"                               {	
                                      std::cout <<"[Multiplication] ";
                                   }
{CLONE}                             {	
                                      std::cout <<"[Clone] ";
                                   }
"=="                             {	
                                      std::cout <<"[Equal] ";
                                   }
"!="                             {	
                                      std::cout <<"[Distinct] ";
                                   }
"-"                               {	
                                      std::cout <<"[Subtraction] ";
                                   }
"_AddSlots:"                       {	
                                      std::cout <<"[Add slot] ";
                                   }
"_RemoveSlots:"                    {	
                                      std::cout <<"[Remove slot] ";
                                   }
"_Name:"                            {	
                                      std::cout <<"[Name] ";
                                   }
"(|"                       	  {	
                                      std::cout <<"[Create Object Init] ";
                                   }
"|"                       	  {	
                                      std::cout <<"Argument ";
                                   }
{ARGUMENTGENERIC}                 {	
                                      std::cout <<"Argument Generic ";
                                   }
{METHOD}                 {	
                                      std::cout <<"[Method] ";
                                   }
"|)"                       	   {	
                                      std::cout <<"[Create Object End] ";
                                   }
<<EOF>>                             {	std::cout<<"Fin"<<std::endl;
                                        yyterminate();
                                    }

.                               {std::cout<<"[Comando No reconocido] ";}

%%
