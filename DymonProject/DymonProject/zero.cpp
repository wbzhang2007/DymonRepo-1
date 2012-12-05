//created by Hu Kun 1 Dec 2012
#include "dateUtil.h"
#include "date.h"
#include "zero.h"
#include <math.h>
#include "instrumentBase.h"
#include <stdio.h>

using namespace std;
using namespace utilities;

namespace instruments {
zero::zero() {
	//spotRate=0;
	//notional=0;
	
	//date maturityDate;
	//price=0;
	//date issueDate;
	
	//date todayDate;
}
zero::zero(double aSpotRate,double aNotional,date aMaturityDate,date aIssueDate) {

	int yy=dateUtil::getTodayYear();
	int mm=dateUtil::getTodayMonth();
	int dd=dateUtil::getTodayDay();

	cout<<"today is yy mm dd="<<yy<<" "<<mm<<" "<<dd<<endl;
	todayDate=date(yy,mm,dd,date::Gregorian);

	spotRate=aSpotRate;
	notional=aNotional;
	maturityDate=aMaturityDate;
	price=getPrice();
	issueDate=aIssueDate;
	
	

	cout<<"maturity date is yy="<<maturityDate.getYear()<<" mm="<<maturityDate.getMonth()<<" dd="<<maturityDate.getDay()<<endl;

	
}

zero::~zero() {

	//delete &price;
	//delete &spotRate;
	//delete &notional;
	maturityDate.~date();
	issueDate.~date();
	todayDate.~date();

}

//double zero::getPriceWrapper() {
	//return getPrice(spotRate,notional,maturityDate,issueDate);
//}

//double zero::getImpliedSpotRateWrapper() {
	//return getImpliedSpotRate(price,notional,maturityDate,issueDate);
//}

double zero::getPrice(){
	
	long numBizDays=dateUtil::getBizDaysBetween(todayDate,maturityDate);
	float fraction=(float)numBizDays/365;
	cout<<"fraction="<<fraction<<endl;
	cout<<"numBizDays="<<numBizDays<<endl;

	double result=notional*exp(0-spotRate*fraction);
	return result;
}

double zero::getImpliedSpotRate() {

	return -log(price/notional)/((float)dateUtil::getBizDaysBetween(todayDate,maturityDate)/365);
}

date zero::getIssueDate() {
	return issueDate;

}

date zero::getMaturityDate() {
	return maturityDate;
}

void zero::setIssueDate(date aIssueDate) {
	issueDate=aIssueDate;

}

void zero::setMaturityDate(date aMaturityDate){
	maturityDate=aMaturityDate;
}

}