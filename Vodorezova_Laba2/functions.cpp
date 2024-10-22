#include "functions.h"
#include <iostream>
#include <map>
#include "Cpipes.h"
#include "Compressor_St.h"
#include <string>
#include <vector>
#include <fstream>

void functions::logAction(const std::string& action) {
    std::ofstream logFile("log.txt", std::ios::app);
    if (logFile.is_open()) {
        logFile << action << " - " << std::endl;
    }
    else {
        std::cerr << "The log file could not be opened." << std::endl;
    }
    logFile.close();
}
void functions::readPipe(std::map<int, Cpipes>& pipes) {
    Cpipes p;
    std::string name;
    int length;
    int diameter;
    std::cout << "Enter pipe name (km mark): ";
    std::cin >> std::ws;
    getline(std::cin, name);
    p.setName(name);

    while (true) {
        std::cout << "Enter length (in km): ";
        std::cin >> length;
        if (std::cin.good() && length > 0 && std::cin.peek() == '\n') {
            p.setLength(length);
            break;
        }
        else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter an integer that is positive and greater than zero. " << std::endl;
        }
    }
    while (true) {
        std::cout << "Enter diameter (in m): ";
        std::cin >> diameter;
        if (std::cin.good() && diameter > 0 && std::cin.peek() == '\n') {
            p.setDiameter(diameter);
            break;
        }
        else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter an integer that is positive and greater than zero. " << std::endl;
        }
    }
    int id = pipes.empty() ? 1 : (pipes.rbegin()->first + 1);
    pipes.emplace(id, p);
    logAction("Added pipe with ID " + std::to_string(id));
}

void functions::displayAllPipes(std::map<int, Cpipes>& pipes) {
    if (size(pipes) == 0) {
        std::cout << "Pipes are not found." << std::endl;
    }
    else {
        for (auto& p : pipes) {
            std::cout << "ID: " << p.first << std::endl;
            p.second.display();
        }
    }
}
void functions::delitepipes(std::map<int, Cpipes>& pipes) {
    int id;
    std::cout << "Enter the index of the pipe you want to delite:" << std::endl;
    std::cin >> id;
    if (pipes.find(id) != pipes.end()) {
        pipes.erase(id);
        logAction("Delited pipe with ID " + std::to_string(id));
    }
    else {
        std::cout << "Pipe is not found." << std::endl;
    }
}

void functions::editPipe(std::map<int, Cpipes>& pipes) {
    int id;
    std::cout << "Enter pipe ID to edit: ";
    std::cin >> id;
    if (pipes.find(id) != pipes.end()) {
        pipes[id].editRepairStatus();
        logAction("Edited pipe with ID " + std::to_string(id));
    }
    else {
        std::cout << "Pipe is not found." << std::endl;
    }
}


void functions::batchPipes(std::map<int, Cpipes>& pipes) {
    bool editAll;
    int choice;
    std::cout << "Edit all pipes? (1 for yes, 0 for no): ";
    std::cin >> editAll;
    std::cout << "1.Delite" << std::endl;
    std::cout << "2.Change" << std::endl;
    std::cin >> choice;
    if (editAll) {
        switch (choice) {
        case 1:
            if (size(pipes) == 0) {
                std::cout << "Pipes are not found" << std::endl;
                break;
            }
            for (auto& pipe : pipes) {
                pipes.erase(pipe.first);
            }
            logAction("Batch delited all pipes.");
            break;
        case 2:
            if (size(pipes) == 0) {
                std::cout << "Pipes are not found" << std::endl;
                break;
            }
            for (auto& pipe : pipes) {
                pipe.second.editRepairStatus();
            }
            logAction("Batch edited all pipes.");
            break;
        default:
            std::cout << "Invalid choice! Try again." << std::endl;
            break;
        }
    }
    else {
        std::vector<int> ids;
        int id;
        std::cout << "Enter pipe IDs to edit or delite (enter -1 to stop): ";
        while (std::cin >> id && id != -1) {
            if (pipes.find(id) != pipes.end()) {
                ids.push_back(id);
            }
            else {
                std::cout << "Pipe with ID " << id << " not found." << std::endl;
            }
        }
        switch (choice) {
        case 1:
            for (int pipeId : ids) {
                pipes.erase(pipeId);
            }
            logAction("Batch delited selected pipes.");
            break;
        case 2:
            for (int pipeId : ids) {
                pipes[pipeId].editRepairStatus();
            }
            logAction("Batch edited selected pipes.");
            break;
        default:
            std::cout << "Invalid choice! Try again." << std::endl;
            break;
        }
    }
}

// Function for reading CS data
void functions::readst(std::map<int, Compressor_St>& stations) {
    Compressor_St st;
    std::string name;
    int workshopCount;
    int workshopsInOperation;
    int efficiency;

    std::cout << "Enter compressor station name: ";
    std::cin >> std::ws;
    getline(std::cin, name);
    st.setName(name);

    while (true) {
        std::cout << "Enter number of workshops: ";
        std::cin >> workshopCount;
        if (std::cin.good() && workshopCount > 0 && std::cin.peek() == '\n') {
            st.setWorkshops(workshopCount);
            break;
        }
        else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter an integer that is positive and greater than zero. " << std::endl;
        }
    }
    while (true) {
        std::cout << "Enter number of workshops in operation: ";
        std::cin >> workshopsInOperation;
        if (std::cin.good() && workshopsInOperation > 0 && workshopsInOperation <= workshopCount && std::cin.peek() == '\n') {
            st.setActiveWorkshops(workshopsInOperation);
            break;
        }
        else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter an integer that is positive number greater than zero and less than the number of workstations. " << std::endl;
        }
    }
    if (workshopCount == 0) {
        efficiency = 0;
    }
    else {
        efficiency = (100 * workshopsInOperation) / workshopCount;
    }
    st.setefficiency(efficiency);
    int id = stations.empty() ? 1 : (stations.rbegin()->first + 1);
    stations.emplace(id, st);
    logAction("Added compressor station with ID " + std::to_string(id));
}

void functions::delitest(std::map<int, Compressor_St>& stations) {
    int id;
    std::cout << "Enter the index of the Compressor station you want to delite:" << std::endl;
    std::cin >> id;
    if (stations.find(id) != stations.end()) {
        stations.erase(id);
        logAction("Edited station with ID " + std::to_string(id));
    }
    else {
        std::cout << "Station is not found." << std::endl;
    }
}


void functions::displayAllStations(std::map<int, Compressor_St>& stations) {
    if (size(stations) == 0) {
        std::cout << "Compressor stations are not found." << std::endl;
    }
    else {
        for (auto& cs : stations) {
            std::cout << "ID: " << cs.first << std::endl;
            cs.second.displayst();
        }
    }
}

void functions::editStation(std::map<int, Compressor_St>& stations) {
    int id;
    std::cout << "Enter station ID to edit: ";
    std::cin >> id;
    if (stations.find(id) != stations.end()) {
        stations[id].toggleWorkshopStatus();
        logAction("Edited compressor station with ID " + std::to_string(id));
    }
    else {
        std::cout << "Station is not found." << std::endl;
    }
}

void functions::searchPipes(std::map<int, Cpipes>& pipes) {
    std::string query;
    bool inRepair;
    int choice;
    int ch;
    std::vector<int> ids;
    std::cout << "1.Search by pipe name" << std::endl;
    std::cout << "2.Search by repair status" << std::endl;
    std::cout << "3.Batch Edit Pipes" << std::endl;
    std::cin >> choice;
    switch (choice) {
    case 1:
        std::cout << "Enter pipe name to search: ";
        std::cin >> std::ws;
        getline(std::cin, query);
        for (auto& p : pipes) {
            if (p.second.getName().find(query) != std::string::npos || p.second.getName().rfind(query) != std::string::npos) {
                std::cout << "ID: " << p.first << " ";
                p.second.display();
                ids.push_back(p.first);
            }
        }
        if (size(ids) == 0) {
            std::cout << "Pipes are not found" << std::endl;
            break;
        }
        std::cout << "1.Delite" << std::endl;
        std::cout << "2.Change" << std::endl;
        std::cin >> ch;
        switch (ch) {
        case 1:
            for (int idd : ids) {
                pipes.erase(idd);
                logAction("Delited pipe with ID " + std::to_string(idd));
            }
            break;
        case 2:
            for (int idd : ids) {
                pipes[idd].editRepairStatus();
                logAction("Edited pipe with ID " + std::to_string(idd));
            }
            break;
        default:
            std::cout << "Invalid choice! Try again." << std::endl;
            break;
        }
        break;
    case 2:
        std::cout << "Filter by repair status (1 for yes, 0 for no): ";
        std::cin >> inRepair;
        for (auto& p : pipes) {
            if (p.second.getRepairStatus() == inRepair) {
                std::cout << "ID: " << p.first << " ";
                p.second.display();
                ids.push_back(p.first);
            }
        }
        if (size(ids) == 0) {
            std::cout << "Pipes are not found" << std::endl;
            break;
        }
        std::cout << "1.Delite" << std::endl;
        std::cout << "2.Change" << std::endl;
        std::cin >> ch;
        switch (ch) {
        case 1:
            for (int idd : ids) {
                pipes.erase(idd);
                logAction("Delited pipe with ID " + std::to_string(idd));
            }
            break;
        case 2:
            for (int idd : ids) {
                pipes[idd].editRepairStatus();
                logAction("Edited pipe with ID " + std::to_string(idd));
            }
            break;
        default:
            std::cout << "Invalid choice! Try again." << std::endl;
            break;
        }
        break;
    case 3:
        batchPipes(pipes);
        break;

    default:
        std::cout << "Invalid choice! Try again." << std::endl;
        break;
    }
}
void functions::searchStations(std::map<int, Compressor_St>& stations) {
    std::string query;
    std::vector<int> ids;
    double maxIdlePercentage;
    int choice;
    int percent;
    int ch;
    std::cout << "1.Search by compressor station name" << std::endl;
    std::cout << "2.Search by efficienty" << std::endl;
    std::cin >> choice;
    switch (choice) {
    case 1:
        std::cout << "Enter compressor station name to search: ";
        std::cin >> std::ws;
        getline(std::cin, query);
        for (auto& cs : stations) {
            if (cs.second.getName().find(query) != std::string::npos || cs.second.getName().rfind(query) != std::string::npos){
                std::cout << "ID: " << cs.first << " ";
                cs.second.displayst();
                ids.push_back(cs.first);
            }
        }
        if (size(ids) == 0) {
            std::cout << "Compressor stations are not found." << std::endl;
            break;
        }
        std::cout << "1.Delite" << std::endl;
        std::cout << "2.Change" << std::endl;
        std::cin >> ch;
        switch (ch) {
        case 1:
            for (int idd : ids) {
                stations.erase(idd);
                logAction("Delited station with ID " + std::to_string(idd));
            }
            break;
        case 2:
            for (int idd : ids) {
                stations[idd].toggleWorkshopStatus();
                logAction("Edited Compressor station with ID " + std::to_string(idd));
            }
            break;
        default:
            std::cout << "Invalid choice! Try again." << std::endl;
            break;
        }
        break;
    case 2:
        std::cout << "Enter maximum idle percentage: ";
        std::cin >> maxIdlePercentage;
        std::cout << "1. Output of compressor stations with a lower percentage of efficiency indicated." << std::endl;
        std::cout << "2. Output of compressor stations with a high percentage of efficiency indicated." << std::endl;
        std::cin >> percent;
        switch (percent) {
        case 1:
            for (auto& cs : stations) {
                if (100 - cs.second.getefficiency() <= maxIdlePercentage) {
                    std::cout << "ID: " << cs.first << " ";
                    cs.second.displayst();
                    ids.push_back(cs.first);
                }
            }
            if (size(ids) == 0) {
                std::cout << "Compressor stations are not found" << std::endl;
                break;
            }
            std::cout << "1.Delite" << std::endl;
            std::cout << "2.Change" << std::endl;
            std::cin >> ch;
            switch (ch) {
            case 1:
                for (int idd : ids) {
                    stations.erase(idd);
                    logAction("Delited station with ID " + std::to_string(idd));
                }
                break;
            case 2:
                for (int idd : ids) {
                    stations[idd].toggleWorkshopStatus();
                    logAction("Edited Costation with ID " + std::to_string(idd));
                }
                break;
            default:
                std::cout << "Invalid choice! Try again." << std::endl;
                break;
            }
            break;
        case 2:
            for (auto& cs : stations) {
                if (100 - cs.second.getefficiency() >= maxIdlePercentage) {
                    std::cout << "ID: " << cs.first << " ";
                    cs.second.displayst();
                    ids.push_back(cs.first);
                }
            }
            if (size(ids) == 0) {
                std::cout << "Compressor stations are not found" << std::endl;
                break;
            }
            std::cout << "1.Delite" << std::endl;
            std::cout << "2.Change" << std::endl;
            std::cin >> ch;
            switch (ch) {
            case 1:
                for (int idd : ids) {
                    stations.erase(idd);
                    logAction("Delited station with ID " + std::to_string(idd));
                }
                break;
            case 2:
                for (int idd : ids) {
                    stations[idd].toggleWorkshopStatus();
                    logAction("Edited Compressor station with ID " + std::to_string(idd));
                }
                break;
            default:
                std::cout << "Invalid choice! Try again." << std::endl;
                break;
            }
            break;
        default:
            std::cout << "Invalid choice! Try again." << std::endl;
            break;
        }
        break;
    default:
        std::cout << "Invalid choice! Try again." << std::endl;
        break;
    }
}





