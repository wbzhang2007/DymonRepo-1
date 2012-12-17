//created by Wang Jianwei on 01 Dec 2012
#ifndef NUMERICALFACTORY_H
#define NUMERICALFACTORY_H
#include "AbstractNumerical.h"
#include "AbstractBootStrapper.h"
#include "Bisection.h"
#include <tuple>
#include "date.h"
#include "Enums.h"
#include "Secant.h"
#include "FalsePosition.h"
#include "Newton.h"
#include "Ridder.h"

using namespace enums;

namespace utilities{
	template<typename T> class NumericalFactory{

	public:

		typedef tuple<date, double> point;

		static NumericalFactory<T>* getInstance();

		AbstractNumerical<T>* getNumerical(T* callerObj, double (T::*func) (double d), enums::NumericAlgo algo);

	private:

		NumericalFactory(){};

		static NumericalFactory<T>* single;

	};

	template<typename T> 
	NumericalFactory<T>* NumericalFactory<T>::single = NULL;

	template<typename T> 
	NumericalFactory<T>* NumericalFactory<T>::getInstance()
	{
		if(!single)
			single = new NumericalFactory<T>();
		return single;
	}


	template<typename T> 
	AbstractNumerical<T>* NumericalFactory<T>::getNumerical(T* callerObj, double (T::*func) (double d), enums::NumericAlgo algo){
		switch (algo){
		case BISECTION:
			return new Bisection<T>(callerObj, func);
		case SECANT:
			return new Secant<T>(callerObj, func);
		case RIDDER:
			return new Ridder<T>(callerObj, func);
		case FALSEPOSITION:
			return new FalsePosition<T>(callerObj, func);
		default:
			return new Bisection<T>(callerObj,func);
		}
	}
}
#endif