//created by Wang Jianwei on 1 Dec 2012

#include "AbstractInterpolator.h"

using namespace utilities;
using namespace std;


typedef tuple<date, double> point;

AbstractInterpolator::AbstractInterpolator(point startPoint, point endPoint){
	_startPoint = startPoint;
	_endPoint = endPoint;
}

vector<point> AbstractInterpolator::interpolateM(std::vector<date> dates){
	vector<point> pointVector;
	for (unsigned int i = 0; i<dates.size(); i++){
		pointVector.push_back(interpolateS(dates[i]));
	}
	return pointVector;
}
