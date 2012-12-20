//created by Wang Jianwei on 1 Dec 2012
//minor modifications for numericalFunc on 19 Dec - Kun for accuralFactor

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
	
	_cashflowStartIndex = findCashFlowIndex(std::get<0>(_startPoint));
	_cashflowEndIndex = findCashFlowIndex(_endDate);

	AbstractNumerical<SwapRateBootStrapper>* an = NumericalFactory<SwapRateBootStrapper>::getInstance()->getNumerical(this,&SwapRateBootStrapper::numericalFunc,_numericAlgo);
	double previousVal = std::get<1>(_startPoint);
	double lowerBound = 0; // previousVal*(1-_plusMinus/100.0);
	double upperBound = (1+_plusMinus/100.0); //previousVal*(1+_plusMinus/100.0);
	double swapPointValue = an->findRoot(lowerBound,upperBound,_tolerance,_iterateCount);

	AbstractInterpolator* ai = InterpolatorFactory::getInstance()->getInterpolator(_startPoint, point(_endDate,swapPointValue) , _interpolAlgo);
	return ai;
}

double SwapRateBootStrapper::numericalFunc(double x){
	
	AbstractInterpolator* ai = InterpolatorFactory::getInstance()->getInterpolator(_startPoint, point(_endDate,x) , _interpolAlgo);

	double numerator = 1 - x;
	double denominator = 0;

	for( unsigned int i=0; i<=_cashflowStartIndex; i++){
		cashflow ithCashFlow = _cashflowVector[i];
		double ithAccuralFactor=dateUtil::getAccrualFactor(ithCashFlow.getAccuralStartDate(),ithCashFlow.getAccuralEndDate(),_dayCount);
		double ithDF = _curve->getDiscountFactor(ithCashFlow.getPaymentDate());
		denominator = denominator + ithAccuralFactor*ithDF;
	}
	for( unsigned int i=_cashflowStartIndex+1; i<=_cashflowEndIndex; i++){
		cashflow ithCashFlow = _cashflowVector[i];
		double ithAccuralFactor=dateUtil::getAccrualFactor(ithCashFlow.getAccuralStartDate(),ithCashFlow.getAccuralEndDate(),_dayCount);
		denominator = denominator + ithAccuralFactor*std::get<1>(ai->interpolate(ithCashFlow.getPaymentDate()));
	}

	return numerator - _swapRate*denominator;
}

unsigned int SwapRateBootStrapper::findCashFlowIndex(date date0){
	for(unsigned int i = 0; i < _cashflowVector.size(); i++)
	{
		cashflow ithCashFlow = _cashflowVector[i];
		if ( ithCashFlow.getPaymentDate().getJudianDayNumber() == date0.getJudianDayNumber()){
			return i;
		}
	}
	throw "Date not found in all accrual dates: " + date0.getJudianDayNumber();
}