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
#include "swap.h"
#include "option.h"

using namespace utilities;
using namespace std;
using namespace enums;
using namespace instruments;


namespace instruments {
	class swaption:  public swap, public option {

		swaption(date optionStartDate, date optionExpiryDate, VolSurface* vs,date swapStartDate, date swapMaturityDate,double notional, double couponRate, DiscountCurve* yc, currency fixLegCurr, currency floatingLegCurr, int paymentFreqFixLeg, int paymentFreqFloatingLeg, bool rollAccuralDates, int buildDirection);
		~swaption();

		option getOption();
		swap getSwap();


	private:
		
		
		swap _underlyingSwap;
		option _optionOnSwap;

	};


}
#endif