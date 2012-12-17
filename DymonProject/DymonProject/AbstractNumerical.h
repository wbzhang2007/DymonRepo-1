//created by Wang Jianwei on 01 Dec 2012
#include <iostream>

using namespace std;


#ifndef ABSTRACTNUMERICAL_H
#define ABSTRACTNUMERICAL_H
#include "TestNumerical.h"


namespace utilities{
	template<typename T> class AbstractNumerical{

	public:

		AbstractNumerical(T* callerObj){_callerObj=callerObj;};

		virtual double findRoot(double startVal, double endVal, double tolerance, int iterateCount){return 0;}
		
	protected:
		
		T* _callerObj;

	};
}
#endif