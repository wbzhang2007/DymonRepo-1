//created by Hu Kun on 30 Nov
//updated by Hu Kun on 5 Dec

#include "currency.h"
#include "Enums.h"
#include "EnumHelper.h"
#include "RecordHelper.h"

using namespace instruments;
using namespace utilities;
using namespace Session;

currency::currency(enums::CurrencyEnum market) {
	RecordHelper::currencyMap ccyMap = RecordHelper::getInstance()->getCurrencyMap();
	RecordHelper::currencyTuple ccyTuple =  ccyMap[market];
	setDayCountCashConvention(std::get<0>(ccyTuple));
	setDayCountSwapConvention(std::get<1>(ccyTuple));
	setDayRollCashConvention(std::get<2>(ccyTuple));
	setDayRollSwapConvention(std::get<3>(ccyTuple));
	setAccrualAdjustCashConvention(std::get<4>(ccyTuple));
	setAccrualAdjustSwapConvention(std::get<5>(ccyTuple));	
}