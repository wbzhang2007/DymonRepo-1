//created by Wang Jianwei on 01 Dec 2012
#ifndef HOLIDAYFILESOURCE_H
#define HOLIDAYFILESOURCE_H
#include <string>
#include <fstream>
#include "AbstractFileSource.h"
#include <set>
#include <vector>

namespace DAO {
	class HolidayFileSource: public AbstractFileSource{
		
	public:
		HolidayFileSource();
		HolidayFileSource(std::string persistDir, std::string fileName, long fileSize);
		~HolidayFileSource();

		void init();
		
		void retrieveRecord();
		
	private:
		std::set<long> buildJDNSet(std::vector<std::string>);
	};

}
#endif