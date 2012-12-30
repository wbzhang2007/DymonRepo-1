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

swap::swap(date tradeDate, int tenorNumOfMonths, double notional, double couponRate, DiscountCurve* yc, currency fixLegCurr, currency floatingLegCurr, int paymentFreqFixLeg, int paymentFreqFloatingLeg, bool rollAccuralDates) {

	BuilderCashFlowLeg fixLegs(tradeDate, tenorNumOfMonths,couponRate,notional, paymentFreqFixLeg, fixLegCurr.getCurrencyEnum());
	BuilderCashFlowLeg floatLegs(tradeDate, tenorNumOfMonths,yc,notional, paymentFreqFloatingLeg, floatingLegCurr.getCurrencyEnum());

	_fixCashflowLeg=*fixLegs.getCashFlowLeg();
	_floatingCashflowLeg=*floatLegs.getCashFlowLeg();
	_yc=*yc;

	_fixLegCurr=fixLegCurr;
	_floatingLegCurr=floatingLegCurr;
	_paymentFreqFixLeg=paymentFreqFixLeg;
	_paymentFreqFloatingLeg=paymentFreqFloatingLeg;

	
}

currency swap::getFixLegCurr() {
	return _fixLegCurr;
}

currency swap::getFloatLegCurr() {
	return _floatingLegCurr;
}

int swap::getPaymentFreqFixLeg() {
	return _paymentFreqFixLeg;
}

int swap::getPaymentFreqFloatingLeg() {
	return _paymentFreqFloatingLeg;
}

swap::swap(date tradeDate, date maturityDate, double notional, double couponRate, DiscountCurve* yc, currency fixLegCurr, currency floatingLegCurr, int paymentFreqFixLeg, int paymentFreqFloatingLeg, bool rollAccuralDates, int buildDirection) {

	setTradeDate(tradeDate);
	setMaturityDate(maturityDate);

	BuilderCashFlowLeg fixLegs(tradeDate, maturityDate,couponRate,notional, paymentFreqFixLeg, fixLegCurr.getCurrencyEnum(),buildDirection);
	BuilderCashFlowLeg floatLegs(tradeDate, maturityDate,yc,notional, paymentFreqFloatingLeg, floatingLegCurr.getCurrencyEnum(), buildDirection);

	_fixCashflowLeg=*fixLegs.getCashFlowLeg();
	_floatingCashflowLeg=*floatLegs.getCashFlowLeg();
	_yc=*yc;
}

cashflowLeg* swap::getCashflowLegFix() {
	return &_fixCashflowLeg;
}

cashflowLeg* swap::getCashflowLegFloat() {
	return &_floatingCashflowLeg;
}

void swap::printCashflowLegFix() {
	_fixCashflowLeg.printCashFlowLeg();
}

void swap::printCashflowLegFloat() {
	_floatingCashflowLeg.printCashFlowLeg();
}

//double swap::getParRate() {
//	return SwapPricer::getParRate(&_floatingCashflowLeg,&_fixCashflowLeg,&_yc);
//}

DiscountCurve* swap::getDiscountCurve() {

	return &_yc;
}