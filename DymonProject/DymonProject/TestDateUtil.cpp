//created by Wang Jianwei on 1 Dec 2012
#include "TestDateUtil.h"
#include <cmath>
#include <string>
#include <iostream>
#include <sstream>

	using namespace UnitTest;
using namespace utilities;
using namespace std;

typedef AbstractTest super;

void TestDateUtil::runTest(){
	_EPSILON = 0.000001;
	dayRollAdjustTestSuit();
	getEndDateTestSuit();
	DayCountTestSuit();
}

void TestDateUtil::dayRollAdjustTestSuit(){
	cout << "******** DayRollAdjust Test ********" << endl;
	{
		date date0(2456270);
		date date1(2012,12,8);
		cout<<date0.isEqual(date1)<<endl;} 
	{
		date date0(2011,9,18);
		date date1 = dateUtil::dayRollAdjust(date0, Following, USD);
		date date2(2011,9,19);
		cout<<date1.isEqual(date2)<<endl;}
	{
		date date0(2011,9,18);
		date date1 = dateUtil::dayRollAdjust(date0, Preceding, USD);
		date date2(2011,9,16);
		cout<<date1.isEqual(date2)<<endl;}
	{
		date date0(2011,7,30);
		date date1 = dateUtil::dayRollAdjust(date0, Mfollowing, USD);
		date date2(2011,7,29);
		cout<<date1.isEqual(date2)<<endl;}
	{
		date date0(2011,7,30);
		date date1 = dateUtil::dayRollAdjust(date0, Mfollowingbi, USD);
		date date2(2011,7,29);
		cout<<date1.isEqual(date2)<<endl;}
	{
		date date0(2011,10,15);
		date date1 = dateUtil::dayRollAdjust(date0, Mfollowingbi, USD);
		date date2(2011,10,14);
		cout<<date1.isEqual(date2)<<endl;}
}

void TestDateUtil::getEndDateTestSuit(){
	cout << "******** GetEndDate Test ********" << endl;
	{
		date date0(2012,1,31);
		date date1 = dateUtil::getEndDate(date0, 1, Preceding,USD,dateUtil::MONTH);
		date date2(2012,2,29);
		cout<<date1.isEqual(date2)<<endl;}
	{
		date date0(2012,10,31);
		date date1 = dateUtil::getEndDate(date0, 4, Preceding,USD,dateUtil::MONTH);
		date date2(2013,2,28);
		cout<<date1.isEqual(date2)<<endl;}
	{
		date date0(2012,10,31);
		date date1 = dateUtil::getEndDate(date0, 4, Following,USD,dateUtil::MONTH);
		date date2(2013,3,1);
		cout<<date1.isEqual(date2)<<endl;}
	{
		date date0(2012,10,31);
		date date1 = dateUtil::getEndDate(date0, 4, Mfollowing,USD,dateUtil::MONTH);
		date date2(2013,2,28);
		cout<<date1.isEqual(date2)<<endl;}
}

void TestDateUtil::DayCountTestSuit(){
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

void compareResult(std::string testName, date derivedVal, date expectedVal){
}