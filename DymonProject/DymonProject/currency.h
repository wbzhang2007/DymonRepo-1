//created by Hu Kun on 29 Nov 2012

#ifndef CURRENCY_H
#define CURRENCY_H
#include <tuple>
#include "DayCountEnum.h"
#include "DayRollEnum.h"
#include "CurrencyEnum.h"

namespace instruments {


	class currency {

	public:
		currency();
		currency(enums::CurrencyEnum currencyName,enums::DayRollEnum dayCountCashConvention, enums::DayCountEnum dayCountSwapConvention, enums::DayRollEnum dayRollConvention, int paymentFreq, int compoundFreq);
		~currency();

	private:
		enums::CurrencyEnum currencyName;
		enums::DayCountEnum dayCountCashConvention;
		enums::DayCountEnum dayCountSwapConvention;
		enums::DayRollEnum dayRollConvention;
		int paymentFreq;
		int compoundFreq;
	};

}
#endif