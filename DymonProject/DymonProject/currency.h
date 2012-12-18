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
		~currency(){};

		enums::CurrencyEnum getCurrencyName(){return _marketName;}
		enums::DayCountEnum getDayCountCashConvention(){return _dayCountCashConvention;}
		enums::DayCountEnum getDayCountSwapConvention(){return _dayCountSwapConvention;}
		enums::DayRollEnum getDayRollCashConvention(){return _dayRollCashConvention;}
		enums::DayRollEnum getDayRollSwapConvention(){return _dayRollSwapConvention;}
		enums::DayRollEnum getAccrualAdjustCashConvention(){return _accrualAdjustCashConvention;}
		enums::DayRollEnum getAccrualAdjustSwapConvention(){return _accrualAdjustSwapConvention;}

		void setCurrencyName(enums::CurrencyEnum marketName){_marketName = marketName;}
		void setDayCountCashConvention(enums::DayCountEnum dayCountCashConvention){_dayCountCashConvention = dayCountCashConvention;}
		void setDayCountSwapConvention(enums::DayCountEnum dayCountSwapConvention){_dayCountSwapConvention = dayCountSwapConvention;}
		void setDayRollCashConvention(enums::DayRollEnum dayRollCashConvention){_dayRollCashConvention = dayRollCashConvention;}
		void setDayRollSwapConvention(enums::DayRollEnum dayRollSwapConvention){_dayRollSwapConvention = dayRollSwapConvention;}
		void setAccrualAdjustCashConvention(enums::DayRollEnum accrualAdjustCashConvention){_accrualAdjustCashConvention = accrualAdjustCashConvention;}
		void setAccrualAdjustSwapConvention(enums::DayRollEnum accrualAdjustSwapConvention){_accrualAdjustSwapConvention = accrualAdjustSwapConvention;}
		
	private:
		enums::CurrencyEnum _marketName;
		enums::DayCountEnum _dayCountCashConvention;
		enums::DayCountEnum _dayCountSwapConvention;
		enums::DayRollEnum _dayRollCashConvention;
		enums::DayRollEnum _dayRollSwapConvention;
		enums::DayRollEnum _accrualAdjustCashConvention;
		enums::DayRollEnum _accrualAdjustSwapConvention;
	};

}
#endif