//created by Wang Jianwei on 1 Dec 2012
#include "BondCurveBuilder.h"
#include <iostream>
#include "BondCurve.h"
#include "BuilderCashFlowLeg.h"
#include "BondRateBootStrapper.h"
#include "cashflow.h"
#include "cashflowLeg.h"
#include "EnumHelper.h"
#include "dateUtil.h"
#include "RecordHelper.h"
#include "Constants.h"

using namespace utilities;
typedef AbstractBuilder super;
typedef tuple<date, double> point;

void BondCurveBuilder::init(Configuration* cfg){
	super::init(cfg);
	
	_market = Market(EnumHelper::getCcyEnum("USD"));
	_curveStartDate = dateUtil::dayRollAdjust(dateUtil::getToday(),enums::Following,_market.getMarketEnum());
	_interpolAlgo = EnumHelper::getInterpolAlgo(cfg->getProperty("BondCurve"+_market.getNameString()+"interpol",false,"CUBIC"));
	_numericalAlgo = EnumHelper::getNumericalAlgo(cfg->getProperty("BondCurve"+_market.getNameString()+"numerical",false,"BISECTION"));
}

BondCurve* BondCurveBuilder::build(Configuration* cfg){
	if (cfg!=NULL) init(cfg);
	BondCurve* bc = new BondCurve();
	buildSection(bc);
	return bc;
}


void BondCurveBuilder::buildSection(BondCurve* yc){
	point lineStartPoint(_curveStartDate,1);
	_curvePointer = lineStartPoint;
	map<long,Bond> rateMap = RecordHelper::getInstance()->getBondRateMap()[enums::USD];
	for (map<long,Bond>::iterator it=rateMap.begin(); it != rateMap.end(); it++ ){
		Bond bond = (*it).second;
		date startDate = _curveStartDate;
		int numOfNights = (int) (*it).first;
		date paymentDate = dateUtil::getBizDateOffSet(startDate,numOfNights,_market.getMarketEnum());
		//cout << "Overnight rate at date ["<<startDate.toString()<< "], maturity date ["<<paymentDate.toString()<<"], number of nights ["<<numOfNights<<"], rate ["<< depositRate<<"]"<< endl;

		cashflow cf(bond.getCouponRate(),0, startDate, paymentDate,startDate, paymentDate, _market);
		BondRateBootStrapper bondBS(_curvePointer, paymentDate, cf, _interpolAlgo, _numericalAlgo, _market, 0);
		bondBS.init(Configuration::getInstance());
		AbstractInterpolator<date>* lineSection = bondBS.bootStrap();
		yc->insertLineSection(lineSection);
		_curvePointer = lineSection->getEndPoint();
	}
}
