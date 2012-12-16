//created by Wang Jianwei on 1 Dec 2012
//Added cashflowleg creating - Kun
#include "YieldCurveBuilder.h"
#include <iostream>
#include "YieldCurve.h"
#include "BuilderCashFlowLeg.h"
#include "cashflow.h"
#include "cashflowLeg.h"

using namespace utilities;
typedef AbstractBuilder super;

void YieldCurveBuilder::init(Configuration* cfg){
	super::init(cfg);
}

YieldCurve* YieldCurveBuilder::buildCurve(){

	date tradeDate(2013,11,2);
	date maturityDate(2015,2,6);
	
	//
	double notional=1000000;
	double couponRate=0.05;
	int paymentFreq=4;
	//build from start to end (build forward)
	int buildDirection=1;
	RecordHelper::HolidayMap holidayMap;
	bool rollAccuralDates=false;

	currency cashFlowLegCurr=currency(enums::USD,enums::ACT_360, enums::ACT_ACT, enums::Mfollowing);

	BuilderCashFlowLeg builtCashflowLeg1(tradeDate, maturityDate,couponRate,notional, paymentFreq, cashFlowLegCurr, rollAccuralDates, buildDirection,holidayMap);
	_cashflowLeg=builtCashflowLeg1.getCashFlowLeg();

	return new YieldCurve();
}