//created by Wang Jianwei on 1 Dec 2012

#include "YieldCurve.h"

using namespace utilities;
using namespace std;

typedef tuple<date, double> point;
typedef AbstractCurve super;

void YieldCurve::insertLineSection(const AbstractInterpolator& lineSection){
	super::insertLineSection(lineSection);
}

double YieldCurve::getY(date date0){
	return super::getY(date0);
}
