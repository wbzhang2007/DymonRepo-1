//created by Wang Jianwei on 30 Nov 2012

#ifndef _DATEUTIL_H
#define _DATEUTIL_H

#include "date.h"
#include "Enums.h"

using namespace enums;

namespace utilities {
	class dateUtil {

	public:
		static long getJudianDayNumber(unsigned short year, unsigned short month, unsigned short day);

		static long getDaysBetween(date startDate, date endDate);

		static long getBizDaysBetween(date startDate, date endDate);

	    static bool isBizDay(date date0);

		static bool isHoliday(date aDate, std::string city);

		static int getTodayYear();
		static int getTodayMonth();
		static int getTodayDay();
		static unsigned short* getYearMonthDay(long JDN);

		//to be used by instruments namespaces to calc dates
		static date getBizDate(date refDate, long bias, enums::DayRollEnum dayRollType);
		static date getEndDate(date refDate, int numMonth, bool adjustInvalidDay);
		static date dayRollAdjust(date aDate,enums::DayRollEnum aDayRollConvention, std::string city);

	private:

		static long getDaysBetween(long startJDN, long endJDN);		
		static long getBizDaysBetween(long startJDN, long endJDN);
	    static bool isBizDay(long JDN);
		static bool isHoliday(long JDN, std::string city);
		static bool isleapyear(unsigned short year);
		static long getPrecedingJDN(long JDN, std::string city);
		static long getFolloingJDN(long JDN, std::string city);
		static date adjustInvalidateDate(date aDate);
	};
}

#endif