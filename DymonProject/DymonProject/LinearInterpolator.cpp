//created by Wang Jianwei on 1 Dec 2012

#include "LinearInterpolator.h"

using namespace utilities;

typedef tuple<date, double> point;

LinearInterpolator::LinearInterpolator(point startPoint, point endPoint):
	AbstractInterpolator(startPoint, endPoint){}

point LinearInterpolator::interpolateS(date date0){
	
}
