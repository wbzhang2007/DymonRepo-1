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
#include "TestDateUtil.h"
#include "YieldCurveBuilder.h"
#include "YieldCurve.h"
#include "LinearInterpolator.h"

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
	RecordTest();
	//TestDateUtil dateUtilTest;
	//dateUtilTest.runTest();
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

void buildSampleCurve(){

	typedef tuple<date, double> point;
	date date0(10005);
	date date1(10006);
	date date2(10007);
	point point1(date0, 1);
	point point2(date1, 2);
	point point3(date2, 2.5);
	YieldCurve* yc = new YieldCurve();
	LinearInterpolator* li1 = new LinearInterpolator(point1, point2);
	LinearInterpolator* li2 = new LinearInterpolator(point2, point3);
	yc->insertLineSection(li1);
	yc->insertLineSection(li2);
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

void RecordTest(){
	cout << "******** RecordHelper Test ********" << endl;
	RecordHelper* recordHelper = RecordHelper::getInstance();
	recordHelper->init(Configuration::getInstance());
}

void CashFlowTest() {

	cout << "******** CashFlow Test starts********" << endl;
	date fixingDate(2013,11,2);
	date paymentDate(2014,2,6);
	date accrualStartDate(2013,11,3);
	date accrualEndDate(2014,2,5);
	double notional=1000000;
	double couponRate=0.05;
	int paymentFreq=4;
	currency cashFlowCurr=currency(enums::USD);
	cashFlowCurr.setDayCountCashConvention(enums::ACT_360);
	cashFlowCurr.setDayCountSwapConvention(enums::ACT_ACT);
	cashFlowCurr.setDayRollCashConvention(enums::Mfollowing);

	cashflow testCashFlow(couponRate,notional,fixingDate, paymentDate,accrualStartDate, accrualEndDate, cashFlowCurr);
	testCashFlow.printCashFlow();
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
	bool rollAccuralDates=false;

	currency cashFlowLegCurr=currency(enums::USD);
	cashFlowLegCurr.setDayCountCashConvention(enums::ACT_360);
	cashFlowLegCurr.setDayCountSwapConvention(enums::ACT_ACT);
	cashFlowLegCurr.setDayRollCashConvention(enums::Mfollowing);

	BuilderCashFlowLeg testCashFlowLeg(startDate, maturityDate,couponRate,notional, paymentFreq, enums::USD, buildDirection);

	cout << "******** CashFlowLeg Build Test starts********" << endl;

	std::vector<cashflow> cfVector=(*testCashFlowLeg.getCashFlowLeg()).getCashFlowVector();
	std::vector<cashflow>::iterator it=cfVector.begin();

	cout<<"start date="<<startDate.toString()<<endl;
	cout<<"maturity date="<<maturityDate.toString()<<endl<<endl;
	
	int i=0;
	for (;it!=cfVector.end();it++) {
	 cashflow aCF(*it);
	 cout<<"***CF stream #"<<++i<<":"<<endl;
	 aCF.printCashFlow();	 
	}

	cout <<"Total number of CF streams="<<i<<endl;
	std::cout << (-20 % 12) << std::endl;
	cout<<"****************************************************"<<endl<<endl;

	buildDirection=-1;
	BuilderCashFlowLeg testCashFlowLegReverse(startDate, maturityDate,couponRate,notional, paymentFreq, enums::USD, buildDirection);

	
	cout << "******** CashFlowLeg ReverseBuild Test starts********" << endl;

	std::vector<cashflow> cfVectorR=(*testCashFlowLegReverse.getCashFlowLeg()).getCashFlowVector();
	std::vector<cashflow>::iterator itR=cfVectorR.begin();

	cout<<"start date="<<startDate.toString()<<endl;
	cout<<"maturity date="<<maturityDate.toString()<<endl<<endl;

	i=0;
	for (;itR!=cfVectorR.end();itR++) {
	 cashflow aCF(*itR);
	 cout<<"***CF stream #"<<++i<<":"<<endl;
	 aCF.printCashFlow();	 
	}

	cout <<"Total number of CF streams="<<i<<endl<<endl;

	int tenorNumMonth=12;

	BuilderCashFlowLeg testCashFlowLegTenor(startDate, tenorNumMonth, couponRate, notional,  paymentFreq, enums::USD);

	cout << "******** CashFlowLeg TenorBuild Test starts********" << endl;

	std::vector<cashflow> cfVectorT=(*testCashFlowLegTenor.getCashFlowLeg()).getCashFlowVector();
	std::vector<cashflow>::iterator itT=cfVectorT.begin();
	
	cout<<"start date="<<startDate.toString()<<endl;
	cout<<"tenorNumOfMonths="<<tenorNumMonth<<endl<<endl<<endl;

	i=0;
	for (;itT!=cfVectorT.end();itT++) {
	 cashflow aCF(*itT);
	 cout<<"***CF stream #"<<++i<<":"<<endl;
	 aCF.printCashFlow(); 
	}

	cout <<"Total number of CF streams="<<i<<endl<<endl;

	string s;
	getline(cin,s);
}

void SwapTest() {
	date tradeDate(2013,11,2);
	date maturityDate(2015,2,6);
	
	
	double notional=1000000;
	double couponRate=0.05;
	int paymentFreqFixLeg=2;
	int paymentFreqFloatingLeg=4;
	//build from start to end (build forward)
	int buildDirection=1;
	RecordHelper::HolidayMap holidayMap;
	bool rollAccuralDates=false;
	vector<double> FLiborRate;

	FLiborRate.resize(100,0.05);

	 typedef tuple<date, double> point;
	 date date0(2013,11,2);
	 date date1(2015,2,6);
	 date date2(2016,2,6);
	 point point1(date0, 1);
	 point point2(date1, 2);
	 point point3(date2, 2.5);
	 YieldCurve* yc = new YieldCurve();
	 LinearInterpolator* li1 = new LinearInterpolator(point1, point2);
	 LinearInterpolator* li2 = new LinearInterpolator(point2, point3);
	 yc->insertLineSection(li1);
	 yc->insertLineSection(li2);

	currency fixLegCurr=currency(enums::USD);
	currency floatingLegCurr=currency(enums::USD);
	
	fixLegCurr.setDayCountCashConvention(enums::ACT_360);
	fixLegCurr.setDayCountSwapConvention(enums::ACT_ACT);
	fixLegCurr.setDayRollCashConvention(enums::Mfollowing);
	
	floatingLegCurr.setDayCountCashConvention(enums::ACT_360);
	floatingLegCurr.setDayCountSwapConvention(enums::ACT_ACT);
	floatingLegCurr.setDayRollCashConvention(enums::Mfollowing);

	instruments::swap swap1(tradeDate, maturityDate, notional, couponRate, yc, fixLegCurr, floatingLegCurr,paymentFreqFixLeg, paymentFreqFloatingLeg, rollAccuralDates, holidayMap);

	cout<<"tradeDate=";
	tradeDate.printDate();
	cout<<endl;

	cout<<"maturityDate=";
	maturityDate.printDate();
	cout<<endl;
	
	cashflowLeg fixLeg=swap1.getCashflowLegFix();
	cashflowLeg floatLeg=swap1.getCashflowLegFloat();
	YieldCurve aYC=*yc;
	cout<<"MPV="<<swap1.getMPV(fixLeg,floatLeg,aYC)<<endl;
	
	//cout<<"ParRate="<<swap1.getParRate(fixLeg,floatLeg,aYC)<<endl;
	
	cout<<"========================Fix Leg of Swap1 is:========================="<<endl;
	swap1.printCashflowLegFix();


	cout<<"========================Floating Leg of Swap1 is:===================="<<endl;
	swap1.printCashflowLegFloat();


}