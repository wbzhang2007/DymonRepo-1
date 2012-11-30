//created by Hu Kun on 29 Nov 2012
#ifndef MARKETDATA_H
#define MARKETDATA_H
#include "currency.h"
#include "date.h"
#include "instrumentBase.h"
#include "instrumentValue.h"
#include "numerical.h"
#include <map>
#include <utility>
#include <tuple>

using namespace utilities;
using namespace instruments;
using namespace std;

namespace markets {

	// Singlton class for marketdata
	class marketdata {
	public:
		static marketdata* getInstance();
		double getPrice();
		void setPrice(double aPrice);

		template <class T>
		vector<double> getYieldCurve(vector<T> inputPoints, date startTenor, date endTenor, algo interpolationAlgo);
		
		template <class T>
		map<double,vector<T>> getVolSurface(double underlyingPrice, vector<double> delta, date tradeDate, vector<date> maturity);
		
		template <class T>
		map<double,vector<T>> swaptionVolSurface(double underlyingPrice, vector<double> delta, date tradeDate, vector<date> swapMaturity, vector<date> optionMaturity);

		template <class T>
		vector<double> getBondCurve(vector<T> inputPoints, date startTenor, date endTenor, algo interpolationAlgo);

		template <class T>
		vector<double> getFxForwardCurve(vector<T> inputPoints, date startTenor, date endTenor, algo interpolationAlgo);

		template <class T>
		vector<double> getImpliedYieldCurve(vector<T> inputPoints, date startTenor, date endTenor, algo interpolationAlgo);

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