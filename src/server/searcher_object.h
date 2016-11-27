#ifndef SEARCHER_OBJECT_H
#define SEARCHER_OBJECT_H

#include "object.h"

class SearcherObject:public Object{
  Object* expressionSearched;
public:

    virtual void serialize(json& jserialization){
        std::cout << "SearcherObject::serialize start: " << objectName << std::endl;
        jserialization["objectName"] = objectName;
        jserialization["representation"] = representation;

        json jRegisterOfSlots;
        slots.serialize(jRegisterOfSlots);
        jserialization["slots"] = jRegisterOfSlots;

        json jMorph;
        myMorph.serialize(jMorph);
        jserialization["myMorph"] = jMorph;

        jserialization["type"] = "searcherObject";

        std::cout << "SearcherObject::serialize end " << objectName << std::endl;

    }

    //Deserealizacion

    static Object* deserialize(json& jdeserialization, Lobby* lobby){
        std::cout << "SearcherObject::deserialize start" << std::endl;
        std::string name = jdeserialization["objectName"];
        SearcherObject* searcherobj = new SearcherObject(name);
        searcherobj->objectName = jdeserialization["objectName"];
        searcherobj->representation = jdeserialization["representation"];

        json jRegisterOfSlots;
        jRegisterOfSlots = jdeserialization["slots"];
        searcherobj->slots.deserialize(jRegisterOfSlots, searcherobj, lobby);

        json jMorph;
        jMorph = jdeserialization["myMorph"];
        searcherobj->myMorph.deserialize(jMorph);

        searcherobj->myLobby = lobby;

        std::cout << "SearcherObject::deserialize end" << std::endl;

        return searcherobj;
    }

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
