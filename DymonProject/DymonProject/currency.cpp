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
	enums::DayRollEnum dayRollConvention = std::get<2>(ccyTuple);
	currency::currency(currency, dayCountCashConvention,dayCountSwapConvention,dayRollConvention);
}

currency::currency(enums::CurrencyEnum currencyName,enums::DayCountEnum dayCountCashConvention, enums::DayCountEnum dayCountSwapConvention, enums::DayRollEnum dayRollConvention) {
	_currencyName=currencyName;
	_dayCountCashConvention=dayCountCashConvention;
	_dayCountSwapConvention=dayCountSwapConvention;
	_dayRollConvention=dayRollConvention;
}
currency::~currency(){
}

enums::CurrencyEnum currency::getCurrencyName() {
	return _currencyName;
}

enums::DayCountEnum currency::getDayCountCashConvention() {
	return _dayCountCashConvention;
}

enums::DayCountEnum currency::getDayCountSwapConvention() {
	return _dayCountSwapConvention;
}

enums::DayRollEnum currency::getDayRollConvention() {
	return _dayRollConvention;
}

void currency::setCurrencyName(enums::CurrencyEnum currencyName) {
	_currencyName=currencyName;
}

void currency::setDayCountCashConvention(enums::DayCountEnum dayCountCashConvention) {
	_dayCountCashConvention=dayCountCashConvention;
}

void currency::setDayCountSwapConvention(enums::DayCountEnum dayCountSwapConvention) {
	_dayCountSwapConvention=dayCountSwapConvention;
}

void currency::setDayRollConvention(enums::DayRollEnum dayRollConvention) {
	_dayRollConvention=dayRollConvention;
}