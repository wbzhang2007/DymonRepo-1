//created by Wang Jianwei on 1 Dec 2012

#include "AbstractCurve.h"
#include <iostream>
#include <sstream>

using namespace utilities;
using namespace std;

typedef tuple<date, double> point;

AbstractCurve::AbstractCurve(std::vector<AbstractInterpolator>* lineSectionVector){
	_lineSectionVector = lineSectionVector;
}

void AbstractCurve::insertLineSection(AbstractInterpolator* lineSection){
	for (unsigned int i = 0; i<_lineSectionVector->size(); i++){
		long iterateStartingJDN = _lineSectionVector->at(i).getStartingJDN();
		if (iterateStartingJDN>=(*lineSection).getStartingJDN()){
			if (iterateStartingJDN<(*lineSection).getEndingJDN()){
				throw "LineSection miss match: "+ lineSection->toString();
			}
			_lineSectionVector->insert(_lineSectionVector->begin()+i,*lineSection);
		}
	}
}

double AbstractCurve::getValue(date date0){
	return 0;
}

void AbstractCurve::setLineSectionVector(std::vector<AbstractInterpolator>* lineSectionVector){
	_lineSectionVector = lineSectionVector;
}

bool AbstractCurve::validateLineSections(){
	bool validationPass = true;
	for (unsigned int i = 1; i<=_lineSectionVector->size(); i++){
		long nextStartJDN = _lineSectionVector->at(i).getStartingJDN();
		long previousEndJDN = _lineSectionVector->at(i-1).getEndingJDN();
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
	for (unsigned int i = 1; i<=_lineSectionVector->size(); i++){
		ss << _lineSectionVector->at(i).toString() <<"\n";
	}
	return ss.str();
}