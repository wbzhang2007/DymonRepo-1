//created by Hu Kun on 16 Dec 2012
#ifndef SWAPPRICER_H
#define SWAPPRICER_H
#include "currency.h"
#include "date.h"
#include "AbstractPricer.h"
#include "swap.h"
#include "cashflowLeg.h"

using namespace std;
using namespace instruments;


namespace models {
	class SwapPricer: public AbstractPricer {
	
	public:
		
		SwapPricer();

		~SwapPricer();
				
		
		
		double getMPV(instruments::swap aSwap,vector<yieldCurvePoint> aYieldCurve);

		vector<PV> getPVLeg(instruments::swap aSwap,vector<yieldCurvePoint> aYieldCurve);
		
		double getParRate(instruments::swap aSwap,vector<yieldCurvePoint> aYieldCurve);

	protected: 
		double _MPV;
		vector<PV> _PVLeg;
		double _parRate;
		cashflowLeg _fixCashflowLeg;
		cashflowLeg _floatCashflowLeg;

		instruments::swap _swapToBePriced;
		vector<yieldCurvePoint> _pricingYieldCurve;

		double getMPVFixLeg(cashflowLeg fixCashflowLeg,vector<yieldCurvePoint> aYieldCurve);
		double getMPVFloatLeg(cashflowLeg floatCashflowLeg,vector<yieldCurvePoint> aYieldCurve);
	};
}
#endif