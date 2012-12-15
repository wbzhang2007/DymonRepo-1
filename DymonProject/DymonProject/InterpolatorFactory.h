//created by Wang Jianwei on 01 Dec 2012
#ifndef INTERPOLATORFACTORY_H
#define INTERPOLATORFACTORY_H
#include "AbstractInterpolator.h"

namespace utilities{
	class InterpolatorFactory{

	public:

		typedef tuple<date, double> point;

		static InterpolatorFactory* getInstance();

		AbstractInterpolator* getInterpolator(point startPoint, point endPoint, AbstractInterpolator::interpolAlgo algo);

	private:

		InterpolatorFactory(){};
		
		static InterpolatorFactory* single;

	};
}
#endif