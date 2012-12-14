//created by Wang Jianwei on 01 Dec 2012
#ifndef CURVEBUILDER_H
#define CURVEBUILDER_H
#include "AbstractCurve.h"
#include "cashflow.h"
#include <vector>

namespace utilities{
	class CurveBuilder{
		
	public:
		
		CurveBuilder(vector<cashflow> cashflows){}

		AbstractCurve buildCurve();

	private:

		vector<cashflow> _cashflows;
	};
}
#endif