//created by Wang Jianwei on 1 Dec 2012

#include "LinearInterpolator.h"

using namespace utilities;

typedef tuple<date, double> point;

LinearInterpolator::LinearInterpolator(point startPoint, point endPoint):
	AbstractInterpolator(startPoint, endPoint){}

point LinearInterpolator::interpolate(date date0){
	double yDiff = std::get<1>(_endPoint) - std::get<1>(_startPoint);
	double xDiff = std::get<0>(_endPoint).getJudianDayNumber() - std::get<0>(_startPoint).getJudianDayNumber();
	double slope = yDiff / xDiff;
	double yVal = slope*date0.getJudianDayNumber()+std::get<1>(_startPoint);
	return point(date0, yVal);
}


