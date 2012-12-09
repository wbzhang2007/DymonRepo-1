//created by Hu Kun 30 Nov 2012
#include "dateUtil.h"
#include "date.h"
#include <math.h>
#include <iostream>
#include "DymonRecordHelper.h"
#include <ctime>

using namespace utilities;
using namespace Session;
using namespace std;

long dateUtil::getJudianDayNumber(unsigned short year, unsigned short month, unsigned short day){
	int	_a=(14-month)/12;
	int _y=year+4800-_a;
	int _m=month+12*_a-3;
	//if (_calendarType==Gregorian){
	return day+(int)((153*_m+2)/5)+365*_y+(int)(_y/4)-(int)(_y/100)+(int)(_y/400)-32045;
	/*}else if (_calendarType==Judian){
		_judianDayNumber=_day+(int)((153*_m+2)/5)+365*_y+(int)(_y/4)-32083;
	}*/
}

long dateUtil::getDaysBetween(date startDate, date endDate){
	return getDaysBetween
		(endDate.getJudianDayNumber(),startDate.getJudianDayNumber());
}

long dateUtil::getDaysBetween(long startJDN, long endJDN){
	return startJDN-endJDN;
}

long dateUtil::getBizDaysBetween(date startDate, date endDate){
	return getBizDaysBetween
		(startDate.getJudianDayNumber(),endDate.getJudianDayNumber());
}

long dateUtil::getBizDaysBetween(long startJDN, long endJDN){
	long numBizDay=0;
	for (long i = 0; i<endJDN-startJDN; i++){
		if (isBizDay(i)) numBizDay++;
	}
	return numBizDay;
}

bool dateUtil::isBizDay(date date0){
	return isBizDay(date0.getJudianDayNumber());
}

bool dateUtil::isBizDay(long JDN){
	int dayOfWeek = 1 + fmod(JDN+1,7.0);
	if (dayOfWeek==1||dayOfWeek==7){
		return false;
	}
	return true;
}

bool dateUtil::isHoliday(long JDN, std::string city){
	if (city=="") return false;
	if (DymonRecordHelper::holidayMap.find(city)== DymonRecordHelper::holidayMap.end());
		throw "City not found in Holiday Map: "+city;

	set<long> holidaySet = DymonRecordHelper::holidayMap[city];
	if (holidaySet.find(JDN) != holidaySet.end())
		return false;
	return true;
}

bool dateUtil::isHoliday(date aDate, std::string city){
	return isHoliday(aDate,city);
}

int dateUtil::getTodayDay() {
		time_t     rawtime;
		struct tm* timeinfo;

		time( &rawtime );
		timeinfo = localtime( &rawtime );
		return timeinfo->tm_mday;
		
	}
int dateUtil::getTodayMonth() {
		time_t     rawtime;
		struct tm* timeinfo;

		time( &rawtime );
		timeinfo = localtime( &rawtime );
		return 1+timeinfo->tm_mon;
	
}
	
int dateUtil::getTodayYear() {
		time_t     rawtime;
		struct tm* timeinfo;

		time( &rawtime );
		timeinfo = localtime( &rawtime );
		return 1900+timeinfo->tm_year;

}

unsigned short* dateUtil::getYearMonthDay(long JDN){
	unsigned short _year, _month, _day;
	JDN = JDN - 1721119 ;
	_year = (4 * JDN - 1) / 146097 ; 
	JDN = 4 * JDN - 1 - 146097 * _year ; 
	_day = JDN / 4 ;
	JDN = (4 * _day + 3) / 1461 ; 
	_day = 4 * _day + 3 - 1461 * JDN ; 
	_day = (_day + 4) / 4 ;
	_month = (5 * _day - 3) / 153 ; 
	_day = 5 * _day - 3 - 153 * _month ; 
	_day = (_day + 5) / 5 ;
	_year = 100 * _year + JDN ;
	if (_month < 10){
		_month = _month + 3;
	}
	else{
		_month = _month - 9 ; _year = _year + 1;
	}
	unsigned short yearMonthDay[3] = {_year,_month,_day};
	return yearMonthDay;
}

double dateUtil::getAccrualFactor(date startDate,date endDate, enums::DayCountEnum dayCount){
	double accrualFactor;
	switch(dayCount){
	case thirty_360US:
		break;
	case thirthE_360:
		break;
	case ACT_360:
		break;
	case ACT_365:
		break;
	case ACT_ACT:
		break;
	}
	return accrualFactor;
}

date dateUtil::dayRollAdjust(date aDate,DayRollEnum aDayRollConvention, string city) {
	long adjustedJDN;
	switch(aDayRollConvention){
	case Following:
		adjustedJDN = getFolloingJDN(aDate.getJudianDayNumber(), city);
		break;
	case Preceding:
		adjustedJDN = getPrecedingJDN(aDate.getJudianDayNumber(), city);
		break;
	case Mfollowing:
		adjustedJDN = getFolloingJDN(aDate.getJudianDayNumber(), city);
		if (getYearMonthDay(adjustedJDN)[1]!=getYearMonthDay(aDate.getJudianDayNumber())[1])
			adjustedJDN = getPrecedingJDN(aDate.getJudianDayNumber(), city);
		break;
	case Mfollowingbi:	
		adjustedJDN = getFolloingJDN(aDate.getJudianDayNumber(), city);
		if (getYearMonthDay(adjustedJDN)[2]!=getYearMonthDay(aDate.getJudianDayNumber())[2]||
			getYearMonthDay(adjustedJDN)[3]>=15)
			adjustedJDN = getPrecedingJDN(aDate.getJudianDayNumber(), city);
		break;
	case EOM:
		break;
	}
	date adjustedDate(adjustedJDN);
	return adjustedDate;
}

// *** To be deprecated ***
date dateUtil::getBizDate(date refDate, long bias, DayRollEnum dayRollType) {
	//long refDateJudianNum=refDate.getJudianDayNumber();

	//if (dateUtil::getJudianDate(refDateJudianNum+bias).isBusinessDay()) {
	//	return dateUtil::getJudianDate(refDateJudianNum+bias);
	//}
	//else {
	//	return refDate;
	//}
	return refDate;
}

date dateUtil::getEndDate(date startDate, int numMonth, bool adjustInvalidDay){
	unsigned short startMonth = startDate.getMonth();
	unsigned short endMonth = (startMonth + numMonth)%12;
	unsigned short endYear = startDate.getYear()+(startMonth + numMonth)/12;
	date endDate(endYear, endMonth, startDate.getDay());
	endDate = adjustInvalidateDate(endDate);
	return endDate;
}

date dateUtil::adjustInvalidateDate(date aDate){
	unsigned short monthlen[]={31,28,31,30,31,30,31,31,30,31,30,31};
	if (isleapyear(aDate.getYear()) && aDate.getMonth()==2)
		monthlen[1]++;
	if (aDate.getDay()>monthlen[aDate.getMonth()-1]){
			aDate.setDay(monthlen[aDate.getMonth()-1]);
	}
	return aDate;
}

bool dateUtil::isleapyear(unsigned short year){
	return (!(year%4) && (year%100) || !(year%400));
}

long dateUtil::getPrecedingJDN(long JDN, std::string city){
	while(!isBizDay(JDN) && !isHoliday(JDN,city)){
		JDN--;
	}
	return JDN;
}

long dateUtil::getFolloingJDN(long JDN, std::string city){
	while(!isBizDay(JDN) && !isHoliday(JDN,city)){
		JDN++;
	}
	return JDN;
}

