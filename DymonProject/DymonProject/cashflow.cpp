#include "cashflow.h"
#include <math.h>
#include <stdio.h>


using namespace utilities;
using namespace std;
using namespace enums;

namespace instruments {
	cashflow::cashflow(date startDate,date tradeDate,double couponRate,double notional, double margin, int paymentFreq, date maturityDate, currency cashFlowCurr) {
		_startDate=startDate;
		_tradeDate=tradeDate;
		_notional=notional;
		_paymentFreq=paymentFreq;
		_maturityDate=maturityDate;
		_cashFlowCurr=cashFlowCurr;
		_couponRate=couponRate;
		_margin=margin;
		_fixingDates=getFixingDates();
		_paymentDates=getPaymentDates();
		_PVs=getPVs();
	}

	cashflow::~cashflow() {
	}

	double cashflow::MPV() {
		vector<double>::iterator it;
		double sum=0.0;
		for (it= _PVs.begin();it!= _PVs.end();++it) {
			sum+=*it;
		}

		return sum;

	}
	vector<double> cashflow::getPVs() {

		vector<double>::iterator it;
		vector<date>::iterator itPay=_paymentDates.begin();
		vector<date>::iterator itFix;
		int count=0;
		double accuralFactor;
		date priorCouponDate;
		date nextCouponDate;

		for (itPay=_paymentDates.begin();itPay!=_paymentDates.end();++itPay) {
			if (dateUtil::getBizDaysBetween(_tradeDate,*itPay)>=0) {
				nextCouponDate=*itPay;
				priorCouponDate=*(--itPay);
			}

		}
		accuralFactor=dateUtil::getBizDaysBetween(_tradeDate,priorCouponDate)/dateUtil::getBizDaysBetween(priorCouponDate,nextCouponDate);
		

		for (it= _PVs.begin(),itPay=_paymentDates.begin(),itFix=_fixingDates.begin();it!= _PVs.end()&&itPay!=_paymentDates.end()&&itFix!=_fixingDates.end();++it,++itPay,++itFix) {
			
		
			*it=_notional*_couponRate/_paymentFreq/pow((1+_margin/_paymentFreq),++count-accuralFactor);
		}
		return _PVs;
	}

	double cashflow::getMargin(){
		return _margin;
	}
	int cashflow::getPaymentFreq() {

		return _paymentFreq;
	}
	
	vector<date> cashflow::getFixingDates() {
		
		vector<date>::iterator it;
		int i=0;
		long increment=252/_paymentFreq;
		for (it= _fixingDates.begin();it!= _fixingDates.end();++it) { 
	        *it=dateUtil::getBizDate(_startDate, increment*(++i), _cashFlowCurr.getDayRollConvention());
		}
		return _fixingDates;

	}
	
	vector<date> cashflow::getPaymentDates() {
		vector<date>::iterator itFix;
		vector<date>::iterator itPay;

		for (itFix= _fixingDates.begin(),itPay=_paymentDates.begin();itFix!= _fixingDates.end()&&itPay!=_paymentDates.end();++itFix,++itPay) { 
	        if (dateUtil::isBizDay(*itFix)) {
				*itPay=*itFix;
			}
			else {
				*itPay=dateUtil::dayRoll(*itFix,_cashFlowCurr.getDayRollConvention());
			}
		}
		return _paymentDates;


	}
	
	double cashflow::getNotional() {
		
		return _notional;
	}
	
	date cashflow::getStartDate()  {
		return _startDate;

	}
	
	date cashflow::getMaturityDate() {
		return _maturityDate;

	}
	
	currency cashflow::getCashFlowCurr() {
		
		
		return _cashFlowCurr;

	}

	void cashflow::printPVs() {
		vector<double>::iterator itPV;
		vector<date>::iterator itPay;
		int year;
		int month;
		int day;
		date dummy;

		for (itPV= _PVs.begin(),itPay=_paymentDates.begin();itPV!= _PVs.end()&&itPay!=_paymentDates.end();++itPV,++itPay) { 
			dummy=*itPay;
			year=dummy.getYear();
			month=dummy.getMonth();
			day=dummy.getDay();
			cout<<"On "<<year<<"/"<<month<<"/"<<day<<" pays "<<*itPV<<endl;
		}
	}
}