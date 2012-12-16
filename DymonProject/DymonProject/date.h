//created by Hu Kun on 29 Nov 2012
//added functions to get today's year, month and day-Hu Kun 2 Dec

#ifndef DATE_H
#define DATE_H

#include <ctime>
#include <iostream>
#include <string>

using namespace std;

namespace utilities {
	class date {

	public:
		
		date();
		date(unsigned short year, unsigned short month, unsigned short day);
		date(long JDN);
		~date();
		int getYear();
		int getMonth();
		int getDay();
		void setDay(unsigned short day);
		void setJudianDayNumber(long JDN);
		long getJudianDayNumber();
		bool isEqual(date date0);
		void printDate();
		std::string toString();
		
	private:

		int _year;
		int _month;
		int _day;
		long _judianDayNumber;
		void setJudianDayNumber();
		
	};
}
#endif