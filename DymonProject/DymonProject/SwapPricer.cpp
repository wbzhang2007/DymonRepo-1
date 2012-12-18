//created by Hu Kun on 16 Dec 2012
#include "SwapPricer.h"
#include "AbstractPricer.h"
#include "swap.h"
#include "cashflowLeg.h"
#include <iterator>

using namespace std;
using namespace instruments;
using namespace models;

namespace models {
	SwapPricer::SwapPricer() {

	}

	SwapPricer::~SwapPricer() {

	}
				
	
	double SwapPricer::getMPVFixLeg(cashflowLeg fixCashflowLeg,vector<yieldCurvePoint> aYieldCurve) {

		vector<cashflow> cfVector=fixCashflowLeg.getCashFlowLeg().getCashFlowVector();
		vector<cashflow>::iterator it=cfVector.begin();
		double sum=0.0;
		int count=0;
		for (;it!=cfVector.end();it++) {
			cashflow aCF=*it;
			int numOfMonths;
			//=aCF.get;
			sum+=aCF.getCouponAmount();
		}
	
		return 0.0;
	}
	
	double SwapPricer::getMPVFloatLeg(cashflowLeg floatCashflowLeg,vector<yieldCurvePoint> aYieldCurve) {
		return 0.0;
	}
		
	double SwapPricer::getMPV(instruments::swap aSwap,vector<yieldCurvePoint> aYieldCurve) {
		_swapToBePriced=aSwap;
		_fixCashflowLeg=_swapToBePriced.getCashflowLegFix();
		_floatCashflowLeg=_swapToBePriced.getCashflowLegFloat();

		_pricingYieldCurve=aYieldCurve;

		_MPV=getMPVFixLeg(_fixCashflowLeg,_pricingYieldCurve)-getMPVFloatLeg(_floatCashflowLeg,_pricingYieldCurve);
		return _MPV;
	}
		
	vector<PV> SwapPricer::getPVLeg(instruments::swap aSwap,vector<yieldCurvePoint> aYieldCurve) {
		vector<PV> dummy;
		return dummy;
	}
	
	double SwapPricer::getParRate(instruments::swap aSwap,vector<yieldCurvePoint> aYieldCurve) {
		_parRate=getMPVFloatLeg(_floatCashflowLeg,_pricingYieldCurve)/getMPVFixLeg(_fixCashflowLeg,_pricingYieldCurve);
		
		return _parRate;
	}

}