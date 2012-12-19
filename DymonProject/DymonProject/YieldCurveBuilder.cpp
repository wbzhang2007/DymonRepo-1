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
#include "OvernightRateBootStrapper.h"
#define NaN log(-1.0) 

using namespace utilities;
typedef AbstractBuilder super;
typedef tuple<date, double> point;

void YieldCurveBuilder::init(Configuration* cfg){
	super::init(cfg);
	
	_market = currency(EnumHelper::getCcyEnum("USD"));
	_floatFreqency = std::stoi(cfg->getProperty("swap.usd.floatfreq",false,"4"));
	_fixFreqency = std::stoi(cfg->getProperty("swap.usd.fixfreq",false,"2"));
	_timeLineBuildDirection = std::stoi(cfg->getProperty("timeline.usd.builddirection",false,"1"));
	_rollAccuralDates =  cfg->getProperty("timeline.usd.rollaccuraldates",false,"0")=="0"?false:true;
	_interpolAlgo = EnumHelper::getInterpolAlgo(cfg->getProperty("yieldcurve.usd.interpol",false,"LINEAR"));
	_numericalAlgo = EnumHelper::getNumericalAlgo(cfg->getProperty("yieldcurve.usd.numerical",false,"BISECTION"));
	_bizDaysAfterSpot = _market.getBusinessDaysAfterSpot();
	_bizDaysAfterSpotRate = NaN;
}

YieldCurve* YieldCurveBuilder::build(){
	YieldCurve* yc = new YieldCurve();
	buildOvernightSection(yc);
	//buildDepositSection(yc);
	//buildSwapSection(yc);
	return yc;
}

void YieldCurveBuilder::buildOvernightSection(YieldCurve* yc){
	point lineStartPoint(dateUtil::getToday(), 0);
	_curvePointer = lineStartPoint;
	map<long,double> rateMap = RecordHelper::getInstance()->getOverNightRateMap()[enums::USD];
	for (map<long,double>::iterator it=rateMap.begin(); it != rateMap.end(); it++ ){
		double depositRate = (*it).second;
		date startDate = dateUtil::getToday();
		int numOfNights = (int) (*it).first;
		date paymentDate = dateUtil::getBizDateOffSet(startDate,numOfNights,_market.getCurrencyEnum());
		cout << "Overnight rate at date ["<<startDate.toString()<< "], maturity date ["<<paymentDate.toString()<<
			"], number of nights ["<<numOfNights<<"], rate ["<< depositRate<<"]"<< endl;

		cashflow cf(depositRate,0, startDate, paymentDate,startDate, paymentDate, _market);
		OvernightRateBootStrapper overnightBS(_curvePointer, paymentDate, cf, _interpolAlgo, _numericalAlgo, _market);
		AbstractInterpolator* lineSection = overnightBS.bootStrap();
		yc->insertLineSection(lineSection);
		_curvePointer = lineSection->getEndPoint();

		if (numOfNights = _bizDaysAfterSpot) _bizDaysAfterSpotRate = std::get<1>(lineSection->getEndPoint());
	}
}

void YieldCurveBuilder::buildDepositSection(YieldCurve* yc){
	date accrualStartDate = dateUtil::getBizDateOffSet(dateUtil::getToday(),_market.getBusinessDaysAfterSpot(),enums::USD);
	map<long,double> rateMap = RecordHelper::getInstance()->getDepositRateMap()[enums::USD];

	for (map<long,double>::iterator it=rateMap.begin(); it != rateMap.end(); it++ ){

		date fixingDate = dateUtil::getToday();
		date accrualEndDate((*it).first);
		date paymentDate = dateUtil::dayRollAdjust(accrualEndDate,_market.getDayRollSwapConvention(),enums::USD);
		double depositRate = (*it).second;

		cout << "Deposit rate at fixing date ["<<fixingDate.toString()<<"], accrual start date ["<<accrualStartDate.toString()<<
			"], accrual end date ["<<accrualEndDate.toString()<<"], payment day ["<<paymentDate.toString()<<"], rate ["<< depositRate<<"]"<< endl;

		cashflow cf(depositRate,0, fixingDate, paymentDate,accrualStartDate, accrualEndDate, _market);

		AbstractInterpolator* lineSection;
		if (_bizDaysAfterSpotRate == NaN){
			DepositRateBootStrapper depositBS(_curvePointer, paymentDate, cf, _interpolAlgo, _numericalAlgo, _market);
			lineSection = depositBS.bootStrap();
			_bizDaysAfterSpotRate = std::get<1>(lineSection->getEndPoint());
		}else{
			DepositRateBootStrapper depositBS(_curvePointer, paymentDate, cf, _interpolAlgo, _numericalAlgo, _market);
			lineSection = depositBS.bootStrap();
		}
		yc->insertLineSection(lineSection);
		_curvePointer = lineSection->getEndPoint();
	}

}

void YieldCurveBuilder::buildSwapSection(YieldCurve* yc){
	//currency market(enums::USD);
	//date startDate = dateUtil::getBizDateOffSet(dateUtil::getToday(),market.getBusinessDaysAfterSpot(),enums::USD);
	//	BuilderCashFlowLeg builtCashflowLeg(startDate,600,1,1, _floatFreqency, enums::USD);
	//cashflowLeg _cashflowLeg=builtCashflowLeg.getCashFlowLeg();
	//vector<date> timeLine = _cashflowLeg.getAccuralDates();
	//_cashflowLeg.printTimeLine();


}