//created by Hu Kun on 16 Dec 2012
#include "SwapPricer.h"
#include "AbstractPricer.h"
#include "swap.h"
#include "cashflowLeg.h"
#include <iterator>
#include "AbstractInstrument.h"

using namespace std;
using namespace instruments;

double SwapPricer::getMPVFixLeg(cashflowLeg fixCashflowLeg,YieldCurve* aYieldCurve) {
	_fixCashflowLeg=fixCashflowLeg;
	_pricingYieldCurve=aYieldCurve;
	vector<cashflow> cfVector=fixCashflowLeg.getCashFlowLeg().getCashFlowVector();
	vector<cashflow>::iterator it=cfVector.begin();
	double sum=0.0;
	int count=0;
	for (;it!=cfVector.end();it++) {
		cashflow aCF=*it;
		date paymentDate=aCF.getPaymentDate();
		sum+=aCF.getCouponAmount()*_pricingYieldCurve->getDiscountFactor(paymentDate);
	}

	return sum;
}

double SwapPricer::getMPVFloatLeg(cashflowLeg floatCashflowLeg,YieldCurve* aYieldCurve) {
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
		//double FWDR=calFLiborRate(accrualStartDate,accrualEndDate,aCF.getAccuralFactor());

		currency cashflowCurr=aCF.getCashFlowCurr();
		double FLiborRate=aYieldCurve->getFLiborRate(accrualStartDate,accrualEndDate,cashflowCurr.getDayCountSwapConvention());
		sum+=aCF.getAccuralFactor()*(FLiborRate)*(_pricingYieldCurve->getDiscountFactor(aCF.getPaymentDate()));
	}

	return sum;
}


double SwapPricer::calFLiborRate(date forwardStartDate, date forwardEndDate, double accuralFactor) {
	return (_pricingYieldCurve->getDiscountFactor(forwardStartDate)/ _pricingYieldCurve->getDiscountFactor(forwardEndDate)-1)/accuralFactor;
}

double SwapPricer::getMPV(cashflowLeg fixCashflowLeg,cashflowLeg floatCashflowLeg,YieldCurve* aYieldCurve) {
	//_swapToBePriced=aSwap;
	_fixCashflowLeg=fixCashflowLeg;
	_floatCashflowLeg=floatCashflowLeg;
	_pricingYieldCurve=aYieldCurve;

	_MPV=getMPVFixLeg(_fixCashflowLeg,_pricingYieldCurve)-getMPVFloatLeg(_floatCashflowLeg,_pricingYieldCurve);
	return _MPV;
}

double SwapPricer::getParRate(cashflowLeg floatCashflowLeg,cashflowLeg fixCashflowLeg,YieldCurve* aYieldCurve) {

	_floatCashflowLeg=floatCashflowLeg;
	_fixCashflowLeg=fixCashflowLeg;
	_pricingYieldCurve=aYieldCurve;
	vector<cashflow> cfVector=fixCashflowLeg.getCashFlowLeg().getCashFlowVector();
	vector<cashflow>::iterator it=cfVector.begin();
	double denom=0.0;

	for (;it!=cfVector.end();it++) {
		cashflow aCF=*it;
		date accrualEndDate=aCF.getAccuralEndDate();
		date accrualStartDate=aCF.getAccuralStartDate();

		denom+=aCF.getAccuralFactor()*(aYieldCurve->getDiscountFactor(accrualEndDate));

	}

	_parRate=getMPVFloatLeg(floatCashflowLeg,_pricingYieldCurve)/denom;
	return _parRate;
}

