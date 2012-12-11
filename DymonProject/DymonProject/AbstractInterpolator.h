//created by Wang Jianwei on 01 Dec 2012
#ifndef ABSTRACTINTERPOLATOR_H
#define ABSTRACTINTERPOLATOR_H
#include <vector>
#include <tuple>
#include "date.h"

namespace utilities{
	class AbstractInterpolator{

		enum interpolAlgo{LINEAR,LOGLINEAR};

	public:

		typedef tuple<date, double> point;

		AbstractInterpolator(point startPoint, point endPoint);

		vector<point>* interpolateM(std::vector<date>* dates);
	
		virtual point interpolateS(date date0);

	private:

		point _startPoint;
		
		point _endPoint;
	};
}
#endif