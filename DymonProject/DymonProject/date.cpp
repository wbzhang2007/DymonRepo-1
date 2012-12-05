//created by Wang Jianwei on 29 Nov 2012
//added functions to get today's year, month and day-Hu Kun 2 Dec

#include "date.h"
#include "dateUtil.h"

using namespace std;

namespace utilities {

	date::date() {};
	date::date(int year, int month, int day, CalendarType calendarType){
		if (year<=0 || month<=0 || day<=0)
			throw "Year/Month/Day must be larger than 0";
		_year=year;
		_month=month;
		_day=day;
		_calendarType = calendarType;
		setJudianDayNumber();
	}
	
	date::date(long JDN, CalendarType calendarType){
	}

	date::~date(){
	}

	void date::setJudianDayNumber(){
		_a=(14-_month)/12;
		_y=_year+4800-_a;
		_m=_month+12*_a-3;
		if (_calendarType==Gregorian){
			_judianDayNumber=_day+(int)((153*_m+2)/5)+365*_y+(int)(_y/4)-(int)(_y/100)+(int)(_y/400)-32045;
		}else if (_calendarType==Judian){
			_judianDayNumber=_day+(int)((153*_m+2)/5)+365*_y+(int)(_y/4)-32083;
		}
	}

	

	long date::getJudianDayNumber(){
		return _judianDayNumber;
	}

	int date::getYear(){
		return _year;
	}

	int date::getMonth(){
		return _month;
	}

	int date::getDay(){
		return _day;
	}
	
}