//created by Wang Jianwei on 1 Dec 2012

#include "YieldCurve.h"
#include <cmath>

using namespace utilities;
using namespace std;

typedef tuple<date, double> point;
typedef AbstractCurve super;

void YieldCurve::insertLineSection(AbstractInterpolator* lineSection){
	super::insertLineSection(lineSection);
}

double YieldCurve::getValue(date date0){
	return super::getValue(date0);
}

double YieldCurve::getDiscountFactor(date date0){
	return exp(-getValue(date0));
}

std::string YieldCurve::toString(){
	return "\nYield "+AbstractCurve::toString();
}