//created by Hu Kun 17 Dec

#ifndef RIDDER_H
#define RIDDER_H
#include "AbstractNumerical.h"
#define UNUSED (-1.11e30)

namespace utilities{
	template<typename T> class Ridder: public AbstractNumerical<T>{

	public:

		Ridder(T* callerObj, double (T::*func) (double d)):AbstractNumerical(callerObj){_func = func;};

		double findRoot(double x1, double x2, double xacc, int iterateCount);
		
	private:

		double (T::*_func) (double d);
	};

	template<typename T> 
	double Ridder<T>::findRoot(double x1, double x2, double xacc, int iterateCount){

		int j;
		double ans,fh,fl,fm,fnew,s,xh,xl,xm,xnew;

		fl=(*_callerObj.*_func)(x1);
		fh=(*_callerObj.*_func)(x2);

		if ((fl>0.0&& fh<0.0)||(fl<0.0&& fh>0.0)) {
			xl=x1;
			xh=x2;
			ans=UNUSED;
			for (j=1;j<=iterateCount;j++) {
				xm=0.5*(xl+xh);
				fm=(*_callerObj.*_func)(xm);
				s=sqrt(fm*fm-fl*fh);
				if (s==0.0) return ans;
				xnew=xm+(xm-xl)*((fl>=fh?1.0:-1.0)*fm/s);
				if(fabs(xnew-ans)<=xacc) return ans;
				ans=xnew;
				fnew=(*_callerObj.*_func)(ans);
				if (fnew==0.0) return ans;

				if (((fm>=fnew?1.0:-1.0)*fm)!=fm) {
					xl=xm;
					fl=fm;
					xh=ans;
					fh=fnew;
				} else if (((fl>=fnew?1.0:-1.0)*fl)!=fl) {
					xh=ans;
					fh=fnew;
				} else if (((fh>=fnew?1.0:-1.0)*fh)!=fh) {
					xl=ans;
					fl=fnew;
				} 
				else {
					cout<<"never get here."<<endl;
				}
				if (fabs(xh-xl)<=xacc) return ans;
			}
			cout<<"Maximum iterations exceeded in Ridder"<<endl;
		} 
		else {
			if (fl==0.0) return x1;
			if (fh=0.0) return x2;
			cout<<"root must be bracketed in Ridder"<<endl;
		}
		return 0.0;
	}
}
#endif