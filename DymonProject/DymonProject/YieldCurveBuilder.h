//created by Wang Jianwei on 01 Dec 2012
//Added cashflowleg creating - Kun
#ifndef YIELDCURVEBUILDER_H
#define YIELDCURVEBUILDER_H
#include "AbstractCurve.h"
#include "YieldCurve.h"
#include "AbstractBuilder.h"
#include "cashflow.h"
#include "cashflowLeg.h"
#include <vector>

using namespace instruments;

namespace utilities{
	class YieldCurveBuilder: public AbstractBuilder{
		
	public:
		
		YieldCurveBuilder(cashflowLeg cashflowLeg):AbstractBuilder(){
			_cashflowLeg = cashflowLeg;
		}

		virtual void init(Configuration* cfg);

		YieldCurve* buildCurve();

	private:

		cashflowLeg _cashflowLeg;
	};
}
#endif