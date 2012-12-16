//created by Hu Kun on 29 Nov 2012

#ifndef CURRENCY_H
#define CURRENCY_H
#include <tuple>
#include "dateUtil.h"
#include "Enums.h"

namespace instruments {

	class currency {

	public:
		currency(){};
		currency(enums::CurrencyEnum);
		currency(enums::CurrencyEnum currencyName,enums::DayCountEnum dayCountCashConvention, enums::DayCountEnum dayCountSwapConvention, enums::DayRollEnum dayRollConvention);
		~currency();

		enums::CurrencyEnum getCurrencyName();
		enums::DayCountEnum getDayCountCashConvention();
		enums::DayCountEnum getDayCountSwapConvention();
		enums::DayRollEnum getDayRollConvention();

		void setCurrencyName(enums::CurrencyEnum currencyName);
		void setDayCountCashConvention(enums::DayCountEnum dayCountCashConvention);
		void setDayCountSwapConvention(enums::DayCountEnum dayCountSwapConvention);
		void setDayRollConvention(enums::DayRollEnum dayRollConvention);
		
	private:
		enums::CurrencyEnum _currencyName;
		enums::DayCountEnum _dayCountCashConvention;
		enums::DayCountEnum _dayCountSwapConvention;
		enums::DayRollEnum _dayRollConvention;
	};

}
#endif