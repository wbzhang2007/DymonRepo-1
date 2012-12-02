// DymonProject.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "date.h"
#include "dateUtil.h"
#include <iostream>
#include "zero.h"
#include <fstream>
#include <string>

using namespace utilities;
using namespace std;
using namespace instruments;

int _tmain(int argc, _TCHAR* argv[])
{
	//date date0(2012,12,1,date::Gregorian);
	////cout<<date0.getJudianDayNumber()<<" "<<date0.isBusinessDay()<<endl;
	//date date1(2012,12,8,date::Gregorian);
	//date date2(2013,12,1,date::Gregorian);
	//date date3(2012,1,1,date::Gregorian);

	//zero zero1(0.001,1,date2,date0);

	////cout<<date1.getJudianDayNumber()<<" "<<date1.isBusinessDay()<<endl;
	////cout<<"Days inbetween: "<<dateUtil::getDaysBetween(date0, date1)<<endl;
	////cout<<"Business days inbetween: "<<dateUtil::getBizDaysBetween(date1, date2)<<endl;
	////cout<<"Today is "<<dateUtil::getTodayYear()<<" "<<dateUtil::getTodayMonth()<<" "<<dateUtil::getTodayDay()<<endl;
	//cout<<"zero1 price is "<<zero1.getPrice()<<endl;
	//cout<<"zero2 implied spot rate is "<<zero1.getImpliedSpotRate()<<endl;

	//ofstream outFile("test.txt");
	//outFile<<"content test"<<endl;
	//outFile<<1.23<<endl;
	//outFile.close();

	string str1;
	string str2;
	char output[50];
	ifstream inFile;
	inFile.open("test1.txt");
	if (inFile.is_open()){
		inFile.read(output, 50);
		cout<<output<<endl;
	}
	//inFile>>str1>>str2;
	//cout<<str1<<str2<<endl;
	inFile.close();

}

