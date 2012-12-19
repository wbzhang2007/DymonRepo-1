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
typedef tuple<date, double> point;

namespace utilities{
	class YieldCurveBuilder: public AbstractBuilder{
		
	public:
		
		YieldCurveBuilder():AbstractBuilder(){}

		void init(Configuration* cfg);

		YieldCurve* build();

		void buildDepositSection(YieldCurve* yc);

		void buildSwapSection(YieldCurve* yc);
		
		void buildOvernightSection(YieldCurve* yc);

	private:

		currency _market;
		int _floatFreqency;
		int _fixFreqency;
		int _timeLineBuildDirection;
		bool _rollAccuralDates;
		enums::interpolAlgo _interpolAlgo;
		enums::NumericAlgo _numericalAlgo;
		int _bizDaysAfterSpot;
		double _bizDaysAfterSpotRate;
		point _curvePointer;
	};
}
#endif