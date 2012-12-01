//created by Hu Kun on 29 Nov 2012

#ifndef DATE_H
#define DATE_H
namespace utilities {
	class date {

		enum CalendarType{Judian, Gregorian};

	public:

		date(int year, int month, int day, CalendarType calendarType);
		~date();
		long getJudianDayNumber();
		void setJudianDayNumber();

	private:
		int year;
		int month;
		int day;
		bool isBusinessDay;
		long judianDayNumber;
		CalendarType calendarType;
	};
}
#endif