//created by Hu Kun on 30 Nov 2012
//class for zero coup bonds in one currency.

#ifndef ZERO_H
#define ZERO_H
#include "currency.h"
#include "date.h"
#include "instrumentBase.h"
#include <vector>

using namespace utilities;
using namespace std;

namespace instruments {
	class zero: public instrumentBase {

	public:
		zero();
		zero(double spotRate,double notional,date maturityDate, date issueDate);
		~zero();
		double getPrice();
		double getImpliedSpotRate();
		//double getPriceWrapper();
		double getImpliedSpotRateWrapper();

		virtual utilities::date getIssueDate();
	    virtual utilities::date getMaturityDate();
		virtual void setIssueDate(utilities::date issueDate);
		virtual void setMaturityDate(utilities::date maturityDate);

	public:
		double spotRate;
		double notional;
		date maturityDate;
		double price;
		date issueDate;
		date todayDate;


	};

}

#endif