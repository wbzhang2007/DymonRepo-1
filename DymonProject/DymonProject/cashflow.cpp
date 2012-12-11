//created by Hu Kun on 8 Dec
//modified by Hu Kun on 10 Dec

#include "cashflow.h"
#include <math.h>
#include <stdio.h>

using namespace utilities;
using namespace std;
using namespace enums;

namespace instruments {
	cashflow::cashflow(date startDate,date tradeDate,double couponRate,double notional, vector<double> margin, int paymentFreq, date maturityDate, currency cashFlowCurr,bool exchangeNotionalBegin, bool exchangeNotionalEnd) {
		
		setExchangeNotionalEnd(exchangeNotionalEnd);
		setExchangeNotionalBegin(exchangeNotionalBegin);

		setStartDate(startDate);
		setTradeDate(tradeDate);
		setNotional(notional);
		setPaymentFreq(paymentFreq);
		setMaturityDate(maturityDate);

		setCashFlowCurr(cashFlowCurr);
		setCouponRate(couponRate);
		setMargin(margin);
		
		setFixingDates();
		setPaymentDates();
		setPVs();

	}

	cashflow::~cashflow() {
	}

	bool cashflow::getExchangeNotionalBegin() {
		return _exchangeNotionalBegin;
	}

	bool cashflow::getExchangeNotionalEnd() {
		return _exchangeNotionalEnd;
	}

	void cashflow::setExchangeNotionalBegin(bool exchangeNotionalBegin) {
		_exchangeNotionalBegin=exchangeNotionalBegin;
	}

	void cashflow::setExchangeNotionalEnd(bool exchangeNotionalEnd) {
		_exchangeNotionalEnd=exchangeNotionalEnd;
	}

	void cashflow::setPaymentFreq(int paymentFreq) {
		_paymentFreq=paymentFreq;
	}
	
	void cashflow::setNotional(double notional) {
		_notional=notional;
	}
	
	void cashflow::setStartDate(date startDate) {
		_startDate=startDate;
	}
	
	void cashflow::setTradeDate(date tradeDate) {
		_tradeDate=tradeDate;
	}
	
	void cashflow::setCouponRate(double couponRate) {
		_couponRate=couponRate;
	}
	
	void cashflow::setMargin(vector<double> margin) {
		_margin=margin;
	}
	
	void cashflow::setMaturityDate(date maturityDate) {
		_maturityDate=maturityDate;
	}
	
	void cashflow::setCashFlowCurr(currency cashFlowCurr) {
		_cashFlowCurr=cashFlowCurr;
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
		return _PVs;
	}

	void cashflow::setPVs() {
		vector<double>::iterator it;
		vector<date>::iterator itPay=_paymentDates.begin();
		vector<date>::iterator itFix=_fixingDates.begin();
		vector<double>::iterator itMargin=_margin.begin();

		int count=0;
		double accuralFactor;
		date priorFixingDate;
		date nextFixingDate;

		int numOfMonthIncr=12/_paymentFreq;
		int i=1;
		date iteratorDate=dateUtil::getEndDate(_startDate,numOfMonthIncr*i,true);
		while(dateUtil::getBizDaysBetween(iteratorDate,_maturityDate)>0){
			
			_PVs.push_back(0);
			
			iteratorDate=dateUtil::getEndDate(_startDate,numOfMonthIncr*(++i),true);
		}
		signed long dayC=dateUtil::getBizDaysBetween(_tradeDate,*_fixingDates.begin());
		cout<<"dayC="<<dayC<<endl;

		_tradeDate.printDate();
		date testDate=*_fixingDates.begin();
		testDate.printDate();
		if (dateUtil::getBizDaysBetween(_tradeDate,*_fixingDates.begin())>=0) {
			accuralFactor=0;
		}else {
			itFix=_fixingDates.begin();
			itFix++;
			for (;itFix!=_fixingDates.end();itFix++) {
				if (dateUtil::getBizDaysBetween(_tradeDate,*itFix)>0) {
					nextFixingDate=*itFix;
					priorFixingDate=*(--itFix);
					cout<<"***********"<<endl;
					nextFixingDate.printDate();
					priorFixingDate.printDate();
					cout<<"***********"<<endl;

					cout<<"num="<<dateUtil::getBizDaysBetween(_tradeDate,nextFixingDate)<<endl;
					cout<<"denom="<<dateUtil::getBizDaysBetween(priorFixingDate,nextFixingDate)<<endl;
					accuralFactor=(double)dateUtil::getBizDaysBetween(_tradeDate,nextFixingDate)/dateUtil::getBizDaysBetween(priorFixingDate,nextFixingDate);
					break;
				}
			}
		}

		cout<<"accuralFactor="<<accuralFactor<<endl;

		for (it= _PVs.begin(),itPay=_paymentDates.begin(),itFix=_fixingDates.begin();it!= _PVs.end()&&itPay!=_paymentDates.end()&&itFix!=_fixingDates.end();++it,++itPay,++itFix) {
			//cout<<"itMarg="<<*itMargin<<endl;
			*it=_notional*_couponRate/_paymentFreq/pow((1+*itMargin),(++count)-accuralFactor);
			itMargin++;
		}
		
		cout<<"final count="<<count<<endl;
	}

	vector<double> cashflow::getMargin(){
		return _margin;
	}

	int cashflow::getPaymentFreq() {
		return _paymentFreq;
	}
	
	vector<date> cashflow::getFixingDates() {
		return _fixingDates;
	}

	void cashflow::setFixingDates() {
		
		vector<date>::iterator it;
		_startDate.printDate();
		cout<<"payFreq="<<_paymentFreq<<endl;

		
		int numOfMonthIncr=12/_paymentFreq;
		int i=1;
		date iteratorDate=dateUtil::getEndDate(_startDate,numOfMonthIncr*i,true);
		while(dateUtil::getBizDaysBetween(iteratorDate,_maturityDate)>0){
			
			_fixingDates.push_back(0);
			
			iteratorDate=dateUtil::getEndDate(_startDate,numOfMonthIncr*(++i),true);
		}

		int count=0;
		for (it= _fixingDates.begin();it!= _fixingDates.end();it++) { 
	        *it=dateUtil::getEndDate(_startDate,numOfMonthIncr*(++count),true);
			date aTestDate=*it;
			cout<<"fixingDate";
		    aTestDate.printDate();
			cout<<endl;
		}
	}
	
	vector<date> cashflow::getPaymentDates() {
		return _paymentDates;
	}

	void cashflow::setPaymentDates() {
		vector<date>::iterator itFix;
		vector<date>::iterator itPay;

		int numOfMonthIncr=12/_paymentFreq;
		int i=1;
		date iteratorDate=dateUtil::getEndDate(_startDate,numOfMonthIncr*i,true);
		while(dateUtil::getBizDaysBetween(iteratorDate,_maturityDate)>0){
			
			_paymentDates.push_back(0);
			
			iteratorDate=dateUtil::getEndDate(_startDate,numOfMonthIncr*(++i),true);
		}
		
		

		cout<<"size of paymentDates="<<_paymentDates.size()<<endl;
		int count=0;
		for (itFix=_fixingDates.begin(),itPay=_paymentDates.begin();itFix!=_fixingDates.end(),itPay!=_paymentDates.end();itFix++,itPay++) { 

			*itPay=dateUtil::dayRollAdjust(*itFix,Mfollowing,"");
			date aPayDate=*itPay;
			cout<<"paymentDate";
			aPayDate.printDate();
			cout<<endl;
		}
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