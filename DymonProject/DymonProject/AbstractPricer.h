//created by Hu Kun on 16 Dec 2012
#ifndef ABSTRACTPRICER_H
#define ABSTRACTPRICER_H
#include "currency.h"
#include "date.h"
#include <vector>
#include <tuple>
#include <map>

using namespace std;
using namespace instruments;


namespace models {
	//tuple<tenorNumofMonths,zeroRates>
	typedef tuple<double,double> yieldCurvePoint;
	typedef tuple<double,double> PV;

	//map<tuple<tenorNumofMonths,delta>, volatility>
	typedef map<tuple<double,double>,double> volSurfacePoint;
	
	class AbstractPricer {
	
	public:
		//base class for all other instruments to be derived from
		AbstractPricer(){};
		~AbstractPricer(){};
		
		
		template <class T, typename P> double getMPV(T aInstrument,vector<P> curve);
		
		
		template <class T, typename P> vector<PV> getPVLeg(T aInstrument,vector<P> curve);
		

	protected: 

		
	};
}
#endif