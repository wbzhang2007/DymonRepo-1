//created by Hu Kun on 30 Nov 2012

#ifndef SWAPTION_H
#define SWAPTION_H
#include "currency.h"
#include "date.h"
#include "AbstractInstrument.h"
#include <vector>
#include "zero.h"
#include <tuple>
#include <iterator>
#include "cashflow.h"
#include "cashflowLeg.h"
#include "BuilderCashFlowLeg.h"
#include "RecordHelper.h"
#include "SwapPricer.h"
#include "AbstractPricer.h"
#include "DiscountCurve.h"
#include "Swap.h"
#include "AbstractOption.h"
#include "SwaptionVolSurface.h"
#include "SwaptionVolCube.h"

using namespace utilities;
using namespace std;
using namespace enums;
using namespace instruments;


namespace instruments {
	class Swaption:  public Swap, public AbstractOption {
		
		Swaption(){};
		~Swaption(){};
		Swaption(PayReceive PayReceiveInd, double T, double K, SwaptionVolCube* vs, date swapStartDate, int tenorNumOfMonths,double notional, double couponRate, DiscountCurve* yc, currency fixLegCurr, currency floatingLegCurr, int paymentFreqFixLeg, int paymentFreqFloatingLeg, bool rollAccuralDates, int buildDirection);
		Swaption(PayReceive PayReceiveInd, double T, double K, SwaptionVolCube* vs, DiscountCurve* yc, Swap* underlyingSwap);
		
		Swap* getSwap(){ return _underlyingSwap; }

	private:		

		int _tenorInMonth;
		date _expiryDate;
		Swap* _underlyingSwap;

	};
}
#endif