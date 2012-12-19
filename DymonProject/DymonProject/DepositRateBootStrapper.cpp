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
	if (_bizDaysAfterSpotRate != NaN){
		double accrualFactor = dateUtil::getAccrualFactor(_cashFlow.getAccuralStartDate(),_cashFlow.getAccuralEndDate(), dayCountCashConvention);
		double cashPointValue = (log(1+accrualFactor*_depositRate)+1)*_bizDaysAfterSpotRate;
		ai = InterpolatorFactory::getInstance()->getInterpolator(_startPoint, point(_endDate,cashPointValue) , _interpolAlgo);
	}else{
		AbstractNumerical<DepositRateBootStrapper>* an = NumericalFactory<DepositRateBootStrapper>::getInstance()->getNumerical(this,&DepositRateBootStrapper::numericalFunc,_numericAlgo);
		double previousVal = std::get<1>(_startPoint);
		double cashPointValue = an->findRoot(previousVal*(1-_plusMinus/100),previousVal*(1+_plusMinus/100),_tolerance,_iterateCount);
		ai = InterpolatorFactory::getInstance()->getInterpolator(_startPoint, point(_endDate,cashPointValue) , _interpolAlgo);
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

	return (1+_depositRate)*depositRateStart - depositRateEnd;
}