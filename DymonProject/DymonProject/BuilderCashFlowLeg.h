#ifndef BUILDERCASHFLOWLEG_H
#define BUILDERCASHFLOWLEG_H

#include "cashflow.h"
#include "currency.h"
#include "cashflowLeg.h"
#include "Enums.h"
#include "date.h"
#include "dateUtil.h"
#include <vector>
#include <iterator>
#include "RecordHelper.h"

using namespace utilities;
using namespace std;
using namespace enums;
using namespace Session;

namespace instruments {
	class BuilderCashFlowLeg {
		

	public:
		// buildDirection: 1=build from startDate towards maturityDate
		// buildDirection: -1=build from maturityDate towards startDate
		BuilderCashFlowLeg();
		BuilderCashFlowLeg(date startDate, date maturityDate,double couponRate,double notional, int paymentFreq, currency cashFlowLegCurr,bool rollAccuralDates, int buildDirection,RecordHelper::HolidayMap holidayMap);
		BuilderCashFlowLeg(date startDate, int tenorNumOfMonths,double couponRate,double notional, int paymentFreq, currency cashFlowLegCurr,bool rollAccuralDates,RecordHelper::HolidayMap holidayMap);
		
		~BuilderCashFlowLeg();

		
		
	private:
		cashflowLeg _cashflowLeg;
		date _startDate;
		date _maturityDate;
		int _tenorNumOfMonths;
		double _couponRate;
		double _notional;
		int _paymentFreq;
		currency _cashFlowLegCurr;
		bool _rollAccuralDates;
		RecordHelper::HolidayMap _holidayMap;

		////annualized zero rates for coupon dates cashflow points
		//vector<double> _margin;
		//int _paymentFreq;
		//date _maturityDate;
		//currency _cashFlowCurr;
		//double _notional;
		////fixing and payment dates for coupon cashflows only
		//vector<date> _fixingDates;
		//vector<date> _paymentDates;

		//DayCountEnum _cashFlowDayCount;
		//DayRollEnum _cashFlowDayRollEnum;
		//
		////PV and NV for coupon cashflows only
		//vector<double> _PVs;
		//vector<double> _NVs;

		////for fixed leg only, floating leg uses forward rates
		//double _couponRate;
		//date _tradeDate;
		////flags for notional exchanges at start/end of over cashflow streams
		////1=has notional cashflow, 0=no notional cashflow
		//int _exchangeNotionalBegin;
		//int _exchangeNotionalEnd;
		//
		//vector<double> notionalPVs;
		//vector<double> notionalNVs;

		//double MPV();
		//void printPVs();
		//void printNVs();

		//int getPaymentFreq();
		//vector<date> getFixingDates();
		//vector<date> getPaymentDates();
		//double getNotional();
		//date getStartDate();
		//date getMaturityDate();
		//currency getCashFlowCurr();
		//vector<double> getMargin();
		//int getExchangeNotionalBegin();
		//int getExchangeNotionalEnd();
		//vector<double> getNotionalNVs();
		//vector<double> getNotionalPVs();
		//
		//vector<double> getPVs();
		//vector<double> getNVs();

		//void setExchangeNotionalBegin(int exchangeNotionalBegin);
		//void setExchangeNotionalEnd(int exchangeNotionalEnd);
		//void setPVs();
		//void setNVs();
		//void setFixingDates();
		//void setPaymentDates();
		//void setPaymentFreq(int paymentFreq);
		//void setNotional(double notional);
		//void setStartDate(date startDate);
		//void setTradeDate(date tradeDate);
		//void setCouponRate(double couponRate);
		//void setMargin(vector<double> margin);
		//void setMaturityDate(date maturityDate);
		//void setCashFlowCurr(currency cashFlowCurr);
		//void setNotionalNVs();
		//void setNotionalPVs();
		
	};

}



#endif