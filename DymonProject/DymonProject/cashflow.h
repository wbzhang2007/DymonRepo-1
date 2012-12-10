//created by Hu Kun on 8 Dec
//modified by Hu Kun on 10 Dec

#ifndef CASHFLOW_H
#define CASHFLOW_H

#include "currency.h"
#include "Enums.h"
#include "date.h"
#include "dateUtil.h"
#include <vector>
#include <iterator>

using namespace utilities;
using namespace std;
using namespace enums;

namespace instruments {
	class cashflow {
		

	public:
		cashflow(date startDate, date tradeDate,double couponRate,double notional, vector<double> margin, int paymentFreq, date maturityDate, currency cashFlowCurr);
		~cashflow();

		double MPV();
		void printPVs();

		int getPaymentFreq();
		vector<date> getFixingDates();
		vector<date> getPaymentDates();
		double getNotional();
		date getStartDate();
		date getMaturityDate();
		currency getCashFlowCurr();
		vector<double> getMargin();
		
		vector<double> getPVs();

		void setPVs();
		void setFixingDates();
		void setPaymentDates();
		void setPaymentFreq(int paymentFreq);
		void setNotional(double notional);
		void setStartDate(date startDate);
		void setTradeDate(date tradeDate);
		void setCouponRate(double couponRate);
		void setMargin(vector<double> margin);
		void setMaturityDate(date maturityDate);
		void setCashFlowCurr(currency cashFlowCurr);

	private:
		date _startDate;
		vector<double> _margin;
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