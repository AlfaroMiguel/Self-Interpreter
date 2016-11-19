#ifndef MORPH_H
#define MORPH_H

#include <string>
#include <map>

class Morph{
private:
    std::string name;
    double x;
    double y;
    std::map<std::string, std::string> slots;
    int id;
public:
    static int idNumber;
    Morph();
    ~Morph();
    void setName(const std::string& newName);
    void changePosition(double newX, double newY);
    void addSlot(std::string nombre, std::string valor);
    std::string getEvent(std::string eventName);
    int getId();

};

#endif