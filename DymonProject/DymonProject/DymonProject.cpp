// DymonProject.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "date.h"
#include "dateUtil.h"
#include "zero.h"
#include "cashflow.h"
#include "RecordHelper.h"
#include "BuilderCashFlowLeg.h"
#include <math.h>
#include "currency.h"
#include <vector>
#include "Enums.h"
#include "swap.h"
#include "TestNumerical.h"
#include "TestInterpolator.h"
#include "YieldCurveBuilder.h"
#include "YieldCurve.h"

using namespace utilities;
using namespace std;
using namespace instruments;
using namespace Session;
using namespace UnitTest;
using namespace enums;

void RecordTest();
void DateUtilTest();
void CashFlowLegTest();
void CashFlowTest();
void SwapTest();
void buildYieldCurve();

int _tmain(int argc, _TCHAR* argv[])
{
	//DateUtilTest();
	//RecordTest();
	//CashFlowTest();
    //CashFlowLegTest();
	//TestNumerical numericalTest;
	//numericalTest.runTest();
	//TestInterpolator interpolatorTest;
	//interpolatorTest.runTest();
	//SwapTest();

	buildYieldCurve();
}

void buildYieldCurve(){
	cout << "******** Build Record Helper ********\n" << endl;
	RecordHelper* recordHelper = RecordHelper::getInstance();
	recordHelper->init(Configuration::getInstance());
	cout << "\n******** Build Yield Curve ********\n" << endl;
	YieldCurveBuilder* builder = new YieldCurveBuilder();
	builder->init(Configuration::getInstance());
	YieldCurve* yc = builder->build();
	cout<<yc->toString()<<endl;
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
	currency cashFlowCurr=currency(enums::USD);
	cashFlowCurr.setDayCountCashConvention(enums::ACT_360);
	cashFlowCurr.setDayCountSwapConvention(enums::ACT_ACT);
	cashFlowCurr.setDayRollCashConvention(enums::Mfollowing);

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

void CashFlowLegTest()  {
	date startDate(2013,11,2);
	date maturityDate(2015,2,6);
	//date accuralStartDate(2013,11,3);
	//date accuralEndDate(2014,2,5);
	
	double notional=1000000;
	double couponRate=0.05;
	int paymentFreq=4;
	//build from start to end (build forward)
	int buildDirection=1;
	RecordHelper::HolidayMap holidayMap;
	bool rollAccuralDates=false;

	currency cashFlowLegCurr=currency(enums::USD);
	cashFlowLegCurr.setDayCountCashConvention(enums::ACT_360);
	cashFlowLegCurr.setDayCountSwapConvention(enums::ACT_ACT);
	cashFlowLegCurr.setDayRollCashConvention(enums::Mfollowing);

	BuilderCashFlowLeg testCashFlowLeg(startDate, maturityDate,couponRate,notional, paymentFreq, cashFlowLegCurr, rollAccuralDates, buildDirection,holidayMap);

	cout<<"**********************************************"<<endl;
	cout << "******** CashFlowLeg Build Test starts********" << endl;

	std::vector<cashflow> cfVector=testCashFlowLeg.getCashFlowLeg().getCashFlowVector();
	std::vector<cashflow>::iterator it=cfVector.begin();

	cout<<"start date=";
	startDate.printDate();
	cout<<endl;

	cout<<"maturity date=";
	maturityDate.printDate();
	cout<<endl;

	cout<<endl;
	int i=0;
	for (;it!=cfVector.end();it++) {
	 cashflow aCF(*it);
	 cout<<"*********CF stream #"<<++i<<"****************"<<endl;
	 cout<<"fixingDate=";
	 aCF.getFixingDate().printDate();
	 cout<<endl;
	 cout<<"accuralStartDate=";
	 aCF.getAccuralStartDate().printDate();
	 cout<<endl;
	 cout<<"accuralEndDate=";
	 aCF.getAccuralEndDate().printDate();
	 cout<<endl;
	 cout<<"paymentDate=";
	 aCF.getPaymentDate().printDate();
	 cout<<endl;
	 cout<<"accuralFactor=";
	 

	 cout<<aCF.getAccuralFactor()<<endl;
	 cout<<"couponAmonunt=";

	 cout<<aCF.getCouponAmount()<<endl;
	 cout<<"notional=";
	 cout<<aCF.getNotional()<<endl;
	 cout<<endl;
	 
	}

	cout <<"Total number of CF streams="<<i<<endl;
	cout << "******** CashFlowLeg Build Test ends***********************" << endl;
	std::cout << (-20 % 12) << std::endl;
	cout<<"****************************************************"<<endl;

	buildDirection=-1;
	BuilderCashFlowLeg testCashFlowLegReverse(startDate, maturityDate,couponRate,notional, paymentFreq, cashFlowLegCurr, rollAccuralDates, buildDirection,holidayMap);

	
	cout<<"**********************************************"<<endl;
	cout << "******** CashFlowLeg ReverseBuild Test starts********" << endl;

	std::vector<cashflow> cfVectorR=testCashFlowLegReverse.getCashFlowLeg().getCashFlowVector();
	std::vector<cashflow>::iterator itR=cfVectorR.begin();

	cout<<"start date=";
	startDate.printDate();
	cout<<endl;

	cout<<"maturity date=";
	maturityDate.printDate();
	cout<<endl;

	cout<<endl;
	i=0;
	for (;itR!=cfVectorR.end();itR++) {
	 cashflow aCF(*itR);
	 cout<<"*********CF stream #"<<++i<<"****************"<<endl;
	 cout<<"fixingDate=";
	 aCF.getFixingDate().printDate();
	 cout<<endl;
	 cout<<"accuralStartDate=";
	 aCF.getAccuralStartDate().printDate();
	 cout<<endl;
	 cout<<"accuralEndDate=";
	 aCF.getAccuralEndDate().printDate();
	 cout<<endl;
	 cout<<"paymentDate=";
	 aCF.getPaymentDate().printDate();
	 cout<<endl;
	 cout<<"accuralFactor=";
	 

	 cout<<aCF.getAccuralFactor()<<endl;
	 cout<<"couponAmonunt=";

	 cout<<aCF.getCouponAmount()<<endl;
	 cout<<"notional=";
	 cout<<aCF.getNotional()<<endl;
	 cout<<endl;
	 
	}

	cout <<"Total number of CF streams="<<i<<endl;
	cout << "******** CashFlow ReverseBuild Test ends***********************" << endl;
	cout<<"****************************************************"<<endl;

	int tenorNumMonth=12;

	BuilderCashFlowLeg testCashFlowLegTenor(startDate, tenorNumMonth, couponRate, notional,  paymentFreq, cashFlowLegCurr,rollAccuralDates,holidayMap);

	
	cout<<"**********************************************"<<endl;
	cout << "******** CashFlowLeg TenorBuild Test starts********" << endl;

	std::vector<cashflow> cfVectorT=testCashFlowLegTenor.getCashFlowLeg().getCashFlowVector();
	std::vector<cashflow>::iterator itT=cfVectorT.begin();

	cout<<"start date=";
	startDate.printDate();
	cout<<endl;

	cout<<"tenorNumOfMonths="<<tenorNumMonth<<endl;
	
	cout<<endl;

	cout<<endl;
	i=0;
	for (;itT!=cfVectorT.end();itT++) {
	 cashflow aCF(*itT);
	 cout<<"*********CF stream #"<<++i<<"****************"<<endl;
	 aCF.printCashFlow(); 
	}

	cout <<"Total number of CF streams="<<i<<endl;
	cout << "******** CashFlowLeg TenorBuild Test ends***********************" << endl;
	cout<<"****************************************************"<<endl;

	string s;
	getline(cin,s);
}

void SwapTest() {
	date tradeDate(2013,11,2);
	date maturityDate(2015,2,6);
		
	double notional=1000000;
	double couponRate=0.05;
	int paymentFreqFixLeg=4;
	int paymentFreqFloatingLeg=2;
	//build from start to end (build forward)
	int buildDirection=1;
	RecordHelper::HolidayMap holidayMap;
	bool rollAccuralDates=false;
	vector<double> FLiborRate;

	FLiborRate.resize(100,0.05);

	currency fixLegCurr=currency(enums::USD);
	currency floatingLegCurr=currency(enums::USD);
	
	fixLegCurr.setDayCountCashConvention(enums::ACT_360);
	fixLegCurr.setDayCountSwapConvention(enums::ACT_ACT);
	fixLegCurr.setDayRollCashConvention(enums::Mfollowing);
	
	floatingLegCurr.setDayCountCashConvention(enums::ACT_360);
	floatingLegCurr.setDayCountSwapConvention(enums::ACT_ACT);
	floatingLegCurr.setDayRollCashConvention(enums::Mfollowing);

	instruments::swap swap1(tradeDate, maturityDate, notional, couponRate, FLiborRate, fixLegCurr, floatingLegCurr,paymentFreqFixLeg, paymentFreqFloatingLeg, rollAccuralDates, holidayMap);

	cout<<"tradeDate=";
	tradeDate.printDate();
	cout<<endl;

	cout<<"maturityDate=";
	maturityDate.printDate();
	cout<<endl;

	cout<<"========================Fix Leg of Swap1 is:========================="<<endl;
	swap1.printCashflowLegFix();


	cout<<"========================Floating Leg of Swap1 is:===================="<<endl;
	swap1.printCashflowLegFloat();


}