// DymonProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "date.h"
#include "dateUtil.h"
#include <iostream>

using namespace utilities;
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	date date0(2012,12,1,date::Gregorian);
	cout<<date0.getJudianDayNumber()<<" "<<date0.isBusinessDay()<<endl;
	date date1(2012,12,8,date::Gregorian);
	cout<<date1.getJudianDayNumber()<<" "<<date1.isBusinessDay()<<endl;
	cout<<"Days inbetween: "<<dateUtil::getDaysBetween(date0, date1)<<endl;
	cout<<"Business days inbetween: "<<dateUtil::getBizDaysBetween(date0, date1)<<endl;
	cout<<"Today is "<<date0.getTodayYear()<<" "<<date0.getTodayMonth()<<" "<<date0.getTodayDay()<<endl;
}

