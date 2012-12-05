//created by Wang Jianwei on 01 Dec 2012
#ifndef DEPOSITFILESOURCE_H
#define DEPOSITFILESOURCE_H
#include <string>
#include <fstream>
#include "AbstractFileSource.h"
#include <set>
#include <vector>

namespace DAO {
	class DepositFileSource: public AbstractFileSource{
		
	public:
		DepositFileSource();
		DepositFileSource(std::string persistDir, std::string fileName);
		~DepositFileSource();

		void init(std::map<std::string, std::string>);
		
		void retrieveRecord();
	};

}
#endif