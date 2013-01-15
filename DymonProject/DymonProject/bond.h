//created by Jianwei on 30 Nov 2012
#ifndef BOND_H
#define BOND_H
#include "AbstractInstrument.h"
#include "Enums.h"
#include "Market.h"
#include "BondCurve.h"
#include "BondPricer.h"
#include "Configuration.h"

using namespace utilities;
using namespace instruments;

namespace instruments {
	class  Bond:  public BondPricer, public AbstractInstrument{

	public:

		Bond(){};
		~Bond(){};
		Bond(Market market, date tradeDate, date maturityDate, double notional, double couponRate, BondCurve* yc, int couponFreq, bool rollAccuralDates, int buildDirection);
		Bond(Market market, date tradeDate, int tenorNumOfMonths, double notional, double couponRate, BondCurve* yc, int couponFreq, bool rollAccuralDates);
		Bond(Market market, date tradeDate, date maturityDate, double couponRate, int couponFreq, Configuration* cfg, double cleanPrice);

		cashflowLeg* getCouponLeg(){return _couponLeg;}
		BondCurve* getBondCurve(){return _bc;}
		double getCouponRate(){return _couponRate;}
		int getCouponFreq(){return _couponFreq;}
		int getTenor(){ return _tenorNumOfMonths;}
		double getDirtyPrice(){return _dirtyPrice;}
		double getCleanPrice(){return _cleanPrice;}

		void printCouponLeg();

	private:

		void BaseBond(Market market, date tradeDate, date maturityDate, double notional, double couponRate, int couponFreq, bool rollAccuralDates, int buildDirection);
		double deriveDirtyPrice();

		cashflowLeg* _couponLeg;
		BondCurve* _bc;
		Market _market;
		double _couponRate;
		int _couponFreq;
		int _tenorNumOfMonths;
		double _dirtyPrice;
		double _cleanPrice;
	};

}
#endif