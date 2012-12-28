#include "AbstractSurface.h"

using namespace utilities;
using namespace std;

void AbstractSurface::insertcurve(double majorAxisVal, AbstractCurve* curve){
	_curves->insert(pair<double, AbstractCurve*>(majorAxisVal,curve));
}

AbstractCurve* AbstractSurface::getcurve(double majorAxisVal){
	if (_curves->find(majorAxisVal) == _curves->end())
		throw "Major axis value not found on surface";
	return _curves->find(majorAxisVal)->second;
}

double AbstractSurface::getValue(double majorAxisVal, double minorAxisVal){
	AbstractCurve* curve=getcurve(majorAxisVal);
	return curve->getValue(
}

bool AbstractSurface::validatecurves(){
}

std::string  AbstractSurface::toString(){
}
