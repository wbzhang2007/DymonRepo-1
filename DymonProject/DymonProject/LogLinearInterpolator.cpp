//created by Wang Jianwei on 1 Dec 2012

#include "LogLinearInterpolator.h"
#include <math.h>

using namespace utilities;

typedef tuple<date, double> point;

LogLinearInterpolator::LogLinearInterpolator(point startPoint, point endPoint):
	AbstractInterpolator(startPoint, endPoint){}

point LogLinearInterpolator::interpolate(date date0){
	double yDiff = log(std::get<1>(_endPoint)) - log(std::get<1>(_startPoint));
	double xDiff = std::get<0>(_endPoint).getJudianDayNumber() - std::get<0>(_startPoint).getJudianDayNumber();
	double slope = yDiff / xDiff;
	double yVal = slope*date0.getJudianDayNumber()+ log(std::get<1>(_startPoint));
	return point(date0, exp(yVal));
}