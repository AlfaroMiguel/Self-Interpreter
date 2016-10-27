#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stack>
#include <map>

#include <string>

//#include "tuple_string.h"

class Tokenizer{
private:
  std::map<std::string,int> myMap;
  //std::stack<TupleString> myStack;
public:
    Tokenizer();
    void pushToken(std::string id,std::string message,std::string value);
    void end();
    ~Tokenizer();
};

#endif /*TOKENIZER_H*/
