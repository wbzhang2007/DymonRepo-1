//created by Wang Jianwei on 1 Dec 2012

#include "DepositRateBootStrapper.h"
#include <iostream>
#include <cmath>
#include "YieldCurve.h"
#include "InterpolatorFactory.h"
#include "AbstractInterpolator.h"
#include "NumericalFactory.h"
#include "AbstractBootStrapper.h"
#include "dateUtil.h"
#include "RecordHelper.h"
#define NaN -9999999 

using namespace utilities;

typedef AbstractBootStrapper super;

void DepositRateBootStrapper::init(Configuration* cfg){
	super::init(cfg);
}

AbstractInterpolator* DepositRateBootStrapper::bootStrap(){
	AbstractInterpolator* ai;
	enums::DayCountEnum dayCountCashConvention = _market.getDayCountCashConvention();
	if (_bizDaysAfterSpotDF != NaN){
		double accrualFactor = dateUtil::getAccrualFactor(_cashFlow.getAccuralStartDate(),_cashFlow.getAccuralEndDate(), dayCountCashConvention);
		double discountFactor = (1/(1+accrualFactor*_depositRate))*_bizDaysAfterSpotDF;
		ai = InterpolatorFactory::getInstance()->getInterpolator(_startPoint, point(_endDate,discountFactor) , _interpolAlgo);
	}else{
		AbstractNumerical<DepositRateBootStrapper>* an = NumericalFactory<DepositRateBootStrapper>::getInstance()->getNumerical(this,&DepositRateBootStrapper::numericalFunc,_numericAlgo);
		double previousVal = std::get<1>(_startPoint);
		double lowerBound = abs(previousVal*(1-_plusMinus/100.0));
		double upperBound = previousVal*(1+_plusMinus/100.0);
		double discountFactor = an->findRoot(lowerBound,upperBound,_tolerance,_iterateCount);
		ai = InterpolatorFactory::getInstance()->getInterpolator(_startPoint, point(_endDate,discountFactor) , _interpolAlgo);
	}
	return ai;
}

double DepositRateBootStrapper::numericalFunc(double x){
	point bsStartingPoint(_cashFlow.getFixingDate(),0);
	AbstractInterpolator* ai = InterpolatorFactory::getInstance()->getInterpolator(bsStartingPoint, point(_endDate,x) , _interpolAlgo);

	date bizDaysAfterSpotDate = _cashFlow.getAccuralStartDate();
	double accrualFactorStart = dateUtil::getAccrualFactor(_cashFlow.getFixingDate(),_cashFlow.getAccuralStartDate(), _dayCountCash);
	double accrualFactorEnd = dateUtil::getAccrualFactor(_cashFlow.getFixingDate(),_cashFlow.getAccuralEndDate(), _dayCountCash);
	double accrualFactorMid = dateUtil::getAccrualFactor(_cashFlow.getAccuralStartDate(),_cashFlow.getAccuralEndDate(), _dayCountCash);

	double zeroRateStart = std::get<1>(ai->interpolate(_cashFlow.getAccuralStartDate()));
	double zeroRateEnd = std::get<1>(ai->interpolate(_cashFlow.getAccuralEndDate()));
	double depositRateStart = (exp(accrualFactorStart*zeroRateStart)-1)/accrualFactorStart;
	double depositRateEnd = (exp(accrualFactorEnd*zeroRateEnd)-1)/accrualFactorEnd;

	double shouldBeZero = (1+_depositRate*accrualFactorMid)*depositRateStart - depositRateEnd;
	return shouldBeZero;
}