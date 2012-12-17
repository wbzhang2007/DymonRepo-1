//created by Wang Jianwei on 01 Dec 2012
#ifndef LOGLINEARINTERPOLATOR_H
#define LOGLINEARINTERPOLATOR_H
#include "AbstractInterpolator.h"

namespace utilities{
	class LogLinearInterpolator: public AbstractInterpolator{

	public:

		LogLinearInterpolator(point startPoint, point endPoint);

		point interpolate(date date0);
		
	private:

		double _slope;
	};
}
#endif