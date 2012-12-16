//created by Wang Jianwei on 01 Dec 2012
#ifndef RecordHelper_H
#define RecordHelper_H
#include <string>
#include <fstream>
#include <map>
#include <set>
#include <tuple>
#include "AbstractSession.h"
#include "Enums.h"

namespace Session {
	class RecordHelper: public AbstractSession{
	
	public:
		
		static RecordHelper* getInstance();

		void init(Configuration*);

		typedef std::map<std::string, std::set<long>> HolidayMap;
		
		typedef std::map<std::string, std::map<long, double>> RateMap;
		
		typedef tuple<enums::CurrencyEnum, enums::DayCountEnum, enums::DayCountEnum, enums::DayRollEnum> currencyTuple;

		typedef map<std::string, currencyTuple> currencyMap;
		
		HolidayMap getHolidayMap(){return _holidayMap;}
		void setHolidayMap(HolidayMap map){_holidayMap=map;}

		RateMap getDepositRateMap(){return _depositRateMap;}
		void setDepositRateMap(RateMap map){_depositRateMap=map;}

		RateMap getSwapRateMap(){return _swapRateMap;}
		void setSwapRateMap(RateMap map){_swapRateMap=map;}

		currencyMap getCurrencyMap(){return _currencyMap;}
		void setCurrencyMap(currencyMap map){_currencyMap=map;}

	private:		
		
		RecordHelper();
		~RecordHelper();

		static RecordHelper* single;

		HolidayMap _holidayMap;

		RateMap _depositRateMap;

		RateMap _swapRateMap;
				
		map<std::string, currencyTuple> _currencyMap;
		
		void buildConfiguration(Configuration*);
		void buildHolidayMap(Configuration*);
		void buildSwapRateMap(Configuration*);
		void buildDepositRateMap(Configuration*);
		void buildCurrencyMap(Configuration*);

	};
}

#endif