#ifndef TUPLE_STRING_H
#define TUPLE_STRING_H

#include <string>

class TupleString{
private:
  std::string myId;
  std::string myMessage;
  std::string myValue;
public:
    TupleString(std::string id,std::string message,std::string value);
    std::string getiD();
    std::string getMessage();
    std::string getValue();
    ~TupleString();
};

#endif /*TUPLE_STRING_H*/
