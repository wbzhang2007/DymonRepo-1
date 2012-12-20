//created by Wang Jianwei on 1 Dec 2012

#include "LinearInterpolator.h"
#define NaN -999999

using namespace utilities;

typedef tuple<date, double> point;

LinearInterpolator::LinearInterpolator(point startPoint, point endPoint):
AbstractInterpolator(startPoint, endPoint){
	_slope = NaN;
	_algo = enums::LINEAR;
}

point LinearInterpolator::interpolate(date date0){
	dateInRangeCheck(date0);
	if (_slope == NaN){
		double yDiff = std::get<1>(_endPoint) - std::get<1>(_startPoint);
		double xDiff = std::get<0>(_endPoint).getJudianDayNumber() - std::get<0>(_startPoint).getJudianDayNumber();
		_slope = yDiff / xDiff;
	}
	double yVal = _slope*(date0.getJudianDayNumber() - std::get<0>(_startPoint).getJudianDayNumber())+std::get<1>(_startPoint);
	return point(date0, yVal);
}


