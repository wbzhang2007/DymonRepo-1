//created by Hu Kun on 30 Nov 2012
//class for FX spots
//direct quote convention:
//EUR/USD==> EUR=domCurrency, USD=forCurrency

#ifndef SPOT_H
#define SPOT_H
#include "currency.h"
#include "date.h"
#include "instrumentBase.h"
using namespace utilities;

namespace instruments {
	class spot: public instrumentBase {
	public:
		spot(currency domCurr, currency forCurr, date tradeD, date settleD);
		~spot();

		double getPrice();
		void print();
		void setPrice(double aPrice);
		double getInversePrice();

	private:
		currency domCurrency;
		currency forCurrency;
		date tradeDate;
		date settleDate;
		double price;
		
	};

}
#endif