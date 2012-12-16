//created by Wang Jianwei on 01 Dec 2012
#ifndef ENUMHELPER_H
#define ENUMHELPER_H
#include <vector>
#include "Enums.h"
#include <string>

using namespace enums;
using namespace std;

namespace utilities{
	class EnumHelper{

	public:
		
		static enums::CurrencyEnum getCcyEnum(std::string ccyName);

		static enums::DayRollEnum getDayRollEnum(std::string dayRoll);

		static enums::DayCountEnum getDayCountEnum(std::string dayCount);
	};
}
#endif