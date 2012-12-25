//created by Jianwei on 30 Nov 2012
#ifndef ABSTRACTOPTION_H
#define ABSTRACTOPTION_H
#include "AbstractInstrument.h"
#include "OptionPricer.h"
#include "Enums.h"

using namespace utilities;
using namespace instruments;

namespace instruments {
	class AbstractOption:  public OptionPricer, public AbstractInstrument{

	public:

		AbstractOption(){};
		~AbstractOption(){};
		AbstractOption(date tradeDate, CallPut callPutFlag, double S, double K, double vol, double r, double T){
			setTradeDate(tradeDate);
			_callPutFlag = callPutFlag;
			_S = S;
			_K = K;
			_vol = vol;
			_r = r;
			_T = T;
		}

		virtual double getMPV(){return OptionPricer::getMPV();};

	protected:
		CallPut _callPutFlag;
		double _S;
		double _K;
		double _vol;
		double _r;
		double _T;
	};
}
#endif