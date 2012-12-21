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
		cashflow(){};
		cashflow(double couponRate,double notional,  date fixingDate, date paymentDate,date accuralStartDate, date accuralEndDate, currency cashFlowCurr);

		~cashflow(){};

		double getCouponAmount();
		double getCouponRate();
		double getNotional();
		date getFixingDate();
		date getPaymentDate();
		date getAccuralStartDate();
		date getAccuralEndDate();
		currency getCashFlowCurr();
		double getAccuralFactor();

		void setCouponAmount();
		void setNotional(double notional);
		void setCouponRate(double couponRate);
		void setFixingDate(date fixingDate);
		void setPaymentDate(date paymentDate);
		void setAccuralStartDate(date accuralStartDate);
		void setAccuralEndDate(date accuralEndDate);
		void setCashFlowCurr(currency cashFlowCurr);
		void setAccuralFactor();

		bool isDateEqual(cashflow cf);
		void printCashFlow();
		
	private:
		double _couponRate;
		double _notional;
		double _couponAmount;

		date _fixingDate;
		date _paymentDate; 
		date _accuralStartDate;
		date _accuralEndDate;
		
		currency _cashFlowCurr;
		double _accuralFactor;
	};
}
#endif