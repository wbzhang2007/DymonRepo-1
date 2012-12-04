//created by Hu Kun on 30 Nov 2012
//class for standard IRS with fix to floating legs in one currency.
//rates for fixed and floating in private data members are all in terms of annual rates

#ifndef SWAP_H
#define SWAP_H
#include "currency.h"
#include "date.h"
#include "instrumentBase.h"
#include <vector>
#include "zero.h"

using namespace utilities;
using namespace std;
using namespace enums;

namespace instruments {
	class swap: public instrumentBase {
	public:
		
		swap(double fixLegRate, double floatLegSpread, double floatLegBenchMark,date issueDate, date maturityDate, currency fixLegCurr, currency floatLegCurr);
		~swap();

		double getParRate();


	protected:

	private:
		double fixLegRate;
		double floatLegSpread;
		double floatLegBenchMark; //example: Libor floating rate
		double notional;
		date issueDate;
		date maturityDate;
		//swapCurr inclusive of dayCount, dayRoll, payment freq and compound freq
		//annually=1, semi-annual=2, quarterly=4; monthly=12;
		currency fixLegCurr;
		currency floatLegCurr;

		double swapValue;

		//fixing dates should follow float leg payment frequencies.
		vector<date> fixingDate;
		vector<date> accuralBeginDate;
		vector<date> fixLegPaymentDate;
		vector<date> floatLegPaymentDate;

		double parRate;
		vector<zero> zeroStrips;




	};

}
#endif