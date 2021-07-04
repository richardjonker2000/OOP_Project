#include <string>
#include "Passage.h"
#include "Train.h"
#include "Station.h"
using namespace std;

Passage::Passage(int id, bool para, int lin, Station* e, Train* c) {
	Passage::id = id;
	//date
	withStop = para;
	line = lin;
	//station
	//train

}

