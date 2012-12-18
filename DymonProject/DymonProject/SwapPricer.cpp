//created by Hu Kun on 16 Dec 2012
#include "SwapPricer.h"
#include "AbstractPricer.h"
#include "swap.h"
#include "cashflowLeg.h"
#include <iterator>
#include "AbstractInstrument.h"

using namespace std;
using namespace instruments;


namespace instruments {
	SwapPricer::SwapPricer() {

	}

	SwapPricer::~SwapPricer() {

	}
				
	
	double SwapPricer::getMPVFixLeg(cashflowLeg fixCashflowLeg,YieldCurve aYieldCurve) {
		_fixCashflowLeg=fixCashflowLeg;
		_pricingYieldCurve=aYieldCurve;
		vector<cashflow> cfVector=fixCashflowLeg.getCashFlowLeg().getCashFlowVector();
		vector<cashflow>::iterator it=cfVector.begin();
		double sum=0.0;
		int count=0;
		for (;it!=cfVector.end();it++) {
			cashflow aCF=*it;
			date paymentDate=aCF.getPaymentDate();
			sum+=aCF.getCouponAmount()*_pricingYieldCurve.getDiscountFactor(paymentDate);
		}
	
		return sum;
	}
	
	double SwapPricer::getMPVFloatLeg(cashflowLeg floatCashflowLeg,YieldCurve aYieldCurve) {
		_floatCashflowLeg=floatCashflowLeg;
		_pricingYieldCurve=aYieldCurve;
		vector<cashflow> cfVector=floatCashflowLeg.getCashFlowLeg().getCashFlowVector();
		vector<cashflow>::iterator it=cfVector.begin();
		double sum=0.0;
		int count=0;
		for (;it!=cfVector.end();it++) {
			cashflow aCF=*it;
			date accrualEndDate=aCF.getAccuralEndDate();
			date accrualStartDate=aCF.getAccuralStartDate();
			double FWDR=calFLiborRate(accrualStartDate,accrualEndDate,aCF.getAccuralFactor());
			sum+=aCF.getAccuralFactor()*(FWDR)*(_pricingYieldCurve.getDiscountFactor(aCF.getPaymentDate()));
		}
	
		return sum;
	}
		

	double SwapPricer::calFLiborRate(date forwardStartDate, date forwardEndDate, double accuralFactor) {


		return (_pricingYieldCurve.getDiscountFactor(forwardStartDate)/ _pricingYieldCurve.getDiscountFactor(forwardEndDate)-1)/accuralFactor;
	}
	double SwapPricer::getMPV(cashflowLeg fixCashflowLeg,cashflowLeg floatCashflowLeg,YieldCurve aYieldCurve) {
		//_swapToBePriced=aSwap;
		_fixCashflowLeg=fixCashflowLeg;
		_floatCashflowLeg=floatCashflowLeg;

		_pricingYieldCurve=aYieldCurve;

		_MPV=getMPVFixLeg(_fixCashflowLeg,_pricingYieldCurve)-getMPVFloatLeg(_floatCashflowLeg,_pricingYieldCurve);
		return _MPV;
	}
		
	//vector<PV> SwapPricer::getPVLeg(instruments::swap aSwap,YieldCurve aYieldCurve,int fixOrFloating) {
	//	//fixOrFloating=-1 ==>floating
	//	//fixOrFloating=1 ==>fixed
	//	_pricingYieldCurve=aYieldCurve;
	//	_swapToBePriced=aSwap;

	//	

	//	if (fixOrFloating=-1) {
	//		_PVFloatingLeg.clear();

	//		vector<cashflow> cfVector=aSwap.getCashflowLegFloat().getCashFlowLeg().getCashFlowVector();
	//		vector<cashflow>::iterator it=cfVector.begin();
	//		for (;it!=cfVector.end();it++) {
	//			cashflow aCF=*it;
	//			date accrualEndDate=aCF.getAccuralEndDate();
	//			double aPV_Value=aCF.getCouponAmount()*(_pricingYieldCurve.getDiscountFactor(accrualEndDate));
	//			PV aPV=std::make_tuple(accrualEndDate,aPV_Value);
	//			_PVFloatingLeg.push_back(aPV);


	//		}


	//		return _PVFloatingLeg;
	//	}

	//	if (fixOrFloating=1) {
	//		vector<cashflow> cfVector=aSwap.getCashflowLegFix().getCashFlowLeg().getCashFlowVector();
	//		vector<cashflow>::iterator it=cfVector.begin();
	//		for (;it!=cfVector.end();it++) {



	//		}



	//		return _PVFixLeg;
	//	}

	//	
	//}

	double SwapPricer::getParRate(cashflowLeg floatCashflowLeg,cashflowLeg fixCashflowLeg,YieldCurve aYieldCurve) {

		
		_parRate=getMPVFloatLeg(floatCashflowLeg,_pricingYieldCurve)/getMPVFixLeg(fixCashflowLeg,_pricingYieldCurve);
		
		return _parRate;
	}

}