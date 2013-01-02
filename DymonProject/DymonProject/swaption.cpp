//created by Hu Kun on 30 Nov 2012
#include "swaption.h"
#include "Enums.h"

using namespace utilities;
using namespace std;
using namespace enums;
using namespace instruments;

swaption::swaption(PayReceive PayReceiveInd, date optionStartDate, date optionExpiryDate, double optionStrike, SwaptionVolCube* vs,date swapStartDate, date swapMaturityDate,double notional, double couponRate, DiscountCurve* yc, currency fixLegCurr, currency floatingLegCurr, int paymentFreqFixLeg, int paymentFreqFloatingLeg, bool rollAccuralDates, int buildDirection){
	_underlyingSwap=swap(swapStartDate, swapMaturityDate, notional, couponRate, yc, fixLegCurr, floatingLegCurr, paymentFreqFixLeg, paymentFreqFloatingLeg, rollAccuralDates, buildDirection);
	double parRate=_underlyingSwap.getParRate(_underlyingSwap.getCashflowLegFloat(),_underlyingSwap.getCashflowLegFix(),yc);
	
	enum::DayCountEnum dc=_underlyingSwap.getFixLegCurr().getDayCountSwapConvention();

	double vol=0;
	double r=0.0;

	//PayReceiver Indictor with respect to the fixed leg
	if (PayReceiveInd == Payer) {
		_optionOnSwap=AbstractOption(optionStartDate, Call, parRate, optionStrike, vol, r, optionExpiryDate, dc);
	}
	else {
		_optionOnSwap=AbstractOption(optionStartDate, Put, parRate, optionStrike, vol, r, optionExpiryDate, dc);
	}
	
}

swaption::~swaption() {

}

AbstractOption swaption::getOption() {

	return _optionOnSwap;
}

instruments::swap swaption::getSwap() {

	return _underlyingSwap;
}