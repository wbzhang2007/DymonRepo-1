//created by Wang Jianwei on 30 Nov 2012

#ifndef _DATEUTIL_H
#define _DATEUTIL_H

#include "date.h"

namespace utilities {
	class dateUtil {
	public:
		static long getJudianDayNumber(int year, int month, int day, date::CalendarType calendarType);

		static long getJudianDayNumber(utilities::date date0);

		static long getDaysInbetween(utilities::date startDate, utilities::date endDate);

		static utilities::date getJudianDate(long judianDayNumber);

		static utilities::date getGregorianDate(long judianDayNumber);
	}
}

#endif