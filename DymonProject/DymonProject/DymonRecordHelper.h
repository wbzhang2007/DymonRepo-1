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

		void start();

		void stop();

		static std::map<std::string, std::set<long>> holidayMap;
	
	private:
		
		void buildHolidayMap();
	};
}

#endif