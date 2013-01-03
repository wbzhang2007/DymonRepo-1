//created by Hu Kun on 30 Nov 2012
#include "swaption.h"
#include "Enums.h"
#include "AbstractOption.h"
#include "Swap.h"
#include "dateUtil.h"

using namespace utilities;
using namespace std;
using namespace enums;
using namespace instruments;

Swaption::Swaption(PayReceive PayReceiveInd, double T, double K, SwaptionVolCube* vc,date swapStartDate, int tenorNumOfMonths,double notional, double couponRate, DiscountCurve* yc, currency fixLegCurr, currency floatingLegCurr, int paymentFreqFixLeg, int paymentFreqFloatingLeg, bool rollAccuralDates, int buildDirection){
	Swap* _underlyingSwap= new Swap(swapStartDate, tenorNumOfMonths, notional, couponRate, yc, fixLegCurr, floatingLegCurr, paymentFreqFixLeg, paymentFreqFloatingLeg, rollAccuralDates, buildDirection);
	Swaption(PayReceiveInd, T, K, vc, yc, _underlyingSwap);	
}

Swaption::Swaption(PayReceive PayReceiveInd, double T, double K, SwaptionVolCube* vc,DiscountCurve* yc, Swap* underlyingSwap){
	_underlyingSwap = underlyingSwap;
	double parRate=underlyingSwap->getParRate(underlyingSwap->getCashflowLegFloat(),underlyingSwap->getCashflowLegFix(),yc);
	enum::DayCountEnum dc=underlyingSwap->getFixLegCurr().getDayCountSwapConvention();

	_tenorInMonth = _underlyingSwap->getTenor();
	double vol=vc->getVol(K,T,_tenorInMonth);
	double r=yc->getValue(s;

	//PayReceiver Indictor with respect to the fixed leg
	AbstractOption(dateUtil::getToday(), PayReceiveInd == Payer?Call:Put, parRate, K, vol, r, T);
}
		