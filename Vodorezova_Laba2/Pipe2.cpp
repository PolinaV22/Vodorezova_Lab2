#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include "Cpipes.h"
#include "Compressor_St.h"

using namespace std;

void logAction(const string& action) {
    ofstream logFile("log.txt", ios::app);
    logFile << action << endl;
}

// Function for reading pipe data
void readPipe(map<int, Cpipes>& pipes) {
    Cpipes p;
    string name;
    int length;
    int diameter;
    cout << "Enter pipe name (km mark): ";
    cin >> ws;
    getline(cin, name);
    p.setName(name);

    while (true) {
        cout << "Enter length (in km): ";
        cin >> length;
        if (cin.good() && length > 0 && cin.peek() == '\n') {
            p.setLength(length);
            break;
        }
        else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter an integer that is positive and greater than zero. " << endl;
        }
    }
    while (true) {
        cout << "Enter diameter (in m): ";
        cin >> diameter;
        if (cin.good() && diameter > 0 && cin.peek() == '\n') {
            p.setDiameter(diameter);
            break;
        }
        else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter an integer that is positive and greater than zero. " << endl;
        }
    }
    int id = pipes.empty() ? 1 : (pipes.rbegin()->first + 1);
    pipes[id] = p;
    logAction("Added pipe with ID " + to_string(id));
}

void displayAllPipes(map<int, Cpipes>& pipes) {
    for (auto&  p : pipes) {
        cout << "ID: " << p.first << endl;
        p.second.display();
    }
}
void delitepipes(map<int, Cpipes>& pipes) {
    int id;
    cout << "Enter the index of the pipe you want to delite:" << endl;
    cin >> id;
    if (pipes.find(id) != pipes.end()) {
        pipes.erase(id);
        logAction("Delited pipe with ID " + to_string(id));
    }
    else {
        cout << "Pipe not found." << endl;
    }
}

void editPipe(map<int, Cpipes>& pipes) {
    int id;
    cout << "Enter pipe ID to edit: ";
    cin >> id;
    if (pipes.find(id) != pipes.end()) {
        pipes[id].editRepairStatus();
        logAction("Edited pipe with ID " + to_string(id));
    }
    else {
        cout << "Pipe not found." << endl;
    }
}


void batchPipes(map<int, Cpipes>& pipes) {
    bool editAll;
    int choice;
    cout << "Edit all pipes? (1 for yes, 0 for no): ";
    cin >> editAll;
    cout << "1.Delite" << endl;
    cout << "2.Change" << endl;
    cin >> choice;
    if (editAll) {
        switch (choice) {
        case 1:
            for (auto& pipe : pipes) {
                pipes.erase(pipe.first);
            }
            logAction("Batch delited all pipes.");
            break;
        case 2:
            for (auto& pipe : pipes) {
                pipe.second.editRepairStatus();
            }
            logAction("Batch edited all pipes.");
            break;
        default:
            cout << "Invalid choice! Try again." << endl;
            break;
        }
    }
    else {
        vector<int> ids;
        int id;
        cout << "Enter pipe IDs to edit or delite (enter -1 to stop): ";
        while (cin >> id && id != -1) {
            if (pipes.find(id) != pipes.end()) {
                ids.push_back(id);
            }
            else {
                cout << "Pipe with ID " << id << " not found." << endl;
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
            cout << "Invalid choice! Try again." << endl;
            break;
        }
    }
}

// Function for reading CS data
void readst(map<int, Compressor_St>& stations) {
    Compressor_St st;
    string name;
    int workshopCount;
    int workshopsInOperation;
    int efficiency;

    cout << "Enter compressor station name: ";
    cin >> ws;
    getline(cin, name);
    st.setName(name);

    while (true) {
        cout << "Enter number of workshops: ";
        cin >> workshopCount;
        if (cin.good() && workshopCount > 0 && cin.peek() == '\n') {
            st.setWorkshops(workshopCount);
            break;
        }
        else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter an integer that is positive and greater than zero. " << endl;
        }
    }
    while (true) {
        cout << "Enter number of workshops in operation: ";
        cin >> workshopsInOperation;
        if (cin.good() && workshopsInOperation > 0 && workshopsInOperation <= workshopCount && cin.peek() == '\n') {
            st.setActiveWorkshops(workshopsInOperation);
            break;
        }
        else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter an integer that is positive and greater than zero. " << endl;
        }
    }
    if (workshopCount == 0) {
        efficiency = 0;
    }
    else {
        efficiency = 100 * (workshopCount - workshopsInOperation) / workshopCount;
    }
    st.setefficiency(efficiency);
    int id = stations.empty() ? 1 : (stations.rbegin()->first + 1);
    stations[id] = st;
    logAction("Added compressor station with ID " + to_string(id));
}

void delitest(map<int, Compressor_St>& stations) {
    int id;
    cout << "Enter the index of the Compressor station you want to delite:" << endl;
    cin >> id;
    if (stations.find(id) != stations.end()) {
        stations.erase(id);
        logAction("Edited pipe with ID " + to_string(id));
    }
    else {
        cout << "Station not found." << endl;
    }
}
void displayAllStations( map<int, Compressor_St>& stations) {
    for ( auto&  cs : stations) {
        cout << "ID: " << cs.first << " ";
        cs.second.displayst();
    }
}

void editStation(map<int, Compressor_St>& stations) {
    int id;
    cout << "Enter station ID to edit: ";
    cin >> id;
    if (stations.find(id) != stations.end()) {
        stations[id].toggleWorkshopStatus();
        logAction("Edited compressor station with ID " + to_string(id));
    }
    else {
        cout << "Station not found." << endl;
    }
}

void searchPipes( map<int, Cpipes>& pipes) {
    string query;
    bool inRepair;
    int choice;
    cout << "1.Search by pipe name" << endl;
    cout << "2.Search by repair status" << endl;
    cin >> choice;
    switch (choice) {
    case 1:
        cout << "Enter pipe name to search: ";
        cin >> ws;
        getline(cin, query);
        for ( auto& p : pipes) {
            if (p.second.getName().find(query) != string::npos) {
                cout << "ID: " << p.first << " ";
                p.second.display();
            }
        }
        break;
    case 2:
        cout << "Filter by repair status (1 for yes, 0 for no): ";
        cin >> inRepair;
        for ( auto& p : pipes) {
            if (p.second.getRepairStatus() == inRepair) {
                cout << "ID: " << p.first << " ";
                p.second.display();
            }
        }
        break;
    default:
        cout << "Invalid choice! Try again." << endl;
        break;
    }
}
void searchStations( map<int, Compressor_St>& stations) {
    string query;
    double maxIdlePercentage;
    int choice;
    int percent;
    cout << "1.Search by compressor station name" << endl;
    cout << "2.Search by efficienty" << endl;
    cin >> choice;
    cin >> percent;
    switch (choice) {
    case 1:
        cout << "Enter compressor station name to search: ";
        cin >> ws;
        getline(cin, query);
        for ( auto& cs : stations) {
            if (cs.second.getName().find(query) != string::npos) {
                cout << "ID: " << cs.first << " ";
                cs.second.displayst();
            }
        }
        break;
    case 2:
        cout << "Enter maximum idle percentage: ";
        cin >> maxIdlePercentage;
        cout << "1. Output of compressor stations with a lower percentage of efficiency indicated." << endl;
        cout << "2. Output of compressor stations with a high percentage of efficiency indicated." << endl;
        cin >> percent;
        switch (percent) {
        case 1:
            for ( auto& cs : stations) {
                if (cs.second.getefficiency() <= maxIdlePercentage) {
                    cout << "ID: " << cs.first << " ";
                    cs.second.displayst();
                }
            }
            break;
        case 2:
            for ( auto& cs : stations) {
                if (cs.second.getefficiency() >= maxIdlePercentage) {
                    cout << "ID: " << cs.first << " ";
                    cs.second.displayst();
                }
            }
            break;
        default:
            cout << "Invalid choice! Try again." << endl;
            break;
        }
        break;
    default:
        cout << "Invalid choice! Try again." << endl;
        break;
    }
}

// Сохранение данных объектов в файл
template<typename T>
void saveToFile(const map<int, T>& objects, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& [id, obj] : objects) {
            file << id << endl;
            file << obj.getName() << endl;
        }
    }
    file.close();
    logAction("Saved to file: " + filename);
}

// Загрузка данных объектов из файла
template<typename T>
void loadFromFile(map<int, T>& objects, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        int id;
        T obj;
        string name;
        file >> id;
        file >> name;
        obj.setName(name);
        objects[id] = obj;
    }
    file.close();
    logAction("Loaded from file: " + filename);
}

// Main function
int main() {
    map<int, Cpipes> pipes;
    map<int, Compressor_St> stations;
    int choice; // Variable for selecting an action

    while (true) {
        cout << "Menu: " << endl;
        cout << "1. Add Pipe" << endl;
        cout << "2. Add Compressor Station" << endl;
        cout << "3. Delite Pipe" << endl;
        cout << "4. Delite Compressor Station" << endl;
        cout << "5. View all objects" << endl;
        cout << "6. Edit Pipe" << endl;
        cout << "7. Edit Compressor Station" << endl;
        cout << "8. Batch Edit Pipes" << endl;
        cout << "9. Search Pipes" << endl;
        cout << "10. Search Stations" << endl;
        cout << "11. Save to file" << endl;
        cout << "12. Load from file" << endl;
        cout << "0. Exit" << endl;
        cin >> choice;
        if (cin.fail() || choice < 0 || choice > 11 || cin.peek() != '\n') {
            cout << "Invalid input. Please enter an integer. " << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        switch (choice) {
        case 1: {
            readPipe(pipes); // Reading data
            break;
        }
        case 2: {
            readst(stations); // Reading data
            break;
        }
        case 3: {
            delitepipes(pipes); // Reading data
            break;
        }
        case 4: {
            delitest(stations); // Reading data
            break;
        }
        case 5: {
            displayAllPipes(pipes); // Output data
            displayAllStations(stations); // Output data
            break;
        }
        case 6: {
            editPipe(pipes); // Editing status
            break;
        }
        case 7: {
            editStation(stations); // Change of workshop state
            break;
        }
        case 8: {
            batchPipes(pipes); break;
        }
        case 9: {
            searchPipes(pipes); break;
        }
        case 10: {
            searchStations(stations); break;
        }
        case 11: {
            string filename;
            cout << "Enter filename to save: ";
            cin >> filename;
            saveToFile(pipes, filename + "_pipes.txt");
            saveToFile(stations, filename + "_stations.txt");
            break;
        }
        case 12: {
            string filename;
            cout << "Enter filename to load: ";
            cin >> filename;
            loadFromFile(pipes, filename + "_pipes.txt");
            loadFromFile(stations, filename + "_stations.txt");
            break;
        }
        case 0: {
            return 0; // Exit the program
        }
        default: {
            cout << "Invalid choice!. Try again." << endl; // Incorrect choice
        }
               return 0;
        }
    }
}