#ifndef SEARCHER_OBJECT_H
#define SEARCHER_OBJECT_H

#include "object.h"

class SearcherObject:public Object{
  Object* expressionSearched;
public:
    SearcherObject(std::string nameString);
    ~SearcherObject();
    void setValue(int valueAux);
    void addSlots(std::string id,Object* slot, bool algo, bool otro);
    NativeValue getValue();
    NativeValue ejecute(std::string operation, Object* expression);
    void evaluate();
};

#endif
