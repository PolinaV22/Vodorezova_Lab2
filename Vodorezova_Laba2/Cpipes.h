#pragma once
#include <string>
#include <map>
#include <iostream>
#include "Cpipes.h"
#include "Compressor_St.h"
#include <vector>
#include <fstream>

class Cpipes
{
private:
    std::string name = { "." }; 
    int length = { 0 }; 
    int diameter = { 0 }; 
    bool isUnderRepair = { 0 };
public:
    void setName(std::string& n);
    void setLength(int& l);
    void setDiameter(int& d);
    void setRepairStatus(bool& status);
    std::string getName();
    int getLength();
    int getDiameter();
    bool getRepairStatus();
    void display() const;
    void editRepairStatus();
};


