//created by Wang Jianwei on 1 Dec 2012

#include "AbstractCurve.h"

using namespace utilities;
using namespace std;

typedef tuple<date, double> point;

AbstractCurve::AbstractCurve(){
}

AbstractCurve::AbstractCurve(std::vector<AbstractInterpolator>* lineSectionVector){
	_lineSectionVector = lineSectionVector;
}

void AbstractCurve::insertLineSection(const AbstractInterpolator& lineSection){
}

double AbstractCurve::getY(date date0){
	return 0;
}

void AbstractCurve::setLineSectionVector(std::vector<AbstractInterpolator>* lineSectionVector){
	_lineSectionVector = lineSectionVector;
}