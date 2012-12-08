#ifndef CASHFLOW_H
#define CASHFLOW_H

#include "currency.h"
#include "CurrencyEnum.h"
#include "date.h"
#include "dateUtil.h"
#include <vector>
#include <iterator>

using namespace utilities;
using namespace std;
using namespace enums;

namespace instruments {
	class cashflow {
		cashflow(date startDate, date tradeDate,double couponRate,double notional, double margin, int paymentFreq, date maturityDate, currency cashFlowCurr);
		~cashflow();

	public:
		double MPV();
		int getPaymentFreq();
		vector<date> getFixingDates();
		vector<date> getPaymentDates();
		double getNotional();
		date getStartDate();
		date getMaturityDate();
		currency getCashFlowCurr();
		double getMargin();
		vector<double> getPVs();
		void printPVs();

	private:
		date _startDate;
		double _margin;
		int _paymentFreq;
		date _maturityDate;
		currency _cashFlowCurr;
		double _notional;
		vector<date> _fixingDates;
		vector<date> _paymentDates;
		DayCountEnum _cashFlowDayCount;
		DayRollEnum _cashFlowDayRollEnum;
		vector<double> _PVs;
		double _couponRate;
		date _tradeDate;
	};

}



#endif