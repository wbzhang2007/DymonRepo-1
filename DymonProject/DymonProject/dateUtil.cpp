//created by Hu Kun 30 Nov 2012
#include "dateUtil.h"
#include "date.h"
#include <math.h>
#include <iostream>
#include "DayCountEnum.h"
#include "DayRollEnum.h"

#include <ctime>

using namespace utilities;
using namespace enums;

long dateUtil::getJudianDayNumber(int year, int month, int day, date::CalendarType calendarType){
	date date0(year, month, day, calendarType);
	return date0.getJudianDayNumber();
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

date dateUtil::dayRoll(date aDate,DayRollEnum aDayRollConvention) {
	date dummy;
	return dummy;
}
//to be used by instruments namespaces to calc dates
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