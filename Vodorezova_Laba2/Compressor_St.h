#pragma once
#include <string>
#include <map>
#include <iostream>
#include "Cpipes.h"
#include "Compressor_St.h"
#include <vector>
#include <fstream>

class Compressor_St
{
private:
    std::string name = { "." };
    int workshopCount = { 0 };
    int workshopsInOperation = { 0 };
    int efficiency = { 0 };
public:
    void setName(std::string& n);
    void setWorkshops(int& w);
    void setActiveWorkshops(int& aw);
    void setefficiency(int& ef);
    std::string getName();
    int getWorkshops();
    int getActiveWorkshops();
    int getefficiency();
    void displayst() const;
    void toggleWorkshopStatus();
};

