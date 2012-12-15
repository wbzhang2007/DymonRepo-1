//created by Wang Jianwei on 01 Dec 2012
#ifndef NUMERICALFACTORY_H
#define NUMERICALFACTORY_H
#include "AbstractNumerical.h"
#include <tuple>
#include "date.h"

namespace utilities{
	class NumericalFactory{

	public:

		typedef tuple<date, double> point;

		typedef double (*targetFuncT) (double d);

		static NumericalFactory* getInstance();

		AbstractNumerical* getNumerical(targetFuncT* func, AbstractNumerical::NumericAlgo algo);

	private:

		NumericalFactory(){};
		
		static NumericalFactory* single;

	};
}
#endif