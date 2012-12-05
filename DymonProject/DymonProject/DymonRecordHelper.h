//created by Wang Jianwei on 01 Dec 2012
#ifndef DYMONRECORDHELPER_H
#define DYMONRECORDHELPER_H
#include <string>
#include <fstream>
#include <map>
#include <set>
#include "AbstractSession.h"

namespace Session {
	class DymonRecordHelper: public AbstractSession{
	
	public:

		DymonRecordHelper();

		void init();

		static std::map<std::string, std::set<long>> holidayMap;

		static std::map<std::string, std::map<int, double>> depositRateMap;

		static std::map<std::string, std::map<int, double>> swapRateMap;
	
		static std::map<std::string, std::string> configuration;

	private:
		
		void buildHolidayMap();

		void buildConfiguration();
		
		void buildSwapRateMap();
		
		void buildDepositRateMap();

	};
}

#endif