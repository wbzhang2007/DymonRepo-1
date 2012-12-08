//created by Hu Kun on 29 Nov 2012

#ifndef CURRENCY_H
#define CURRENCY_H
#include <tuple>
#include "dateUtil.h"
#include "Enums.h"

namespace instruments {

	class currency {

	public:
		currency();
		currency(enums::CurrencyEnum currencyName,enums::DayRollEnum dayCountCashConvention, enums::DayCountEnum dayCountSwapConvention, enums::DayRollEnum dayRollConvention, int paymentFreq, int compoundFreq);
		~currency();
		int getPaymentFreq();
		int getCompoundFreq();
		void setPaymentFreq(int paymentFreq);
		void setCompoundFreq(int compoundFreq);

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
		int _paymentFreq;
		int _compoundFreq;
	};

}
#endif