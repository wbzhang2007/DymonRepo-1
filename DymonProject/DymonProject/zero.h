//created by Hu Kun on 30 Nov 2012
//class for zero coup bonds in one currency.
//

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
		zero(double spotRate,double notional,date maturityDate);
		~zero();
		double getPrice(double spotRate,double notional,date maturityDate);
		double getImpliedSpotRate(double price,double notional,date maturityDate);

	private:
		double spotRate;
		double notional;
		date maturityDate;
		double price;



	};

}

#endif