//created by Wang Jianwei on 1 Dec 2012

#include "NumericalFactory.h"
#include "Newton.h"
#include "Bisection.h"
#include "AbstractNumerical.h"

using namespace utilities;

NumericalFactory* NumericalFactory::single = NULL;

NumericalFactory* NumericalFactory::getInstance()
{
	if(!single)
		single = new NumericalFactory();
	return single;
}


AbstractNumerical* NumericalFactory::getNumerical(targetFuncT* func, AbstractNumerical::NumericAlgo algo){
	switch (algo){
	case AbstractNumerical::NEWTON:
		return new Newton(func);
	case AbstractNumerical::BISECTION:
		return new Bisection(func);
	}
	return NULL;
}