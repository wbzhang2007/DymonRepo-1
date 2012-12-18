//created by Wang Jianwei on 1 Dec 2012
#include "AbstractTest.h"
#include <iostream>
#include <sstream>

using namespace UnitTest;
using namespace std;

bool AbstractTest::compareResult(double derivedVal, double expectedVal){
	if (abs(derivedVal-expectedVal)>_EPSILON)
		return false;
	return true;
}

bool AbstractTest::compareResult(std::string derivedVal, std::string expectedVal){
	if (derivedVal==expectedVal){
		return true;
	}
	return false;
}

string AbstractTest::getString(point point0){
	std::stringstream ss (stringstream::in | stringstream::out);
	ss<<std::get<0>(point0).toString()<<": "<<std::get<1>(point0);
	return ss.str();
}