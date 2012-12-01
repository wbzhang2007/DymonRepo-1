//created by Hu Kun on 29 Nov 2012

#ifndef DATE_H
#define DATE_H
namespace utilities {
	class date {

	public:
		
		enum CalendarType{Judian, Gregorian};
		date(int year, int month, int day, CalendarType calendarType);
		~date();
		int getYear();
		int getMonth();
		int getDay();
		bool isBusinessDay();
		long getJudianDayNumber();

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