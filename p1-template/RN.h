#pragma once
#include <string>
#include "Station.h"
#include "Train.h"
//#include<iostream>

using namespace std;

class RN {
public:
	bool addTrain(string);
	bool addStation(string, string);
	bool addConnectionToStation(string, string);
	bool crossTrainByStation(string, string, int, bool);
	bool printCrossesStations(string);
	bool printStopsTrain(string);
private:
	Station* findStation(string);
	Train* findTrain(string);
};
