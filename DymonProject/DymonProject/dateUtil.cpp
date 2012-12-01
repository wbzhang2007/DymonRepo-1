//created by Hu Kun 30 Nov 2012
#include "dateUtil.h"
#include "date.h"
#include <math.h>
#include <iostream>

using namespace utilities;

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
		(endDate.getJudianDayNumber(),startDate.getJudianDayNumber());
}

long dateUtil::getBizDaysBetween(long startJDN, long endJDN){
	long numBizDay=0;
	for (long i = startJDN; i<endJDN; i++){
		if (isBizDay(i)) numBizDay++;
	}
	return numBizDay;
}

bool dateUtil::isBizDay(long isjudianDayNumber){
	int dayOfWeek = 1 + fmod(isjudianDayNumber+1,7.0);
	if (dayOfWeek==1||dayOfWeek==7){
		return false;
	}
	return true;
}

date dateUtil::getJudianDate(long judianDayNumber){
	throw "Not implemented for now!";
}

date dateUtil::getGregorianDate(long judianDayNumber){
	throw "Not implemented for now!";
}
