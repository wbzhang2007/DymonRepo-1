// DymonProject.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "date.h"
#include "dateUtil.h"
#include "zero.h"
#include "cashflow.h"
#include "RecordHelper.h"
#include <math.h>
#include "currency.h"
#include "Enums.h"

using namespace utilities;
using namespace std;
using namespace instruments;
using namespace Session;

void RecordTest();
void DateUtilTest();
void CashFlowLegTest();
void CashFlowTest();

int _tmain(int argc, _TCHAR* argv[])
{
	//DateUtilTest();
	//RecordTest();
	CashFlowTest();
}

void ZeroTest(){
	cout << "******** Zero Test ********" << endl;
	date date0(2012,12,1);
	//cout<<date0.getJudianDayNumber()<<" "<<date0.isBusinessDay()<<endl;
	date date1(2012,12,8);
	date date2(2013,12,1);
	date date3(2012,1,1);

	zero zero1(0.001,1,date2,date0);

	//cout<<date1.getJudianDayNumber()<<" "<<date1.isBusinessDay()<<endl;
	//cout<<"Days inbetween: "<<dateUtil::getDaysBetween(date0, date1)<<endl;
	//cout<<"Business days inbetween: "<<dateUtil::getBizDaysBetween(date1, date2)<<endl;
	//cout<<"Today is "<<dateUtil::getTodayYear()<<" "<<dateUtil::getTodayMonth()<<" "<<dateUtil::getTodayDay()<<endl;
	cout<<"zero1 price is "<<zero1.getPrice()<<endl;
	cout<<"zero2 implied spot rate is "<<zero1.getImpliedSpotRate()<<endl;
}

void DateUtilTest(){
	cout << "******** DayRollAdjust Test ********" << endl;
	{
		date date0(2456270);
		date date1(2012,12,8);
		cout<<date0.isEqual(date1)<<endl;} 
	{
		date date0(2011,9,18);
		date date1 = dateUtil::dayRollAdjust(date0, Following, "");
		date date2(2011,9,19);
		cout<<date1.isEqual(date2)<<endl;}
	{
		date date0(2011,9,18);
		date date1 = dateUtil::dayRollAdjust(date0, Preceding, "");
		date date2(2011,9,16);
		cout<<date1.isEqual(date2)<<endl;}
	{
		date date0(2011,7,30);
		date date1 = dateUtil::dayRollAdjust(date0, Mfollowing, "");
		date date2(2011,7,29);
		cout<<date1.isEqual(date2)<<endl;}
	{
		date date0(2011,7,30);
		date date1 = dateUtil::dayRollAdjust(date0, Mfollowingbi, "");
		date date2(2011,7,29);
		cout<<date1.isEqual(date2)<<endl;}
	{
		date date0(2011,10,15);
		date date1 = dateUtil::dayRollAdjust(date0, Mfollowingbi, "");
		date date2(2011,10,14);
		cout<<date1.isEqual(date2)<<endl;}
	cout << "******** GetEndDate Test ********" << endl;
	{
		date date0(2012,1,31);
		date date1 = dateUtil::getEndDate(date0, 1, true);
		date date2(2012,2,29);
		cout<<date1.isEqual(date2)<<endl;}
	{
		date date0(2012,10,31);
		date date1 = dateUtil::getEndDate(date0, 4, true);
		date date2(2013,2,28);
		cout<<date1.isEqual(date2)<<endl;}
	cout << "******** DayCount Test ********" << endl;
	{
		date sd(2012,10,31);
		date ed(2012,11,30);
		cout<<(dateUtil::getAccrualFactor(sd,ed,thirty_360US)==30/360.0)<<endl;}
	{
		date sd(2012,11,30);
		date ed(2012,12,31);
		cout<<(dateUtil::getAccrualFactor(sd,ed,thirty_360US)==30/360.0)<<endl;}
	{
		date sd(2012,7,31);
		date ed(2012,8,31);
		cout<<(dateUtil::getAccrualFactor(sd,ed,thirthE_360)==30/360.0)<<endl;}
	{
		date sd(2010,12,30);
		date ed(2011,1,2);
		cout<<(dateUtil::getAccrualFactor(sd,ed,ACT_ACT)-3/365.0<pow(10.0,-12))<<endl;}
	{
		date sd(2011,12,30);
		date ed(2012,1,2);
		cout<<(dateUtil::getAccrualFactor(sd,ed,ACT_ACT)-(2/365.0+1/366.0)<pow(10.0,-12))<<endl;}
	{
		date sd(2011,12,30);
		date ed(2013,1,2);
		cout<<(dateUtil::getAccrualFactor(sd,ed,ACT_ACT)-(367/365.0+1+1/365.0)<pow(10.0,-12))<<endl;}
	{
		date sd(2012,12,7);
		date ed(2012,12,17);
		cout<<(dateUtil::getAccrualFactor(sd,ed,BUS_252)-(6/252.0)<pow(10.0,-12))<<endl;}
}

void RecordTest(){
	cout << "******** RecordHelper Test ********" << endl;
	RecordHelper* recordHelper = RecordHelper::getInstance();
	recordHelper->init(Configuration::getInstance());
	for(map<string, set<long>>::iterator outer_iter=RecordHelper::getInstance()->getHolidayMap().begin(); outer_iter!=RecordHelper::getInstance()->getHolidayMap().end(); ++outer_iter) {
		for(set<long>::iterator inner_iter=outer_iter->second.begin(); inner_iter!=outer_iter->second.end(); ++inner_iter) {
			cout << outer_iter->first<< " -> " << *inner_iter << endl;
		}
	}
}

void CashFlowLegTest() {
	
	cout << "******** CashFlow Test ********" << endl;
	date tradeDate(2013,11,2);
	date startDate(2012,10,2);
	date maturityDate(2016,8,13);

	cout<<"startDate=";
	startDate.printDate();

	cout<<"maturityDate=";
	maturityDate.printDate();

	cout<<"tradeDate=";
	tradeDate.printDate();

	double notional=1000000;
	double couponRate=0.04;
	vector<double> margin;
	int paymentFreq=4;
	
	vector<double>::iterator itMargin=margin.begin();

	int numOfMonthIncr=12/paymentFreq;
	int i=1;
	date iteratorDate=dateUtil::getEndDate(startDate,numOfMonthIncr*i,true);
	while(dateUtil::getBizDaysBetween(iteratorDate,maturityDate)>0){
			margin.push_back(0.05);
			
			iteratorDate=dateUtil::getEndDate(startDate,numOfMonthIncr*(++i),true);
	}
    

	currency cashFlowCurr=currency(USD,ACT_360, ACT_365, Mfollowing, paymentFreq,1);
	//cashflow testCashFlow=cashflow(startDate,tradeDate,couponRate,notional, margin, paymentFreq, maturityDate, cashFlowCurr,0,0);
	
	//cout<<"****************NVs streams starts*************"<<endl;
	//testCashFlow.printNVs();
	//cout<<"****************NVs streams ends*************"<<endl;

	//cout<<"****************PVs streams starts*************"<<endl;
	//testCashFlow.printPVs();
	//cout<<"****************PVs streams ends*************"<<endl;
	//cout<<"total MPVs="<<testCashFlow.MPV()<<endl;
}

void CashFlowTest() {

	cout << "******** CashFlow Test starts********" << endl;
	date fixingDate(2013,11,2);
	date paymentDate(2014,2,6);
	date accuralStartDate(2013,11,3);
	date accuralEndDate(2014,2,5);
	double notional=1000000;
	double couponRate=0.05;
	int paymentFreq=4;
	currency cashFlowCurr=currency(enums::USD,enums::ACT_360, enums::ACT_ACT, enums::Mfollowing, paymentFreq,1);

	cashflow testCashFlow(couponRate,notional,  fixingDate, paymentDate,accuralStartDate, accuralEndDate, cashFlowCurr);
	cout<<"couponRate="<<couponRate<<endl;
	
	cout<<"fixingDate=";
	testCashFlow.getFixingDate().printDate();
	cout<<endl;

	cout<<"paymentDate=";
	testCashFlow.getPaymentDate().printDate();
	cout<<endl;

	cout<<"accuralStartDate=";
	testCashFlow.getAccuralStartDate().printDate();
	cout<<endl;

	cout<<"accuralEndDate=";
	testCashFlow.getAccuralEndDate().printDate();
	cout<<endl;

	//cout<<"cashFlowCurr="<<testCashFlow.getCashFlowCurr().getCurrencyName()<<endl;
	cout<<"accuralFactor="<<testCashFlow.getAccuralFactor()<<endl;
	cout<<"couponAmonunt="<<testCashFlow.getCouponAmount()<<endl;
	cout<<"notional="<<testCashFlow.getNotional()<<endl;
	cout << "******** CashFlow Test ends********" << endl;

}