//created by Hu Kun on 29 Nov 2012

#ifndef CURRENCY_H
#define CURRENCY_H
#include <tuple>


namespace instruments {
	
	
	class currency {
	enum currency_t {EUR,USD,THB,KRW,SGD,JPY};
	enum dayCount_t {thirty_360,ACT_360,ACT_365,ACT_ACT};
	enum dayRoll_t {Following,Preceding,Mfollowing,Mfollowingbi,EOM};

	public:
		currency(currency_t currencyName,dayCount_t dayCountCashConvention, dayCount_t dayCountSwapConvention, dayRoll_t dayRollConvention, int paymentFreq, int compoundFreq);
		~currency() {};

	private:
		currency_t currencyName;
		dayCount_t dayCountCashConvention;
		dayCount_t dayCountSwapConvention;
		dayRoll_t dayRollConvention;
		int paymentFreq;
		int compoundFreq;
	};

}
#endif