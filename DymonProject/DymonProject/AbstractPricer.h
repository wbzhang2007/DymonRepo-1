//created by Hu Kun on 16 Dec 2012
#ifndef ABSTRACTPRICER_H
#define ABSTRACTPRICER_H
#include "currency.h"
#include "date.h"

using namespace std;
using namespace instruments;


namespace models {
	class AbstractPricer {
	
	public:
		//base class for all other instruments to be derived from
		AbstractPricer(){};

		template <class T>
		virtual double getPrice(T,vector<double> yieldCurve)=0;
	    /*virtual date getMaturityDate()=0;
		virtual void setIssueDate(date tradeDate)=0;
		virtual void setMaturityDate(date maturityDate)=0;*/

	protected: 
		/*currency _domCurrency;
		currency _forCurrency;
		date _tradeDate;
		date _maturityDate;*/

		
	};
}
#endif