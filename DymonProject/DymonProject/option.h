//created by Hu Kun on 30 Nov 2012

#ifndef OPTION_H
#define OPTION_H
#include "currency.h"
#include "date.h"
#include "AbstractInstrument.h"
#include <vector>
#include "zero.h"
#include <tuple>
#include <iterator>
#include "RecordHelper.h"
#include "DiscountCurve.h"
#include "AbstractInstrument.h"
#include "VolSurface.h"
#include "OptionPricer.h"

using namespace utilities;
using namespace std;
using namespace enums;
using namespace instruments;


namespace instruments {
	class option: public AbstractInstrument, public OptionPricer {

	public:
		option(date tradeDate, date maturityDate, VolSurface* vs, double S);
		~option();

		double getPrice();
	
	private:

	
	

	
	};
}



#endif