//created by Wang Jianwei on 1 Dec 2012

#include "LinearInterpolator.h"

using namespace utilities;

typedef tuple<date, double> point;

LinearInterpolator::LinearInterpolator(point startPoint, point endPoint):
	AbstractInterpolator(startPoint, endPoint){}

point LinearInterpolator::interpolateS(date date0){
	double slope = (std::get<1>(_endPoint) - std::get<1>(_startPoint))/(std::get<0>(_endPoint).getJudianDayNumber() - std::get<0>(_startPoint).getJudianDayNumber());
	double yVal = slope*date0.getJudianDayNumber()+std::get<1>(_startPoint);
	return point(date0, yVal);
}


