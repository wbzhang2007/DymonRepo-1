//created by Hu Kun on 29 Nov 2012
#ifndef INSTRUMENTBASE_H
#define INSTRUMENTBASE_H
#include "currency.h"
#include "date.h"


namespace instruments {
	class instrumentBase {
	
	public:
		instrumentBase(instruments::currency domCurrency, instruments::currency forCurrency, utilities::date issueDate, utilities::date maturityDate);
		~instrumentBase();

		//base class for all other instruments to be derived from
		virtual utilities::date getIssueDate();
	    virtual utilities::date getMaturityDate();
		virtual void setIssueDate(utilities::date issueDate);
		virtual void setMaturityDate(utilities::date maturityDate);

	protected: 
		instruments::currency domCurrency;
		instruments::currency forCurrency;
		utilities::date issueDate;
		utilities::date maturityDate;

		
	};
}
#endif