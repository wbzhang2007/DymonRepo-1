//created by Wang Jianwei on 1 Dec 2012

#include "InterpolatorFactory.h"
#include "LinearInterpolator.h"
#include "LogLinearInterpolator.h"

using namespace utilities;

InterpolatorFactory* InterpolatorFactory::single = NULL;

InterpolatorFactory* InterpolatorFactory::getInstance()
{
	if(!single)
		single = new InterpolatorFactory();
	return single;
}


AbstractInterpolator* InterpolatorFactory::getInterpolator(point startPoint, point endPoint, AbstractInterpolator::interpolAlgo algo){
	switch (algo){
	case AbstractInterpolator::LINEAR:
		return new LinearInterpolator(startPoint, endPoint);
	case AbstractInterpolator::LOGLINEAR:
		return new LogLinearInterpolator(startPoint, endPoint);
	default:
		return new LinearInterpolator(startPoint, endPoint);
	}
}