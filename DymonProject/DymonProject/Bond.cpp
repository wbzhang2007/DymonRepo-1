//created by Wang Jianwei 04 Dec 2012
//rewrote again with cashflow constructs by Kun 16 Dec 2012
#include "bond.h"
#include <iterator>
#include "date.h"
#include "dateUtil.h"
#include "cashflow.h"
#include "cashflowLeg.h"
#include "BuilderCashFlowLeg.h"
#include "RecordHelper.h"
#include "AbstractPricer.h"

using namespace instruments;
using namespace utilities;
using namespace std;
using namespace enums;

Bond::Bond(Market market, date tradeDate, date maturityDate, double notional, double couponRate, BondCurve* bc, int couponFreq, bool rollAccuralDates, int buildDirection){
	BaseBond(market, tradeDate, maturityDate, notional, couponRate, couponFreq, rollAccuralDates, buildDirection);
	_bc=bc;
};

Bond::Bond(Market market, date tradeDate, date maturityDate, double couponRate, Configuration* cfg, double cleanPrice){
	int couponFreq = std::stoi(cfg->getProperty("convention."+market.getNameString()+".bond.couponfreq",false,"2"));
	int timeLineBuildDirection = std::stoi(cfg->getProperty("BondCurve."+market.getNameString()+".buildCashFlowDirection",false,"1"));
	bool rollAccuralDates =  cfg->getProperty("BondCurve."+market.getNameString()+".rollAccuralDates",false,"0")=="0"?false:true;

	BaseBond(market, tradeDate, maturityDate, 100, couponRate, couponFreq, rollAccuralDates, timeLineBuildDirection);
	_cleanPrice = cleanPrice;
	date firstCouponDate = _couponLeg->getCashFlowLeg()[1].getAccuralEndDate();
	double accrualFactor = dateUtil::getAccrualFactor(getTradeDate(),firstCouponDate,market.getDayCountBondConvention());
	_dirtyPrice = cleanPrice + couponRate/couponFreq*accrualFactor;
}

void Bond::BaseBond(Market market, date tradeDate, date maturityDate, double notional, double couponRate, int couponFreq, bool rollAccuralDates, int buildDirection){

	setTradeDate(tradeDate);
	setMaturityDate(maturityDate);

	BuilderCashFlowLeg* couponLegs = new BuilderCashFlowLeg(tradeDate, maturityDate,couponRate,notional, couponFreq, market.getMarketEnum(),buildDirection);

	_couponLeg=couponLegs->getCashFlowLeg();
	_market=market;
	_couponFreq=couponFreq;
}

Bond::Bond(Market market, date tradeDate, int tenorNumOfMonths, double notional, double couponRate, BondCurve* bc, int couponFreq, bool rollAccuralDates){
	
	setTradeDate(tradeDate);
	setMaturityDate(dateUtil::getEndDate(tradeDate,tenorNumOfMonths,market.getDayRollSwapConvention(),market.getMarketEnum(),dateUtil::MONTH));

	BuilderCashFlowLeg* couponLegs = new BuilderCashFlowLeg(tradeDate, tenorNumOfMonths,couponRate,notional, couponFreq, market.getMarketEnum());

	_couponLeg=couponLegs->getCashFlowLeg();
	_bc=bc;
	_market=market;
	_couponFreq=couponFreq;
	_tenorNumOfMonths=tenorNumOfMonths;	
}