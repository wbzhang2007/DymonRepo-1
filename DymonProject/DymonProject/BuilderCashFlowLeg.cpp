#include "cashflowLeg.h"
#include "cashflow.h"
#include "BuilderCashFlowLeg.h"
#include <math.h>
#include <stdio.h>
#include "RecordHelper.h"

using namespace Session;
using namespace utilities;
using namespace std;
using namespace enums;

namespace instruments {

	BuilderCashFlowLeg::BuilderCashFlowLeg() {
	}
	
	BuilderCashFlowLeg::BuilderCashFlowLeg(date startDate, date maturityDate,double couponRate,double notional, int paymentFreq, currency cashFlowLegCurr,bool rollAccuralDates, int buildDirection,RecordHelper::HolidayMap holidayMap) {

	}
	
	BuilderCashFlowLeg::BuilderCashFlowLeg(date startDate, int tenorNumOfMonths,double couponRate,double notional, int paymentFreq, currency cashFlowLegCurr,bool rollAccuralDates,RecordHelper::HolidayMap holidayMap) {

	}

	BuilderCashFlowLeg::~BuilderCashFlowLeg() {
	}
		
	//	setExchangeNotionalEnd(exchangeNotionalEnd);
	//	setExchangeNotionalBegin(exchangeNotionalBegin);

	//	setStartDate(startDate);
	//	setTradeDate(tradeDate);
	//	setNotional(notional);
	//	setPaymentFreq(paymentFreq);
	//	setMaturityDate(maturityDate);

	//	setCashFlowCurr(cashFlowCurr);
	//	setCouponRate(couponRate);
	//	setMargin(margin);
		
	//	setFixingDates();
	//	setPaymentDates();
	//	setNVs();
	//	setPVs();

	//}



	
	//vector<double> BuilderCashFlowLeg::getNotionalNVs() {
	//	vector<double> dummy;
	//	return dummy;
	   //to be filled
	//}
	//vector<double> BuilderCashFlowLeg::getNotionalPVs() {
	//	vector<double> dummy;
	//	return dummy;
	   //to be filled
	//}
		
	//vector<double> BuilderCashFlowLeg::getNVs() {
	//	return _NVs;
	//}

	//void BuilderCashFlowLeg::setNVs() {

	//	vector<double>::iterator it=_NVs.begin();
	//	vector<date>::iterator itPay=_paymentDates.begin();
	//	vector<date>::iterator itFix=_fixingDates.begin();
	//	vector<double>::iterator itMargin=_margin.begin();

//		int numOfMonthIncr=12/_paymentFreq;
//		int i=1;
//		date iteratorDate=dateUtil::getEndDate(_startDate,numOfMonthIncr*i,true);
//		while(dateUtil::getBizDaysBetween(iteratorDate,_maturityDate)>=0){
			
//			_NVs.push_back(_notional*_couponRate/_paymentFreq);
			
//			iteratorDate=dateUtil::getEndDate(_startDate,numOfMonthIncr*(++i),true);
//		}



	    //to be filled
//	}
//	int BuilderCashFlowLeg::getExchangeNotionalBegin() {
//		return _exchangeNotionalBegin;
//	}

//	int BuilderCashFlowLeg::getExchangeNotionalEnd() {
//		return _exchangeNotionalEnd;
//	}

//	void BuilderCashFlowLeg::setExchangeNotionalBegin(int exchangeNotionalBegin) {
//		_exchangeNotionalBegin=exchangeNotionalBegin;
//	}

//	void BuilderCashFlowLeg::setExchangeNotionalEnd(int exchangeNotionalEnd) {
//		_exchangeNotionalEnd=exchangeNotionalEnd;
//	}

//	void BuilderCashFlowLeg::setPaymentFreq(int paymentFreq) {
//		_paymentFreq=paymentFreq;
//	}
	
//	void BuilderCashFlowLeg::setNotional(double notional) {
//		_notional=notional;
//	}
	
//	void BuilderCashFlowLeg::setStartDate(date startDate) {
//		_startDate=startDate;
//	}
	
	//void BuilderCashFlowLeg::setTradeDate(date tradeDate) {
	//	_tradeDate=tradeDate;
	//}
	//
	//void BuilderCashFlowLeg::setCouponRate(double couponRate) {
	//	_couponRate=couponRate;
	//}
	//
	//void BuilderCashFlowLeg::setMargin(vector<double> margin) {
	//	_margin=margin;
	//}
	//
	//void BuilderCashFlowLeg::setMaturityDate(date maturityDate) {
	//	_maturityDate=maturityDate;
	//}
	//
	//void BuilderCashFlowLeg::setCashFlowCurr(currency cashFlowCurr) {
	//	_cashFlowCurr=cashFlowCurr;
	//}

	//double BuilderCashFlowLeg::MPV() {
	//	vector<double>::iterator it;
	//	double sum=0.0;
	//	for (it= _PVs.begin();it!= _PVs.end();++it) {
	//		sum+=*it;
	//	}

	//	return sum;
	//}

	//vector<double> BuilderCashFlowLeg::getPVs() {
	//	return _PVs;
	//}

	//void BuilderCashFlowLeg::setPVs() {
	//	vector<double>::iterator it;
	//	vector<date>::iterator itPay=_paymentDates.begin();
	//	vector<date>::iterator itFix=_fixingDates.begin();
	//	vector<double>::iterator itMargin=_margin.begin();

	//	int count=0;
	//	double accuralFactor;
	//	date priorFixingDate;
	//	date nextFixingDate;

	//	int numOfMonthIncr=12/_paymentFreq;
	//	int i=1;
	//	date iteratorDate=dateUtil::getEndDate(_startDate,numOfMonthIncr*i,true);
	//	while(dateUtil::getBizDaysBetween(iteratorDate,_maturityDate)>=0){
	//		
	//		_PVs.push_back(0);
	//		
	//		iteratorDate=dateUtil::getEndDate(_startDate,numOfMonthIncr*(++i),true);
	//	}
	//	signed long dayC=dateUtil::getBizDaysBetween(_tradeDate,*_fixingDates.begin());
	//	cout<<"dayC="<<dayC<<endl;

	//	_tradeDate.printDate();
	//	date testDate=*_fixingDates.begin();
	//	testDate.printDate();
	//	if (dateUtil::getBizDaysBetween(_tradeDate,*_fixingDates.begin())>=0) {
	//		accuralFactor=0;
	//	}else {
	//		itFix=_fixingDates.begin();
	//		itFix++;
	//		for (;itFix!=_fixingDates.end();itFix++) {
	//			if (dateUtil::getBizDaysBetween(_tradeDate,*itFix)>0) {
	//				nextFixingDate=*itFix;
	//				priorFixingDate=*(--itFix);
	//				cout<<"***********"<<endl;
	//				nextFixingDate.printDate();
	//				priorFixingDate.printDate();
	//				cout<<"***********"<<endl;

	//				//cout<<"num="<<dateUtil::getBizDaysBetween(_tradeDate,nextFixingDate)<<endl;
	//				//cout<<"denom="<<dateUtil::getBizDaysBetween(priorFixingDate,nextFixingDate)<<endl;
	//				accuralFactor=(double)dateUtil::getBizDaysBetween(_tradeDate,nextFixingDate)/dateUtil::getBizDaysBetween(priorFixingDate,nextFixingDate);
	//				break;
	//			}
	//		}
	//	}

	//	cout<<"accuralFactor="<<accuralFactor<<endl;
	//	double offset=(dateUtil::getBizDaysBetween(_tradeDate,_startDate)/dateUtil::getBizDaysBetween(_startDate,_fixingDates.at(0)))*numOfMonthIncr;
	//	
	//	//cout<<"offset_num="<<(dateUtil::getBizDaysBetween(_tradeDate,_startDate))<<endl;
	//	//cout<<"offset_denom="<<dateUtil::getBizDaysBetween(_startDate,_fixingDates.at(0))<<endl;

	//	for (it= _PVs.begin(),itPay=_paymentDates.begin(),itFix=_fixingDates.begin();it!= _PVs.end()&&itPay!=_paymentDates.end()&&itFix!=_fixingDates.end();++it,++itPay,++itFix) {
	//		//cout<<"itMarg="<<*itMargin<<endl;
	//		//review here 
	//		double test=numOfMonthIncr*(++count)+offset;
	//		//cout<<"test="<<test<<endl;
	//		if (test>0.0) {
	//			*it=_notional*_couponRate/_paymentFreq/exp(*itMargin*((count)-accuralFactor*numOfMonthIncr));
	//		}
	//		else {
	//			*it=0;
	//		}
	//		itMargin++;
	//	}
	//	
	//	cout<<"final count="<<count<<endl;
	//}

	//vector<double> BuilderCashFlowLeg::getMargin(){
	//	return _margin;
	//}

	//int BuilderCashFlowLeg::getPaymentFreq() {
	//	return _paymentFreq;
	//}
	//
	//vector<date> BuilderCashFlowLeg::getFixingDates() {
	//	return _fixingDates;
	//}

	//void BuilderCashFlowLeg::setFixingDates() {
	//	
	//	vector<date>::iterator it;
	//	_startDate.printDate();
	//	cout<<"payFreq="<<_paymentFreq<<endl;

	//	
	//	int numOfMonthIncr=12/_paymentFreq;
	//	int i=1;
	//	date iteratorDate=dateUtil::getEndDate(_startDate,numOfMonthIncr*i,true);
	//	while(dateUtil::getBizDaysBetween(iteratorDate,_maturityDate)>=0){
	//		
	//		_fixingDates.push_back(0);
	//		
	//		iteratorDate=dateUtil::getEndDate(_startDate,numOfMonthIncr*(++i),true);
	//	}

	//	int count=0;
	//	for (it= _fixingDates.begin();it!= _fixingDates.end();it++) { 
	//        *it=dateUtil::getEndDate(_startDate,numOfMonthIncr*(++count),true);
	//		date aTestDate=*it;
	//		cout<<"fixingDate";
	//	    aTestDate.printDate();
	//		cout<<endl;
	//	}
	//}
	//
	//vector<date> BuilderCashFlowLeg::getPaymentDates() {
	//	return _paymentDates;
	//}

	//void BuilderCashFlowLeg::setPaymentDates() {
	//	vector<date>::iterator itFix;
	//	vector<date>::iterator itPay;

	//	int numOfMonthIncr=12/_paymentFreq;
	//	int i=1;
	//	date iteratorDate=dateUtil::getEndDate(_startDate,numOfMonthIncr*i,true);
	//	while(dateUtil::getBizDaysBetween(iteratorDate,_maturityDate)>=0){
	//		
	//		_paymentDates.push_back(0);
	//		
	//		iteratorDate=dateUtil::getEndDate(_startDate,numOfMonthIncr*(++i),true);
	//	}
	//	
	//	

	//	cout<<"size of paymentDates="<<_paymentDates.size()<<endl;
	//	int count=0;
	//	for (itFix=_fixingDates.begin(),itPay=_paymentDates.begin();itFix!=_fixingDates.end(),itPay!=_paymentDates.end();itFix++,itPay++) { 

	//		*itPay=dateUtil::dayRollAdjust(*itFix,Mfollowing,"");
	//		date aPayDate=*itPay;
	//		cout<<"paymentDate";
	//		aPayDate.printDate();
	//		cout<<endl;
	//	}
	//}
	//
	//double BuilderCashFlowLeg::getNotional() {
	//	return _notional;
	//}
	//
	//date BuilderCashFlowLeg::getStartDate()  {
	//	return _startDate;
	//}
	//
	//date BuilderCashFlowLeg::getMaturityDate() {
	//	return _maturityDate;
	//}
	//
	//currency BuilderCashFlowLeg::getCashFlowCurr() {		
	//	return _cashFlowCurr;
	//}

	//void BuilderCashFlowLeg::printPVs() {
	//	vector<double>::iterator itPV;
	//	vector<date>::iterator itPay;
	//	int year;
	//	int month;
	//	int day;
	//	date dummy;		

	//	for (itPV= _PVs.begin(),itPay=_paymentDates.begin();itPV!= _PVs.end()&&itPay!=_paymentDates.end();++itPV,++itPay) { 
	//		dummy=*itPay;
	//		year=dummy.getYear();
	//		month=dummy.getMonth();
	//		day=dummy.getDay();
	//		cout<<"On "<<year<<"/"<<month<<"/"<<day<<" pays PV="<<*itPV<<endl;
	//	}
	//}

	//void BuilderCashFlowLeg::printNVs() {
	//	vector<double>::iterator itNV;
	//	vector<date>::iterator itPay;
	//	int year;
	//	int month;
	//	int day;
	//	date dummy;		

	//	for (itNV= _NVs.begin(),itPay=_paymentDates.begin();itNV!= _NVs.end()&&itPay!=_paymentDates.end();++itNV,++itPay) { 
	//		dummy=*itPay;
	//		year=dummy.getYear();
	//		month=dummy.getMonth();
	//		day=dummy.getDay();
	//		cout<<"On "<<year<<"/"<<month<<"/"<<day<<" pays NV="<<*itNV<<endl;
	//	}
	//}
	
}