//created by Wang Jianwei on 01 Dec 2012
#ifndef INTERPOLATORFACTORY_H
#define INTERPOLATORFACTORY_H
#include "AbstractInterpolator.h"
#include "LogLinearInterpolator.h"
#include "LinearInterpolator.h"
#include "Enums.h"

using namespace enums;

namespace utilities{
	template<typename T> class InterpolatorFactory{

	public:

		typedef tuple<T, double> point;

		static InterpolatorFactory* getInstance();

		AbstractInterpolator<T>* getInterpolator(point startPoint, point endPoint, enums::interpolAlgo algo);

	private:

		InterpolatorFactory(){};
		
		static InterpolatorFactory<T>* single;

	};

	template<typename T> 
	InterpolatorFactory<T>* InterpolatorFactory<T>::single = NULL;

	template<typename T> 
	InterpolatorFactory<T>* InterpolatorFactory<T>::getInstance()
	{
		if(!single)
			single = new InterpolatorFactory<T>();
		return single;
	}

	template<typename T> 
	AbstractInterpolator<T>* InterpolatorFactory<T>::getInterpolator(point startPoint, point endPoint, enums::interpolAlgo algo){
		switch (algo){
		case LINEAR:
			return new LinearInterpolator<T>(startPoint, endPoint);
		case LOGLINEAR:
			return new LogLinearInterpolator<T>(startPoint, endPoint);
		default:
			return new LinearInterpolator<T>(startPoint, endPoint);
		}
	}
}
#endif