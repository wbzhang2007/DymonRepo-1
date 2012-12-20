//created by Wang Jianwei on 1 Dec 2012

#include "YieldCurve.h"
#include <cmath>
#include "dateUtil.h"
#include "Enums.h"

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
	return getValue(date0);
}

double YieldCurve::getFLiborRate(date forwardStartDate,date forwardEndDate,enums::DayCountEnum dayCount) {
	double cal=getDiscountFactor(forwardStartDate)/getDiscountFactor(forwardEndDate);

	return (cal-1)/dateUtil::getAccrualFactor(forwardStartDate,forwardEndDate,dayCount);
}

std::string YieldCurve::toString(){
	return "\nYield "+AbstractCurve::toString();
}