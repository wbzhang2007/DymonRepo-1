//created by Hu Kun 04 Dec 2012
//rewrote again with cashflow constructs by Kun 16 Dec 2012
#include "swap.h"
#include <iterator>
#include "date.h"
#include "dateUtil.h"
#include "cashflow.h"
#include "cashflowLeg.h"
#include "BuilderCashFlowLeg.h"
#include "RecordHelper.h"
#include "SwapPricer.h"
#include "AbstractPricer.h"

using namespace instruments;
using namespace utilities;
using namespace std;
using namespace enums;

namespace instruments {
swap::swap(date tradeDate, date maturityDate, double notional, double couponRate, YieldCurve* yc, currency fixLegCurr, currency floatingLegCurr, int paymentFreqFixLeg, int paymentFreqFloatingLeg, bool rollAccuralDates, RecordHelper::HolidayMap holidayMap) {
	

	
	int buildDirection=1;

	setTradeDate(tradeDate);
	setMaturityDate(maturityDate);

	BuilderCashFlowLeg builtCashflowLeg1(tradeDate, maturityDate,couponRate,notional, paymentFreqFixLeg, fixLegCurr.getCurrencyEnum(),buildDirection);

	BuilderCashFlowLeg builtCashflowLeg2(tradeDate, maturityDate,yc,notional, paymentFreqFloatingLeg, floatingLegCurr.getCurrencyEnum(), buildDirection);
	
	_fixCashflowLeg=*builtCashflowLeg1.getCashFlowLeg();
	_floatingCashflowLeg=*builtCashflowLeg2.getCashFlowLeg();
}

swap::~swap() {

}

//double swap::calFLiborRate(date forwardStartDate, date forwardEndDate, double accuralFactor) {
//
//
//		return (_pricingYieldCurve.getDiscountFactor(forwardStartDate)/ _pricingYieldCurve.getDiscountFactor(forwardEndDate)-1)/accuralFactor;
//}

cashflowLeg swap::getCashflowLegFix() {
	return _fixCashflowLeg;
}

cashflowLeg swap::getCashflowLegFloat() {
	return _floatingCashflowLeg;
}
}

void swap::printCashflowLegFix() {
	_fixCashflowLeg.printCashFlowLeg();
}
void swap::printCashflowLegFloat() {

	_floatingCashflowLeg.printCashFlowLeg();
	
}

