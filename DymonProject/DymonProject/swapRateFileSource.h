//created by Wang Jianwei on 01 Dec 2012
#ifndef SWAPRATEFILESOURCE_H
#define SWAPRATEFILESOURCE_H
#include <string>
#include <fstream>
#include "AbstractFileSource.h"
#include <set>
#include <vector>

namespace DAO {
	class SwapRateFileSource: public AbstractFileSource{
		
	public:
		SwapRateFileSource();
		SwapRateFileSource(std::string persistDir, std::string fileName);
		~SwapRateFileSource();

		void init(Configuration);
		
		void retrieveRecord();
	};

}
#endif