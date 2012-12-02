//created by Hu Kun on 29 Nov 2012
//added functions to get today's year, month and day-Hu Kun 2 Dec

#ifndef DATE_H
#define DATE_H

#include <ctime>
#include <iostream>

namespace utilities {
	class date {

	public:
		
		enum CalendarType{Judian, Gregorian};
		date();
		date(int year, int month, int day, CalendarType calendarType);
		~date();
		int getYear();
		int getMonth();
		int getDay();
		bool isBusinessDay();
		long getJudianDayNumber();
		int getTodayYear();
		int getTodayMonth();
		int getTodayDay();
	private:

		int _year;
		int _month;
		int _day;
		bool _isBusinessDay;
		long _judianDayNumber;
		CalendarType _calendarType;
		void setIsBusinessDay();
		void setJudianDayNumber();
		
		int _a;
		int _y;
		int _m;
	};
}
#endif