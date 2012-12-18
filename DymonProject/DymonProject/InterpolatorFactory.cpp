//created by Wang Jianwei on 1 Dec 2012

#include "InterpolatorFactory.h"
#include "LinearInterpolator.h"
#include "LogLinearInterpolator.h"
#include "Enums.h"

using namespace utilities;
using namespace enums;

InterpolatorFactory* InterpolatorFactory::single = NULL;

InterpolatorFactory* InterpolatorFactory::getInstance()
{
	if(!single)
		single = new InterpolatorFactory();
	return single;
}


AbstractInterpolator* InterpolatorFactory::getInterpolator(point startPoint, point endPoint, enums::interpolAlgo algo){
	switch (algo){
	case LINEAR:
		return new LinearInterpolator(startPoint, endPoint);
	case LOGLINEAR:
		return new LogLinearInterpolator(startPoint, endPoint);
	default:
		return new LinearInterpolator(startPoint, endPoint);
	}
}