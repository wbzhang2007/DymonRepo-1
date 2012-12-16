//created by Hu Kun on 29 Nov 2012
#ifndef ABSTRACTINSTRUMENT_H
#define ABSTRACTINSTRUMENT_H
#include "currency.h"
#include "date.h"

using namespace utilities;

namespace instruments {
	class AbstractInstrument {
	
	public:
		//base class for all other instruments to be derived from
		AbstractInstrument(){};
		virtual date getIssueDate() =0;
	    virtual date getMaturityDate()=0;
		virtual void setIssueDate(date tradeDate)=0;
		virtual void setMaturityDate(date maturityDate)=0;

	protected: 
		currency _domCurrency;
		currency _forCurrency;
		date _tradeDate;
		date _maturityDate;

		
	};
}
#endif