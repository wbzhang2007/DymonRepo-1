//created by Hu Kun on 30 Nov
//updated by Hu Kun on 5 Dec

#include "currency.h"
#include "Enums.h"
#include "EnumHelper.h"
#include "RecordHelper.h"

using namespace instruments;
using namespace utilities;
using namespace Session;

currency::currency(enums::CurrencyEnum currency) {
	RecordHelper::currencyMap ccyMap = RecordHelper::getInstance()->getCurrencyMap();
	RecordHelper::currencyTuple ccyTuple =  ccyMap[currency];
	enums::DayCountEnum dayCountCashConvention = std::get<0>(ccyTuple);
	enums::DayCountEnum dayCountSwapConvention = std::get<1>(ccyTuple);
	enums::DayRollEnum dayRollCashConvention = std::get<2>(ccyTuple);
	enums::DayRollEnum dayRollSwapConvention = std::get<3>(ccyTuple);
	enums::DayRollEnum cashAccrualAdjust = std::get<4>(ccyTuple);
	enums::DayRollEnum swapAccrualAdjust = std::get<5>(ccyTuple);	
}