//created by Wang Jianwei on 01 Dec 2012
#ifndef ABSTRACTBOOTSTRAPPER_H
#define ABSTRACTBOOTSTRAPPER_H
#include "AbstractSession.h"
#include "AbstractCurve.h"
#include "AbstractInterpolator.h"
#include "AbstractNumerical.h"
#include <vector>

using namespace Session;

namespace utilities{
	class AbstractBootStrapper{
	public:
		typedef tuple<date, double> point;

		AbstractBootStrapper(point startPoint, date endDate, AbstractInterpolator::interpolAlgo interpolAlgo,
		AbstractNumerical::NumericAlgo numericAlgo){
			_startPoint = startPoint;
			_endDate = endDate;
			_interpolAlgo = interpolAlgo;
			_numericAlgo = numericAlgo;
		}

		virtual AbstractInterpolator* bootStrap();

		virtual double numericalFunc(double x);

	protected:
	
		point _startPoint;

		date _endDate;

		AbstractInterpolator::interpolAlgo _interpolAlgo;

		AbstractNumerical::NumericAlgo _numericAlgo; 
	
	};
}
#endif