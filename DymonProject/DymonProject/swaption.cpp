//created by Hu Kun on 30 Nov 2012
#include "swaption.h"

using namespace utilities;
using namespace std;
using namespace enums;
using namespace instruments;

swaption::swaption(date optionStartDate, date optionExpiryDate, SwaptionVolSurface* vs,date swapStartDate, date swapMaturityDate,double notional, double couponRate, DiscountCurve* yc, currency fixLegCurr, currency floatingLegCurr, int paymentFreqFixLeg, int paymentFreqFloatingLeg, bool rollAccuralDates, int buildDirection){
	_underlyingSwap=swap(swapStartDate, swapMaturityDate, notional, couponRate, yc, fixLegCurr, floatingLegCurr, paymentFreqFixLeg, paymentFreqFloatingLeg, rollAccuralDates, buildDirection);
	double parRate=_underlyingSwap.getParRate(_underlyingSwap.getCashflowLegFloat(),_underlyingSwap.getCashflowLegFix(),yc);
	_optionOnSwap=option(optionStartDate, optionExpiryDate, vs,parRate );

}

swaption::~swaption() {

}

option swaption::getOption() {

	return _optionOnSwap;
}

instruments::swap swaption::getSwap() {

	return _underlyingSwap;
}