#pragma once
#include <string>
class Cpipes
{
private:
    std::string name = { "." }; // Pipe name (kilometer mark)
    int length = { 0 }; // Pipe length
    int diameter = { 0 }; // Pipe diameter
    bool isUnderRepair = { 0 };// "under repair" sign
    int id;
public:
    void setName(std::string& n);
    void setLength(int& l);
    void setDiameter(int& d);
    void setRepairStatus(bool& status);
    std::string getName() { return name; }
    int getLength() { return length; }
    int getDiameter(){ return diameter; }
    bool getRepairStatus() { return isUnderRepair; }
    void display() const;
    void editRepairStatus();
};


