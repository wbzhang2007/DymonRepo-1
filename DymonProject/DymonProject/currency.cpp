//created by Hu Kun on 30 Nov
//updated by Hu Kun on 5 Dec

#include "currency.h"
#include "Enums.h"

using namespace instruments;

currency::currency() {
}

currency::currency(enums::CurrencyEnum currencyName,enums::DayCountEnum dayCountCashConvention, enums::DayCountEnum dayCountSwapConvention, enums::DayRollEnum dayRollConvention, int paymentFreq, int compoundFreq) {
	_currencyName=currencyName;
	_dayCountCashConvention=dayCountCashConvention;
	_dayCountSwapConvention=dayCountSwapConvention;
	_dayRollConvention=dayRollConvention;
	_paymentFreq=paymentFreq;
	_compoundFreq=compoundFreq;
}
currency::~currency(){
}

int currency::getPaymentFreq() {
	return _paymentFreq;
}

int currency::getCompoundFreq() {
	return _compoundFreq;
}

void currency::setPaymentFreq(int paymentFreq) {
	_paymentFreq=paymentFreq;
}

void currency::setCompoundFreq(int compoundFreq) {
	_compoundFreq=compoundFreq;
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