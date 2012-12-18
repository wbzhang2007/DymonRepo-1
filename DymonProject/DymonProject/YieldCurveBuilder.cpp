//created by Wang Jianwei on 1 Dec 2012
//Added cashflowleg creating - Kun
#include "YieldCurveBuilder.h"
#include <iostream>
#include "YieldCurve.h"
#include "BuilderCashFlowLeg.h"
#include "cashflow.h"
#include "cashflowLeg.h"
#include "EnumHelper.h"
#include "dateUtil.h"
#include "RecordHelper.h"
#include "DepositRateBootStrapper.h"

using namespace utilities;
typedef AbstractBuilder super;
typedef tuple<date, double> point;

void YieldCurveBuilder::init(Configuration* cfg){
	super::init(cfg);
	
	_currencyName = EnumHelper::getCcyEnum("USD");
	_dayCountCashConvention = EnumHelper::getDayCountEnum(cfg->getProperty("yieldcurve.usd.dayCountCashConvention",false,"ACT_360"));
	_dayCountSwapConvention = EnumHelper::getDayCountEnum(cfg->getProperty("yieldcurve.usd.dayCountSwapConvention",false,"ACT_ACT"));
	_dayRollConvention = EnumHelper::getDayRollEnum(cfg->getProperty("yieldcurve.usd.dayRollConvention",false,"Mfollowing"));
	_floatFreqency = std::stoi(cfg->getProperty("swap.usd.floatfreq",false,"4"));
	_fixFreqency = std::stoi(cfg->getProperty("swap.usd.fixfreq",false,"2"));
	_timeLineBuildDirection = std::stoi(cfg->getProperty("timeline.usd.builddirection",false,"1"));
	_rollAccuralDates =  cfg->getProperty("timeline.usd.rollaccuraldates",false,"0")=="0"?false:true;
	_interpolAlgo = EnumHelper::getInterpolAlgo(cfg->getProperty("yieldcurve.usd.interpol",false,"LINEAR"));
	_numericalAlgo = EnumHelper::getNumericalAlgo(cfg->getProperty("yieldcurve.usd.numerical",false,"BISECTION"));
}

YieldCurve* YieldCurveBuilder::build(){
	date startDate = dateUtil::getToday();
	currency cashFlowLegCurr=currency(_currencyName,_dayCountCashConvention, _dayCountSwapConvention, _dayRollConvention);

	BuilderCashFlowLeg builtCashflowLeg1(startDate,600,1,1, _floatFreqency, cashFlowLegCurr, _rollAccuralDates,RecordHelper::getInstance()->getHolidayMap());
	cashflowLeg _cashflowLeg=builtCashflowLeg1.getCashFlowLeg();
	vector<date> timeLine = _cashflowLeg.getAccuralDates();
	_cashflowLeg.printTimeLine();

	point startPoint(startDate, 0);
	YieldCurve* yc = new YieldCurve();
	
	map<long,double> rateMap = RecordHelper::getInstance()->getDepositRateMap()["USD"];
	for (map<long,double>::iterator it=rateMap.begin() ; it != rateMap.end(); it++ ){
		cout << (*it).first << " => " << (*it).second << endl;
		date endDate((*it).first);
		double depositRate = (*it).second;
		DepositRateBootStrapper depositBS(startPoint, endDate, depositRate,&timeLine, _interpolAlgo, _numericalAlgo, _dayCountCashConvention);
		AbstractInterpolator* lineSection = depositBS.bootStrap();
		yc->insertLineSection(lineSection);
		startPoint = lineSection->getEndPoint();
	}

	return yc;
}