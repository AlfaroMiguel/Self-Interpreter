#ifndef SEARCHER_OBJECT_H
#define SEARCHER_OBJECT_H

#include "object.h"

class SearcherObject:public Object{
  Object* expressionSearched;
public:
    SearcherObject(std::string nameString);
    ~SearcherObject();
    void setValue(int valueAux);
    void addSlots(std::string slotName,Object* slot, bool isMutable, bool isParentSlot);
    NativeValue getValue();
    NativeValue ejecute(std::string operation, Object* expression);
    void evaluate();
    Object* clone();
};

#endif
