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

void AbstractInterpolator::dateInRangeCheck(date date0){
	if (date0.getJudianDayNumber()<getStartingJDN()){
		std::stringstream ss (stringstream::in | stringstream::out);
		ss<<"Date ["<<date0.getJudianDayNumber()<<"] is smaller than the line section starting date ["<<getStartingJDN()<<"]";
		throw ss.str();
	}else if (date0.getJudianDayNumber()>getEndingJDN()){
		std::stringstream ss (stringstream::in | stringstream::out);
		ss<<"Date ["<<date0.getJudianDayNumber()<<"] is larger than the line section ending date ["<<getEndingJDN()<<"]";
		throw ss.str();
	}
}