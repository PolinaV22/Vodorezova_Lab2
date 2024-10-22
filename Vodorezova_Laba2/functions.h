#pragma once
#include <string>
#include <map>
#include <iostream>
#include "Cpipes.h"
#include "Compressor_St.h"
#include <vector>
#include <fstream>

class functions
{
public:
	void logAction(const std::string& action);
	void readPipe(std::map<int, Cpipes>& pipes);
	void displayAllPipes(std::map<int, Cpipes>& pipes);
	void delitepipes(std::map<int, Cpipes>& pipes);
	void editPipe(std::map<int, Cpipes>& pipes);
	void batchPipes(std::map<int, Cpipes>& pipes);
	void readst(std::map<int, Compressor_St>& stations);
	void delitest(std::map<int, Compressor_St>& stations);
	void displayAllStations(std::map<int, Compressor_St>& stations);
	void editStation(std::map<int, Compressor_St>& stations);
	void searchPipes(std::map<int, Cpipes>& pipes);
	void searchStations(std::map<int, Compressor_St>& stations);

};

