//created by Wang Jianwei on 01 Dec 2012
#ifndef CURRENCYFILESOURCE_H
#define CURRENCYFILESOURCE_H
#include <string>
#include <fstream>
#include "AbstractFileSource.h"
#include <set>
#include <tuple>

using namespace enums;

namespace DAO {
	class CurrencyFileSource: public AbstractFileSource{
		
	public:
		
		CurrencyFileSource();
		CurrencyFileSource(std::string persistDir, std::string fileName);
		~CurrencyFileSource();

		void init(Configuration*);
		
		void retrieveRecord();
	};
}
#endif