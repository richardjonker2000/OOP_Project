#pragma once
#include <string>
#include"Station.h"
#include "Train.h"

using namespace std;

class Passage {
private:
	int id;
	//TDataHora datehour
	bool withStop;
	int line;
public:
	Passage(int, bool, int, Station*, Train*);

};