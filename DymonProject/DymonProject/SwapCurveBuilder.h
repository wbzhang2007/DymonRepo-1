//created by Wang Jianwei on 01 Dec 2012
//Added cashflowleg creating - Kun
#ifndef SwapCurveBuilder_H
#define SwapCurveBuilder_H
#include "AbstractCurve.h"
#include "DiscountCurve.h"
#include "AbstractBuilder.h"
#include "cashflow.h"
#include "cashflowLeg.h"
#include <vector>

using namespace instruments;
typedef tuple<date, double> point;

namespace utilities{
	class SwapCurveBuilder: public AbstractBuilder{
		
	public:
		
		SwapCurveBuilder():AbstractBuilder(){}

		void init(Configuration* cfg);

		DiscountCurve* build(Configuration* cfg);

		void buildDepositSection(DiscountCurve* yc);

		void buildSwapSection(DiscountCurve* yc);
		
		void buildOvernightSection(DiscountCurve* yc);

		Market getMarket(){return _market;}
		void setMarket(Market market){_market = market;}

		enums::interpolAlgo getInterpolAlgo(){return _interpolAlgo;}
		void setInterpolAlgo(enums::interpolAlgo interpolAlgo){_interpolAlgo=interpolAlgo;}

		enums::NumericAlgo getNumericalAlgo(){return _numericalAlgo;}
		void setNumericalAlgo(enums::NumericAlgo numericalAlgo){_numericalAlgo=numericalAlgo;}

		int getFloatFrequency(){return _floatFreqency;}
		void setFloatFrequency(int floatFreqency){_floatFreqency=floatFreqency;}

		int getFixFreqency(){return _fixFreqency;}
		void setFixFreqency(int fixFreqency){_fixFreqency=fixFreqency;}

		int getTimeLineBuildDirectiony(){return _timeLineBuildDirection;}
		void setTimeLineBuildDirection(int timeLineBuildDirection){_timeLineBuildDirection=timeLineBuildDirection;}

		int getBizDaysAfterSpot(){return _bizDaysAfterSpot;}
		void setBizDaysAfterSpot(int bizDaysAfterSpot){_bizDaysAfterSpot=bizDaysAfterSpot;}

		bool getRollAccuralDates(){return _rollAccuralDates;}
		void setRollAccuralDates(bool rollAccuralDates){_rollAccuralDates = rollAccuralDates;}

		double getBizDaysAfterSpotDF(){return _bizDaysAfterSpotDF;}
		void setBizDaysAfterSpotDF(double bizDaysAfterSpotDF){_bizDaysAfterSpotDF = bizDaysAfterSpotDF;}

	private:

		Market _market;
		int _floatFreqency;
		int _fixFreqency;
		int _timeLineBuildDirection;
		bool _rollAccuralDates;
		enums::interpolAlgo _interpolAlgo;
		enums::NumericAlgo _numericalAlgo;
		int _bizDaysAfterSpot;
		double _bizDaysAfterSpotDF;
		point _curvePointer;
		date _curveStartDate;
	};
}
#endif