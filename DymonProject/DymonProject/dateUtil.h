//created by Wang Jianwei on 30 Nov 2012

#ifndef _DATEUTIL_H
#define _DATEUTIL_H

#include "date.h"
#include "DayCountEnum.h"
#include "DayRollEnum.h"

using namespace enums;

namespace utilities {
	class dateUtil {

	public:
		static long getJudianDayNumber(int year, int month, int day, date::CalendarType calendarType);

		static long getDaysBetween(date startDate, date endDate);

		static long getBizDaysBetween(date startDate, date endDate);

	    static bool isBizDay(date date0);

		static int getTodayYear();
		static int getTodayMonth();
		static int getTodayDay();

		//to be used by instruments namespaces to calc dates
		static date getBizDate(date refDate, long bias, DayRollEnum dayRollType);
		static date dayRoll(date aDate,DayRollEnum aDayRollConvention);

	private:

		static long getDaysBetween(long startJDN, long endJDN);		
		static long getBizDaysBetween(long startJDN, long endJDN);
	    static bool isBizDay(long JDN);

	};
}

#endif