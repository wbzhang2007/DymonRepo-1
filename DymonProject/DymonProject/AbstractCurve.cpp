//created by Wang Jianwei on 1 Dec 2012

#include "AbstractCurve.h"
#include <iostream>
#include <sstream>

using namespace utilities;
using namespace std;

typedef tuple<date, double> point;

AbstractCurve::AbstractCurve(std::vector<AbstractInterpolator*>* lineSectionVector){
	_lineSectionVector = lineSectionVector;
}

void AbstractCurve::insertLineSection(AbstractInterpolator* lineSection){
	if (_lineSectionVector->size()==0){
		_lineSectionVector->insert(_lineSectionVector->begin(),lineSection);
	} else{
		int vectorSize = _lineSectionVector->size();
		_lineSectionVector->insert(_lineSectionVector->begin()+vectorSize,lineSection);
	}
}

double AbstractCurve::getValue(date date0){
	long startJDN, endJDN;
	for (unsigned int i = 0; i<_lineSectionVector->size(); i++){
		startJDN = _lineSectionVector->at(i)->getStartingJDN();
		endJDN = _lineSectionVector->at(i)->getEndingJDN();
		if (startJDN<=date0.getJudianDayNumber() && date0.getJudianDayNumber()<=endJDN){
			AbstractInterpolator* ai= _lineSectionVector->at(i);
			point pointOnCurve = ai->interpolate(date0);
			return std::get<1>(pointOnCurve);
		}
	}
	throw "Point not found on curve for date: "+date0.toString();
}

void AbstractCurve::setLineSectionVector(std::vector<AbstractInterpolator*>* lineSectionVector){
	_lineSectionVector = lineSectionVector;
}

bool AbstractCurve::validateLineSections(){
	bool validationPass = true;
	for (unsigned int i = 1; i<=_lineSectionVector->size(); i++){
		long nextStartJDN = _lineSectionVector->at(i)->getStartingJDN();
		long previousEndJDN = _lineSectionVector->at(i-1)->getEndingJDN();
		if (nextStartJDN!=previousEndJDN){
			cout<<"Curve gap detected: "<<previousEndJDN<< " " <<nextStartJDN<<endl;
			validationPass = false;
		}
	}
	return validationPass;
}

string AbstractCurve::toString(){
	std::stringstream ss (stringstream::in | stringstream::out);
	ss << "Curve - Line sections: \n";
	for (unsigned int i = 0; i<_lineSectionVector->size(); i++){
		ss << _lineSectionVector->at(i)->toString() <<"\n";
	}
	return ss.str();
}