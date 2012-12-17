//created by Hu Kun 17 Dec

#ifndef FALSEPOSITION_H
#define FALSEPOSITION_H
#include "AbstractNumerical.h"

namespace utilities{
	template <class T> class FalsePosition: public AbstractNumerical<T>{

	public:

		FalsePosition(T* callerObj, double (T::*func) (double d)):AbstractNumerical(callerObj){_func = func;};

		double findRoot(double x1, double x2, double xacc, int iterateCount);

	private:

		double (T::*_func) (double d);
	};

	template <class T> 
	double FalsePosition<T>::findRoot(double x1, double x2, double xacc, int iterateCount){

		int j;
		double fl,fh,xl,xh,temp,dx,del,f,rtf;

		fl=(*_callerObj.*_func)(x1);
		fh=(*_callerObj.*_func)(x2);
		if(fl*fh>0.0) cout<<"Root must be bracketed in FalsePosition"<<endl;
		if (fl<0.0) {
			xl=x1;
			xh=x2;
		} else {
			x1=x2;
			xh=x1;
			temp=fl;
			fl=fh;
			fh=temp;
		}
		dx=xh-xl;
		for (j=1;j<=iterateCount;j++) {
			rtf=xl+dx*fl/(fl-fh);
			f=(*_callerObj.*_func)(rtf);
			if(f<0.0) {
				del=xl-rtf;
				xl=rtf;
				fl=f;
			} else {
				del=xh-rtf;
				xh=rtf;
				fh=f;
			}
			dx=xh-xl;
			if (fabs(del)<xacc|| f==0.0) return rtf;
		}

		cout<<"Maximum number of iterations exceeded in FalsePosition"<<endl;
		return 0.0; 
	}
}
#endif