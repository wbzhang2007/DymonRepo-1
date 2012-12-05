//created by Wang Jianwei on 01 Dec 2012
#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include <string>
#include <fstream>
#include "AbstractFileSource.h"
#include <set>
#include <vector>

namespace DAO {
	class Configuration: public AbstractFileSource{
		
	public:
		Configuration();
		Configuration(std::string persistDir, std::string fileName);
		~Configuration();

		void init();
		
		void retrieveRecord();
	};

}
#endif