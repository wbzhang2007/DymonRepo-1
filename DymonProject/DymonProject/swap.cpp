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

Swap::Swap(date tradeDate, date maturityDate, double notional, double couponRate, DiscountCurve* yc, currency fixLegCurr, currency floatingLegCurr, int paymentFreqFixLeg, int paymentFreqFloatingLeg, bool rollAccuralDates, int buildDirection) {

	setTradeDate(tradeDate);
	setMaturityDate(maturityDate);

	BuilderCashFlowLeg fixLegs(tradeDate, maturityDate,couponRate,notional, paymentFreqFixLeg, fixLegCurr.getCurrencyEnum(),buildDirection);
	BuilderCashFlowLeg floatLegs(tradeDate, maturityDate,yc,notional, paymentFreqFloatingLeg, floatingLegCurr.getCurrencyEnum(), buildDirection);

	_fixCashflowLeg=fixLegs.getCashFlowLeg();
	_floatingCashflowLeg=floatLegs.getCashFlowLeg();
	_yc=yc;
	_fixLegCurr=fixLegCurr;
	_floatingLegCurr=floatingLegCurr;
	_paymentFreqFixLeg=paymentFreqFixLeg;
	_paymentFreqFloatingLeg=paymentFreqFloatingLeg;
}

Swap::Swap(date tradeDate, int tenorNumOfMonths, double notional, double couponRate, DiscountCurve* yc, currency fixLegCurr, currency floatingLegCurr, int paymentFreqFixLeg, int paymentFreqFloatingLeg, bool rollAccuralDates) {
	
	setTradeDate(tradeDate);
	setMaturityDate(dateUtil::getEndDate(tradeDate,tenorNumOfMonths,fixLegCurr.getDayRollSwapConvention(),fixLegCurr.getCurrencyEnum(),dateUtil::MONTH));

	BuilderCashFlowLeg fixLegs(tradeDate, tenorNumOfMonths,couponRate,notional, paymentFreqFixLeg, fixLegCurr.getCurrencyEnum());
	BuilderCashFlowLeg floatLegs(tradeDate, tenorNumOfMonths,yc,notional, paymentFreqFloatingLeg, floatingLegCurr.getCurrencyEnum());

	_fixCashflowLeg=fixLegs.getCashFlowLeg();
	_floatingCashflowLeg=floatLegs.getCashFlowLeg();
	_yc=yc;
	_fixLegCurr=fixLegCurr;
	_floatingLegCurr=floatingLegCurr;
	_paymentFreqFixLeg=paymentFreqFixLeg;
	_paymentFreqFloatingLeg=paymentFreqFloatingLeg;
	_tenorNumOfMonths=tenorNumOfMonths;	
}

currency Swap::getFixLegCurr() {
	return _fixLegCurr;
}

currency Swap::getFloatLegCurr() {
	return _floatingLegCurr;
}

int Swap::getPaymentFreqFixLeg() {
	return _paymentFreqFixLeg;
}

int Swap::getPaymentFreqFloatingLeg() {
	return _paymentFreqFloatingLeg;
}

cashflowLeg* Swap::getCashflowLegFix() {
	return _fixCashflowLeg;
}

cashflowLeg* Swap::getCashflowLegFloat() {
	return _floatingCashflowLeg;
}

void Swap::printCashflowLegFix() {
	_fixCashflowLeg->printCashFlowLeg();
}

void Swap::printCashflowLegFloat() {
	_floatingCashflowLeg->printCashFlowLeg();
}

DiscountCurve* Swap::getDiscountCurve() {
	return _yc;
}