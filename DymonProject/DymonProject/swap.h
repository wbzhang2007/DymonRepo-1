//created by Hu Kun on 30 Nov 2012
//class for standard IRS with fix to floating legs in one currency.
//rates for fixed and floating in private data members are all in terms of annual rates

#ifndef SWAP_H
#define SWAP_H
#include "currency.h"
#include "date.h"
#include "instrumentBase.h"
#include <vector>

using namespace utilities;
using namespace std;

namespace instruments {
	class swap: public instrumentBase {
	public:
		swap(double fixLegRate, double floatLegSpread, double floatLegBenchMark);
	protected:

	private:
		double fixLegRate;
		double floatLegSpread;
		double floatLegBenchMark;
		double notional;
		date issueDate;
		date maturityDate;
		//swapCurr inclusive of dayCount, dayRoll, payment freq and compound freq
		currency swapCurr;

		vector<date> fixingDate;
		vector<date> accuralBeginDate;
		vector<date> paymentDate;

		double parRate;
		vector<zero> zeroStrips;




	};

}
#endif