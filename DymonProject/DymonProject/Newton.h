//created by Wang Jianwei on 1 Dec 2012
//Implemented by Hu Kun on 16 Dec 2012
#ifndef NEWTON_H
#define NEWTON_H
//#include "AbstractNumerical.h"
#include "math.h"
#define MAXIT 100
#include <iostream>

using namespace std;


namespace utilities{
	/*class Newton: public AbstractNumerical{
		
	public:
		
		Newton(targetFuncT_Newton* func):AbstractNumerical(func){};

		double findRoot(double startVal, double endVal, double tolerance, int iterateCount);

	private:

	};*/

	class Newton {
		public:
			Newton() {};
			~Newton() {};
			static float findroot(void (*funcd)(float,float *, float *), float x1, float x2, float xacc, int iterateCount);


		private:
			


	};
}
#endif