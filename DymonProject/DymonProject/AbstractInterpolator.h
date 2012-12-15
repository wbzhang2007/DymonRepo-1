//created by Wang Jianwei on 01 Dec 2012
#ifndef ABSTRACTINTERPOLATOR_H
#define ABSTRACTINTERPOLATOR_H
#include <vector>
#include <tuple>
#include "date.h"

namespace utilities{
	class AbstractInterpolator{

	public:

		enum interpolAlgo{LINEAR,LOGLINEAR};

		typedef tuple<date, double> point;

		AbstractInterpolator(point startPoint, point endPoint);

		vector<point> interpolateM(std::vector<date> dates);
	
		virtual point interpolate(date date0);

		point getStartPoint();
		
		point getEndPoint();

	protected:

		point _startPoint;
		
		point _endPoint;
	};
}
#endif