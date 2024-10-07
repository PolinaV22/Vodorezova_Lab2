#include "Compressor_St.h"
#include <iostream>

//class Compressor_St {
//private:
  //  std::string name;
   // int workshopCount;
  //  int workshopsInOperation;
   // int efficiency;
//public:
    //Compressor_St(std::string name = ".", int workshopCount = 0, int workshopsInOperation = 0, int efficiency = 0) {};
    void Compressor_St::setName(std::string & n) {
        name = n;
    }
    void Compressor_St::setWorkshops(int& w) {
        workshopCount = w;
    }
    void Compressor_St::setActiveWorkshops(int& aw) {
        workshopsInOperation = aw;
    }
    void Compressor_St::setefficiency(int& ef) {
        efficiency = ef;
    }
    std::string Compressor_St::getName() {
        return name;
    }
    int Compressor_St::getWorkshops() {
        return workshopCount;
    }
    int Compressor_St::getActiveWorkshops() {
        return workshopsInOperation;
    }
    int Compressor_St::getefficiency() {
        return efficiency;
    }
    // Function for outputting CS data
    void Compressor_St::displayst() const{
        if (name == "." || workshopCount <= 0 || workshopsInOperation <= 0 || efficiency <= 0) {
            std::cout << "There is no compressor station. Perhaps you entered the data incorrectly or did not make it. Try again." << std::endl;
        }
        else {
            std::cout << "Compressor Station:" << name << ", Workshops: " << workshopCount << ", In operation: " << workshopsInOperation << ", Efficiency: " << efficiency << std::endl;
        }
    }
    // Function for changing the state of the workshop
    void Compressor_St::toggleWorkshopStatus() {
        int choice;
        if (name == "." || workshopCount <= 0 || workshopsInOperation <= 0 || efficiency <= 0) {
            std::cout << "There is no compressor station. Perhaps you entered the data incorrectly or did not make it. Try again." << std::endl;
        }
        else {
            std::cout << "1. launch a new workshop" << std::endl;
            std::cout << "2. Stop the workshop" << std::endl;
            std::cin >> choice;
            switch (choice) {
            case 1:
                if (workshopsInOperation < workshopCount) {
                    workshopsInOperation++;
                    std::cout << "Launched a new workshop. Now in operation " << workshopsInOperation << " workshop(s)." << std::endl;
                }
                else {
                    std::cout << "All workshops are already running." << std::endl;
                }
                break;
            case 2:
                if (workshopsInOperation > 0) {
                    workshopsInOperation--;
                    std::cout << "One workshop was stopped. Now " << workshopsInOperation << " workshop(s) are in operation." << std::endl;
                }
                else {
                    std::cout << "All workshops are already installed." << std::endl;
                }
                break;
            default:
                std::cout << "Invalid choice! Try again." << std::endl;
                break;
            }
        }
    }

//};
