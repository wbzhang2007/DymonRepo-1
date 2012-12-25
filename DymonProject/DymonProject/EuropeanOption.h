//created by Jianwei on 30 Nov 2012
#ifndef EUROPEANOPTION_H
#define EUROPEANOPTION_H
#include "OptionPricer.h"
#include "AbstractInstrument.h"
#include "AbstractOption.h"

using namespace instruments;
typedef AbstractOption super;

namespace instruments {
	class EuropeanOption:  public AbstractOption{
	public:
		EuropeanOption():AbstractOption(){};
		~EuropeanOption(){};
		EuropeanOption(date tradeDate, CallPut callPutFlag, double S, double K, double vol, double r, double T):
		AbstractOption(tradeDate, callPutFlag, S, K, vol, r, T){}

		virtual double getMPV();
	};
}
#endif