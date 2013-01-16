//created by Wang Jianwei on 1 Dec 2012
#include "BondCurveBuilder.h"
#include <iostream>
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

void BondDiscountCurveBuilder::init(Configuration* cfg){
	super::init(cfg);
	
	_market = Market(EnumHelper::getCcyEnum("USD"));
	_curveStartDate = dateUtil::dayRollAdjust(dateUtil::getToday(),enums::Following,_market.getMarketEnum());
	_interpolAlgo = EnumHelper::getInterpolAlgo(cfg->getProperty("BondDiscountCurve"+_market.getNameString()+"interpol",false,"CUBIC"));
	_numericalAlgo = EnumHelper::getNumericalAlgo(cfg->getProperty("BondDiscountCurve"+_market.getNameString()+"numerical",false,"BISECTION"));
}

DiscountCurve* BondDiscountCurveBuilder::build(Configuration* cfg){
	if (cfg!=NULL) init(cfg);
	DiscountCurve* bc = new DiscountCurve();
	buildSection(bc);
	return bc;
}


void BondDiscountCurveBuilder::buildSection(DiscountCurve* dc){
	point lineStartPoint(_curveStartDate,1);
	_curvePointer = lineStartPoint;
	map<long,Bond> rateMap = RecordHelper::getInstance()->getBondRateMap()[enums::USD];
	for (map<long,Bond>::iterator it=rateMap.begin(); it != rateMap.end(); it++ ){
		Bond bond = (*it).second;
		int numOfNights = (int) (*it).first;
		date paymentDate = bond.getMaturityDate();
		BondRateBootStrapper bondBS(_curvePointer, paymentDate, bond, dc, _interpolAlgo, _numericalAlgo, _market);
		bondBS.init(Configuration::getInstance());
		AbstractInterpolator<date>* lineSection = bondBS.bootStrap();
		dc->insertLineSection(lineSection);
		_curvePointer = lineSection->getEndPoint();
	}
}
