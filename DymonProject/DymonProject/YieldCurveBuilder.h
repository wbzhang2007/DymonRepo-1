//created by Wang Jianwei on 01 Dec 2012
#ifndef YIELDCURVEBUILDER_H
#define YIELDCURVEBUILDER_H
#include "AbstractCurve.h"
#include "YieldCurve.h"
#include "AbstractBuilder.h"
#include "cashflow.h"
#include <vector>

using namespace instruments;

namespace utilities{
	class YieldCurveBuilder: public AbstractBuilder{
		
	public:
		
		YieldCurveBuilder(vector<cashflow> cashflows):AbstractBuilder(){
			_cashflows = cashflows;
		}

		virtual void init(Configuration* cfg);

		YieldCurve* buildCurve();

	private:

		vector<cashflow> _cashflows;
	};
}
#endif