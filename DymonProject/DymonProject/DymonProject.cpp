// DymonProject.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "date.h"
#include "dateUtil.h"
#include "zero.h"
#include "DymonRecordHelper.h"

using namespace utilities;
using namespace std;
using namespace instruments;
using namespace Session;

void RecordTest();

int _tmain(int argc, _TCHAR* argv[])
{

	RecordTest();
}

void ZeroTest(){
	date date0(2012,12,1,date::Gregorian);
	//cout<<date0.getJudianDayNumber()<<" "<<date0.isBusinessDay()<<endl;
	date date1(2012,12,8,date::Gregorian);
	date date2(2013,12,1,date::Gregorian);
	date date3(2012,1,1,date::Gregorian);

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
	Configuration cfg;
	DymonRecordHelper* recordHelper = new DymonRecordHelper();
	recordHelper->init(cfg);
	for(map<string, set<long>>::iterator outer_iter=DymonRecordHelper::holidayMap.begin(); outer_iter!=DymonRecordHelper::holidayMap.end(); ++outer_iter) {
		for(set<long>::iterator inner_iter=outer_iter->second.begin(); inner_iter!=outer_iter->second.end(); ++inner_iter) {
			cout << outer_iter->first<< " -> " << *inner_iter << endl;
		}
	}
}