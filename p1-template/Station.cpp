#include <string>
#include "Station.h"
using namespace std;

Station::Station() {
	acronym = "";
	local = "";
}

Station::Station(string sgl, string loc) {
	acronym = sgl;
	local = loc;
}