//created by Wang Jianwei on 1 Dec 2012

#include "SwapRateBootStrapper.h"
#include <iostream>
#include "YieldCurve.h"
#include "InterpolatorFactory.h"
#include "AbstractInterpolator.h"
#include "NumericalFactory.h"

using namespace utilities;

AbstractInterpolator* SwapRateBootStrapper::bootStrap(){
	
	targetFuncT numericalFunc;

	AbstractNumerical* an = NumericalFactory::getInstance()->getNumerical(&numericalFunc,_numericAlgo);
	double root = an->findRoot(0,0,0,0);

	AbstractInterpolator* ai = InterpolatorFactory::getInstance()->getInterpolator(_startPoint, point(_endDate,root) , _interpolAlgo);
	return ai;
}

double SwapRateBootStrapper::numericalFunc(double x){
	return 0;
}