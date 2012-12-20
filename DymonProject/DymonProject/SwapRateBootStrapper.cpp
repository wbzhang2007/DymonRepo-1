//created by Wang Jianwei on 1 Dec 2012

#include "SwapRateBootStrapper.h"
#include <iostream>
#include "YieldCurve.h"
#include "InterpolatorFactory.h"
#include "AbstractInterpolator.h"
#include "NumericalFactory.h"
#include "dateUtil.h"
#include <cmath>

using namespace utilities;

void SwapRateBootStrapper::init(Configuration* cfg){
	_iterateCount = std::stoi(cfg->getProperty("numerical.iteration",true,"50"));
	_plusMinus = std::stoi(cfg->getProperty("numerical.plusminus",true,"20"));
	_tolerance = std::stod(cfg->getProperty("numerical.tolerance",true,"0.0000001"));
}

AbstractInterpolator* SwapRateBootStrapper::bootStrap(){
	
	_startIndex = findElementIndex(std::get<0>(_startPoint));
	_endIndex = findElementIndex(_endDate);

	AbstractNumerical<SwapRateBootStrapper>* an = NumericalFactory<SwapRateBootStrapper>::getInstance()->getNumerical(this,&SwapRateBootStrapper::numericalFunc,_numericAlgo);
	double previousVal = std::get<1>(_startPoint);
	double swapPointValue = an->findRoot(previousVal*(1-_plusMinus/100),previousVal*(1+_plusMinus/100),_tolerance,_iterateCount);

	AbstractInterpolator* ai = InterpolatorFactory::getInstance()->getInterpolator(_startPoint, point(_endDate,swapPointValue) , _interpolAlgo);
	return ai;
}

double SwapRateBootStrapper::numericalFunc(double x){
	
	AbstractInterpolator* ai = InterpolatorFactory::getInstance()->getInterpolator(_startPoint, point(_endDate,x) , _interpolAlgo);

	double numerator = 1 - exp(-x);
	double denominator = 0;

	for( unsigned int i=1; i<=_startIndex; i++){
		double ithAccuralFactor=dateUtil::getAccrualFactor(_timeLine[0],_timeLine[i],_dayCount)-dateUtil::getAccrualFactor(_timeLine[0],_timeLine[i-1],_dayCount);
		denominator = denominator + ithAccuralFactor*(*_curve).getDiscountFactor(_timeLine[i]);
	}
	for( unsigned int i=_startIndex+1; i<=_endIndex; i++){
		double ithAccuralFactor=dateUtil::getAccrualFactor(_timeLine[0],_timeLine[i],_dayCount)-dateUtil::getAccrualFactor(_timeLine[0],_timeLine[i-1],_dayCount);
		denominator = denominator + ithAccuralFactor*std::get<1>((*ai).interpolate(_timeLine[i]));
	}

	return numerator/denominator - _swapRate;
}

unsigned int SwapRateBootStrapper::findElementIndex(date date0){
	for(unsigned int i = 0; i < _timeLine.size(); i++)
	{
		if ( _timeLine[i].getJudianDayNumber() == date0.getJudianDayNumber()){
			return i;
		}
	}
	throw "Date not found in time line: " + date0.getJudianDayNumber();
}