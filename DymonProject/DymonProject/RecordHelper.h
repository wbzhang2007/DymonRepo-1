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

using namespace utilities;
using namespace enums;

namespace Session {
	class RecordHelper: public AbstractSession{
	
	public:
		
		static RecordHelper* getInstance();

		void init(Configuration*);

		typedef std::map<enums::CurrencyEnum, std::set<long>> HolidayMap;
		
		typedef std::map<enums::CurrencyEnum, std::map<long, double>> RateMap;
		
		typedef std::tuple<enums::DayCountEnum, enums::DayCountEnum, enums::DayRollEnum, enums::DayRollEnum, enums::DayRollEnum, enums::DayRollEnum, int> currencyTuple;

		typedef std::map<enums::CurrencyEnum, currencyTuple> currencyMap;

		//std::map<double,std::map<tuple<double fSwapTenorNumOfMonths,double optionTenorNumOfMonths>,double swaptionVol>> SwaptionVolMap
		typedef std::map<double,std::map<tuple<double ,double >,double >> SwaptionVolMap;
		
		HolidayMap getHolidayMap(){return _holidayMap;}
		void setHolidayMap(HolidayMap map){_holidayMap=map;}

		RateMap getDepositRateMap(){return _depositRateMap;}
		void setDepositRateMap(RateMap map){_depositRateMap=map;}

		RateMap getOverNightRateMap(){return _overNightRateMap;}
		void setOverNightRateMap(RateMap map){_overNightRateMap=map;}

		RateMap getSwapRateMap(){return _swapRateMap;}
		void setSwapRateMap(RateMap map){_swapRateMap=map;}

		currencyMap getCurrencyMap(){return _currencyMap;}
		void setCurrencyMap(currencyMap map){_currencyMap=map;}

		SwaptionVolMap getSwaptionVolMap(){return _swaptionVolMap;}
		void setSwaptionVolMap(SwaptionVolMap map){_swaptionVolMap=map;}

	private:		
		
		RecordHelper();
		~RecordHelper();

		static RecordHelper* single;

		HolidayMap _holidayMap;

		RateMap _depositRateMap;

		RateMap _overNightRateMap;

		RateMap _swapRateMap;
				
		currencyMap _currencyMap;

		SwaptionVolMap _swaptionVolMap;

		
		
		void buildConfiguration(Configuration*);
		void buildHolidayMap(Configuration*);
		void buildSwapRateMap(Configuration*);
		void buildDepositRateMap(Configuration*);
		void buildCurrencyMap(Configuration*);
		void buildSwaptionVolMap(Configuration*);

	};
}

#endif