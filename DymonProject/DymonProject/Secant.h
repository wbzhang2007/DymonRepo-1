//created by Hu Kun 17 Dec

#ifndef SECANT_H
#define SECANT_H
#include "AbstractNumerical.h"

namespace utilities{
	template <class T> class Secant: public AbstractNumerical<T>{

	public:

		Secant(T* callerObj, double (T::*func) (double d)):AbstractNumerical(callerObj){_func = func;};

		double findRoot(double x1, double x2, double xacc, int iterateCount);

	private:

		double (T::*_func) (double d);

	};

	template <class T> 	
	double Secant<T>::findRoot(double x1, double x2, double xacc, int iterateCount){

		int j;
		double fl,f,dx,temp,xl,rts;

		fl=(*_callerObj.*_func)(x1);
		f=(*_callerObj.*_func)(x2);
		if (fabs(fl)<fabs(f)) {
			rts=x1;
			xl=x2;
			temp=fl;
			fl=f;
			f=temp;
		} else  {
			xl=x1;
			rts=x2;
		}

		for (j=1;j<=iterateCount;j++) {
			dx=(xl-rts)*f/(f-fl);
			xl=rts;
			fl=f;
			rts +=dx;
			f=(*_callerObj.*_func)(rts);
			if ((fabs(dx)<xacc)|| f==0.0) return rts;
		}

		cout<<"Maximum number of iterations exceeded in Secant"<<endl;
		return 0.0;
	}
}
#endif