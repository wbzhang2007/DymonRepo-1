#include "cashflowLeg.h"
#include "cashflow.h"
#include <math.h>
#include <stdio.h>

using namespace utilities;
using namespace std;
using namespace enums;

namespace instruments {
	cashflowLeg::cashflowLeg(date startDate,date tradeDate,double couponRate,double notional, vector<double> margin, int paymentFreq, date maturityDate, currency cashFlowCurr,bool exchangeNotionalBegin, bool exchangeNotionalEnd) {
		
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
		setNVs();
		setPVs();

	}

	cashflowLeg::~cashflowLeg() {
	}

	
	vector<double> cashflowLeg::getNotionalNVs() {
		vector<double> dummy;
		return dummy;
	   //to be filled
	}
	vector<double> cashflowLeg::getNotionalPVs() {
		vector<double> dummy;
		return dummy;
	   //to be filled
	}
		
	vector<double> cashflowLeg::getNVs() {
		return _NVs;
	}

	void cashflowLeg::setNVs() {

		vector<double>::iterator it=_NVs.begin();
		vector<date>::iterator itPay=_paymentDates.begin();
		vector<date>::iterator itFix=_fixingDates.begin();
		vector<double>::iterator itMargin=_margin.begin();

		int numOfMonthIncr=12/_paymentFreq;
		int i=1;
		date iteratorDate=dateUtil::getEndDate(_startDate,numOfMonthIncr*i,true);
		while(dateUtil::getBizDaysBetween(iteratorDate,_maturityDate)>=0){
			
			_NVs.push_back(_notional*_couponRate/_paymentFreq);
			
			iteratorDate=dateUtil::getEndDate(_startDate,numOfMonthIncr*(++i),true);
		}



	    //to be filled
	}
	int cashflowLeg::getExchangeNotionalBegin() {
		return _exchangeNotionalBegin;
	}

	int cashflowLeg::getExchangeNotionalEnd() {
		return _exchangeNotionalEnd;
	}

	void cashflowLeg::setExchangeNotionalBegin(int exchangeNotionalBegin) {
		_exchangeNotionalBegin=exchangeNotionalBegin;
	}

	void cashflowLeg::setExchangeNotionalEnd(int exchangeNotionalEnd) {
		_exchangeNotionalEnd=exchangeNotionalEnd;
	}

	void cashflowLeg::setPaymentFreq(int paymentFreq) {
		_paymentFreq=paymentFreq;
	}
	
	void cashflowLeg::setNotional(double notional) {
		_notional=notional;
	}
	
	void cashflowLeg::setStartDate(date startDate) {
		_startDate=startDate;
	}
	
	void cashflowLeg::setTradeDate(date tradeDate) {
		_tradeDate=tradeDate;
	}
	
	void cashflowLeg::setCouponRate(double couponRate) {
		_couponRate=couponRate;
	}
	
	void cashflowLeg::setMargin(vector<double> margin) {
		_margin=margin;
	}
	
	void cashflowLeg::setMaturityDate(date maturityDate) {
		_maturityDate=maturityDate;
	}
	
	void cashflowLeg::setCashFlowCurr(currency cashFlowCurr) {
		_cashFlowCurr=cashFlowCurr;
	}

	double cashflowLeg::MPV() {
		vector<double>::iterator it;
		double sum=0.0;
		for (it= _PVs.begin();it!= _PVs.end();++it) {
			sum+=*it;
		}

		return sum;
	}

	vector<double> cashflowLeg::getPVs() {
		return _PVs;
	}

	void cashflowLeg::setPVs() {
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
		while(dateUtil::getBizDaysBetween(iteratorDate,_maturityDate)>=0){
			
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

					//cout<<"num="<<dateUtil::getBizDaysBetween(_tradeDate,nextFixingDate)<<endl;
					//cout<<"denom="<<dateUtil::getBizDaysBetween(priorFixingDate,nextFixingDate)<<endl;
					accuralFactor=(double)dateUtil::getBizDaysBetween(_tradeDate,nextFixingDate)/dateUtil::getBizDaysBetween(priorFixingDate,nextFixingDate);
					break;
				}
			}
		}

		cout<<"accuralFactor="<<accuralFactor<<endl;
		double offset=(dateUtil::getBizDaysBetween(_tradeDate,_startDate)/dateUtil::getBizDaysBetween(_startDate,_fixingDates.at(0)))*numOfMonthIncr;
		
		//cout<<"offset_num="<<(dateUtil::getBizDaysBetween(_tradeDate,_startDate))<<endl;
		//cout<<"offset_denom="<<dateUtil::getBizDaysBetween(_startDate,_fixingDates.at(0))<<endl;

		for (it= _PVs.begin(),itPay=_paymentDates.begin(),itFix=_fixingDates.begin();it!= _PVs.end()&&itPay!=_paymentDates.end()&&itFix!=_fixingDates.end();++it,++itPay,++itFix) {
			//cout<<"itMarg="<<*itMargin<<endl;
			//review here 
			double test=numOfMonthIncr*(++count)+offset;
			//cout<<"test="<<test<<endl;
			if (test>0.0) {
				*it=_notional*_couponRate/_paymentFreq/exp(*itMargin*((count)-accuralFactor*numOfMonthIncr));
			}
			else {
				*it=0;
			}
			itMargin++;
		}
		
		cout<<"final count="<<count<<endl;
	}

	vector<double> cashflowLeg::getMargin(){
		return _margin;
	}

	int cashflowLeg::getPaymentFreq() {
		return _paymentFreq;
	}
	
	vector<date> cashflowLeg::getFixingDates() {
		return _fixingDates;
	}

	void cashflowLeg::setFixingDates() {
		
		vector<date>::iterator it;
		_startDate.printDate();
		cout<<"payFreq="<<_paymentFreq<<endl;

		
		int numOfMonthIncr=12/_paymentFreq;
		int i=1;
		date iteratorDate=dateUtil::getEndDate(_startDate,numOfMonthIncr*i,true);
		while(dateUtil::getBizDaysBetween(iteratorDate,_maturityDate)>=0){
			
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
	
	vector<date> cashflowLeg::getPaymentDates() {
		return _paymentDates;
	}

	void cashflowLeg::setPaymentDates() {
		vector<date>::iterator itFix;
		vector<date>::iterator itPay;

		int numOfMonthIncr=12/_paymentFreq;
		int i=1;
		date iteratorDate=dateUtil::getEndDate(_startDate,numOfMonthIncr*i,true);
		while(dateUtil::getBizDaysBetween(iteratorDate,_maturityDate)>=0){
			
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
	
	double cashflowLeg::getNotional() {
		return _notional;
	}
	
	date cashflowLeg::getStartDate()  {
		return _startDate;
	}
	
	date cashflowLeg::getMaturityDate() {
		return _maturityDate;
	}
	
	currency cashflowLeg::getCashFlowCurr() {		
		return _cashFlowCurr;
	}

	void cashflowLeg::printPVs() {
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
			cout<<"On "<<year<<"/"<<month<<"/"<<day<<" pays PV="<<*itPV<<endl;
		}
	}

	void cashflowLeg::printNVs() {
		vector<double>::iterator itNV;
		vector<date>::iterator itPay;
		int year;
		int month;
		int day;
		date dummy;		

		for (itNV= _NVs.begin(),itPay=_paymentDates.begin();itNV!= _NVs.end()&&itPay!=_paymentDates.end();++itNV,++itPay) { 
			dummy=*itPay;
			year=dummy.getYear();
			month=dummy.getMonth();
			day=dummy.getDay();
			cout<<"On "<<year<<"/"<<month<<"/"<<day<<" pays NV="<<*itNV<<endl;
		}
	}
	
}