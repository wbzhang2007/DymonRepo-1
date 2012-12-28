//created by Wang Jianwei on 01 Dec 2012
#ifndef LINEARINTERPOLATOR_H
#define LINEARINTERPOLATOR_H
#include "AbstractInterpolator.h"
#define NaN -999999

namespace utilities{
	template<typename T> class LinearInterpolator: public AbstractInterpolator<T>{

	public:

		typedef tuple<T, double> point;

		LinearInterpolator(point startPoint, point endPoint):AbstractInterpolator(startPoint, endPoint){
			_slope = NaN;
			_algo = enums::LINEAR;
		}

		virtual point interpolate(T xVal);

	private:

		double _slope;
	};

	template <class T> 
	point LinearInterpolator<T>::interpolate(T xVal){
		dateInRangeCheck(xVal);
		if (_slope == NaN){
			double yDiff = std::get<1>(_endPoint) - std::get<1>(_startPoint);
			double xDiff = std::get<0>(_endPoint) - std::get<0>(_startPoint);
			_slope = yDiff / xDiff;
		}
		double yVal = _slope*(xVal - std::get<0>(_startPoint))+std::get<1>(_startPoint);
		return point(xVal, yVal);
	}
}
#endif