//created by Wang Jianwei on 01 Dec 2012
#ifndef LINEARINTERPOLATOR_H
#define LINEARINTERPOLATOR_H
#include <string>
#include <map>
#include "AbstractInterpolator.h"

namespace utilities{
	class LinearInterpolator: public AbstractInterpolator{

	public:

		LinearInterpolator(point startPoint, point endPoint);

		point interpolateS(date date0);

	};
}
#endif