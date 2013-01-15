//created by Wang Jianwei on 1 Dec 2012

#include "BondRateBootStrapper.h"
#include <iostream>
#include <cmath>
#include "DiscountCurve.h"
#include "InterpolatorFactory.h"
#include "AbstractInterpolator.h"
#include "NumericalFactory.h"
#include "AbstractBootStrapper.h"
#include "dateUtil.h"
#include "RecordHelper.h"
#include "Constants.h"

using namespace utilities;

typedef AbstractBootStrapper<date> super;

void BondRateBootStrapper::init(Configuration* cfg){
	super::init(cfg);
}

AbstractInterpolator<date>* BondRateBootStrapper::bootStrap(){
	AbstractInterpolator<date>* ai;
	enums::DayCountEnum dayCountCashConvention = _market.getDayCountCashConvention();
	if (_bizDaysAfterSpotDF != NaN){
		double accrualFactor = dateUtil::getAccrualFactor(_cashFlow.getAccuralStartDate(),_cashFlow.getAccuralEndDate(), dayCountCashConvention);
		double discountFactor = (1/(1+accrualFactor*_couponRate))*_bizDaysAfterSpotDF;
		ai = InterpolatorFactory<date>::getInstance()->getInterpolator(_startPoint, point(_endDate,discountFactor) , _interpolAlgo);
	}else{
		AbstractNumerical<BondRateBootStrapper>* an = NumericalFactory<BondRateBootStrapper>::getInstance()->getNumerical(this,&BondRateBootStrapper::numericalFunc,_numericAlgo);
		double previousVal = std::get<1>(_startPoint);
		double lowerBound = abs(previousVal*(1-_plusMinus/100.0));
		double upperBound = previousVal*(1+_plusMinus/100.0);
		double discountFactor = an->findRoot(lowerBound,upperBound,_tolerance,_iterateCount);
		ai = InterpolatorFactory<date>::getInstance()->getInterpolator(_startPoint, point(_endDate,discountFactor) , _interpolAlgo);
	}
	return ai;
}

double BondRateBootStrapper::numericalFunc(double x){
	AbstractInterpolator<date>* ai = InterpolatorFactory<date>::getInstance()->getInterpolator(_startPoint, point(_endDate,x) , _interpolAlgo);

	date bizDaysAfterSpotDate = _cashFlow.getAccuralStartDate();
	double accrualFactorStart = dateUtil::getAccrualFactor(_cashFlow.getFixingDate(),_cashFlow.getAccuralStartDate(), _dayCountBond);
	double accrualFactorEnd = dateUtil::getAccrualFactor(_cashFlow.getFixingDate(),_cashFlow.getAccuralEndDate(), _dayCountBond);
	double accrualFactorMid = dateUtil::getAccrualFactor(_cashFlow.getAccuralStartDate(),_cashFlow.getAccuralEndDate(), _dayCountBond);

	double startDF = std::get<1>(ai->interpolate(_cashFlow.getAccuralStartDate()));
	double endDF = std::get<1>(ai->interpolate(_cashFlow.getAccuralEndDate()));

	double shouldBeZero = (1/(1+_couponRate*accrualFactorMid))*startDF - endDF;
	return shouldBeZero;
}