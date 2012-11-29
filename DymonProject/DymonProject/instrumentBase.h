//created by Hu Kun on 29 Nov 2012

#include "currency.h"
#include "date.h"
#include <vector>	
#include <iostream>

using namespace utilities;
using namespace instruments;

namespace instruments {
	class instrumentBase {
	
	public:
		instrumentBase(currency domCurrency, currency forCurrency,date issueDate, date maturityDate);
		~instrumentBase();

		protected currency domCurrency;
		protected currency forCurrency;
		protected date issueDate;
		protected date maturityDate;
	};
}