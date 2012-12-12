//created by Hu Kun on 8 Dec
//modified by Hu Kun on 10 Dec
//reviewed and modified by Hu Kun on 11 Dec, added running trade features

#include "cashflow.h"
#include <math.h>
#include <stdio.h>


using namespace utilities;
using namespace std;
using namespace enums;

namespace instruments {

	cashflow::cashflow(double couponRate,double notional,  date fixingDate, date paymentDate,date accuralStartDate, date accuralEndDate, currency cashFlowCurr) {
	    setCouponRate(couponRate);
		setNotional(notional);
		setFixingDate(fixingDate);
		setPaymentDate(paymentDate);
		setAccuralStartDate(accuralStartDate);
		setAccuralEndDate(accuralEndDate);
		setCashFlowCurr(cashFlowCurr);

		//setAccuralFactor();
	}
	
	cashflow::~cashflow() {

	}

	//get methods:
	double cashflow::getCouponAmount() {
		
		return _couponAmount;
	}
	
	double cashflow::getCouponRate() {
		return _couponRate;

	}
	
	date cashflow::getFixingDate() {
		return _fixingDate;

	}
	
	date cashflow::getPaymentDate() {
		return _paymentDate;

	}
	
	date cashflow::getAccuralStartDate() {
		return _accuralStartDate;

	}
	
	date cashflow::getAccuralEndDate() {
		return _accuralEndDate;

	}
	
	currency cashflow::getCashFlowCurr() {
		return _cashFlowCurr;

	}
	
	double cashflow::getAccuralFactor() {
		return _accuralFactor;
	}


	//set methods:
	void cashflow::setCouponAmount() {

		_couponAmount=_couponRate*_notional*_accuralFactor;
	}
	
	void cashflow::setCouponRate(double couponRate) {
		_couponRate=couponRate;
	}
	void cashflow::setNotional(double notional) {
		_notional=notional;
	}
	
	void cashflow::setFixingDate(date fixingDate) {
		_fixingDate=fixingDate;
	}
		
	void cashflow::setPaymentDate(date paymentDate) {
		_paymentDate=paymentDate;
	}
		
	void cashflow::setAccuralStartDate(date accuralStartDate) {
		_accuralStartDate=accuralStartDate;
	}
	
	void cashflow::setAccuralEndDate(date accuralEndDate) {
		_accuralEndDate=accuralEndDate;
	}
	
	void cashflow::setCashFlowCurr(currency cashFlowCurr) {

		_cashFlowCurr=cashFlowCurr;
	}
	
	void cashflow::setAccuralFactor() {
		_accuralFactor=dateUtil::getAccrualFactor(_accuralStartDate,_accuralEndDate,_cashFlowCurr.getDayCountCashConvention());
	}
	
}