#include "Cpipes.h"
#include <iostream>


    void Cpipes::setName(std::string & n) {
        name = n;
    }
    void Cpipes::setLength(int& l) {
        length = l;
    }
    void Cpipes::setDiameter(int& d) {
        diameter = d;
    }
    void Cpipes::setRepairStatus(bool& status) {
        isUnderRepair = status;
    }
    std::string Cpipes::getName() {
        return name;
    }
    int Cpipes::getLength() {
        return length;
    }
    int Cpipes::getDiameter() {
        return diameter;
    }
    bool Cpipes::getRepairStatus() {
        return isUnderRepair;
    }

    // Function to output pipe data
    void Cpipes::display() const{
        if (name == "." || length <= 0 || diameter <= 0) {
            std::cout << "There is no pipe. Perhaps you entered the pipe data incorrectly or did not add it. Try again." << std::endl;
        }
        else {
            std::cout << "Pipe: " << name << ", Length: " << length << ", Diameter: " << diameter << ", Under repair: " << (isUnderRepair ? "Yes" : "No") << std::endl;
        }
    }

    // Function for editing the "under repair" state
    void Cpipes::editRepairStatus() {
        if (name == "." || length <= 0 || diameter <= 0) {
            std::cout << "There is no pipe, so this option does not work. Please enter the pipe details." << std::endl;
        }
        else {
            isUnderRepair = !isUnderRepair;// Changes the state to the opposite
            std::cout << "workshop condition" << std::endl;
            std::cout << (isUnderRepair ? "Yes" : "No") << std::endl;
        }
    }

