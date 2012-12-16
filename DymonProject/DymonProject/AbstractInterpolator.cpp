//created by Wang Jianwei on 1 Dec 2012

#include "AbstractInterpolator.h"
#include <iostream>
#include <sstream>

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
		pointVector.push_back(interpolate(dates[i]));
	}
	return pointVector;
}

point AbstractInterpolator::interpolate(date date0){
	return point(NULL,0);
}

point AbstractInterpolator::getStartPoint(){
	return _startPoint;
}

point AbstractInterpolator::getEndPoint(){
	return _endPoint;
}

long AbstractInterpolator::getStartingJDN(){
	point start = getStartPoint();
	return std::get<0>(start).getJudianDayNumber();
}

long AbstractInterpolator::getEndingJDN(){
	point end = getEndPoint();
	return std::get<0>(end).getJudianDayNumber();
}

string AbstractInterpolator::toString(){
	std::stringstream ss (stringstream::in | stringstream::out);
	ss << "line section from {";
	ss << std::get<0>(_startPoint).toString() << "," <<std::get<1>(_startPoint)<<"} to {";
	ss << std::get<0>(_endPoint).toString() << "," <<std::get<1>(_endPoint)<<"}";
	return ss.str();
}