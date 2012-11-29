//created by Hu Kun on 29 Nov 2012
#ifndef MARKETDATA_H
#define MARKETDATA_H
#include "currency.h"
#include "date.h"
#include "instrumentBase.h"
#include "instrumentValue.h"
#include <map>
#include <utility>

using namespace utilities;
using namespace instruments;

namespace markets {

	// Singlton class for marketdata
	class marketdata {
	public:
		static marketdata* getInstance();
		double getPrice();
		void setPrice(double aPrice);
		vector<double> getIrCurve();
		map<vector<double>,vector<date>> getVolSurface(double underlyingPrice, vector<double> delta, date tradeDate, vector<date> maturity);


	protected:
		//private copy constructor
		marketdata();
		~marketdata();
		
	private:
		static bool instanceFlag;
		static marketdata *single;
		double price;
		
	};
}
#endif