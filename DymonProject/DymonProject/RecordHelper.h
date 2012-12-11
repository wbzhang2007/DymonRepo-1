//created by Wang Jianwei on 01 Dec 2012
#ifndef RecordHelper_H
#define RecordHelper_H
#include <string>
#include <fstream>
#include <map>
#include <set>
#include "AbstractSession.h"

namespace Session {
	class RecordHelper: public AbstractSession{
	
	public:
		
		static RecordHelper* getInstance();

		void init(Configuration*);

		typedef std::map<std::string, std::set<long>> HolidayMap;
		
		typedef std::map<std::string, std::map<int, double>> RateMap;

		HolidayMap getHolidayMap(){return _holidayMap;}
		void setHolidayMap(HolidayMap map){_holidayMap=map;}

		RateMap getDepositRateMap(){return _depositRateMap;}
		void setDepositRateMap(RateMap map){_depositRateMap=map;}

		RateMap getSwapRateMap(){return _swapRateMap;}
		void setSwapRateMap(RateMap map){_swapRateMap=map;}

	private:		
		
		RecordHelper();
		~RecordHelper();

		static RecordHelper* single;

		HolidayMap _holidayMap;

		RateMap _depositRateMap;

		RateMap _swapRateMap;
		
		void buildConfiguration(Configuration*);
		void buildHolidayMap(Configuration*);
		void buildSwapRateMap(Configuration*);
		void buildDepositRateMap(Configuration*);

	};
}

#endif