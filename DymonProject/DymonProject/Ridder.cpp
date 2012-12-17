//implemented by Hu Kun on 16 Dec 2012

#include "Ridder.h"
#include "math.h"
#include <iostream>

#define UNUSED (-1.11e30)

using namespace std;
using namespace utilities;



double Ridder::findRoot(double (*func)(double), double x1, double x2, float xacc, int iterateCount){
	
	

	int j;
	double ans,fh,fl,fm,fnew,s,xh,xl,xm,xnew;

	fl=(*func)(x1);
	fh=(*func)(x2);

	if ((fl>0.0&& fh<0.0)||(fl<0.0&& fh>0.0)) {
		xl=x1;
		xh=x2;
		ans=UNUSED;
		for (j=1;j<=iterateCount;j++) {
			xm=0.5*(xl+xh);
			fm=(*func)(xm);
			s=sqrt(fm*fm-fl*fh);
			if (s==0.0) return ans;
			xnew=xm+(xm-xl)*((fl>=fh?1.0:-1.0)*fm/s);
			if(fabs(xnew-ans)<=xacc) return ans;
			ans=xnew;
			fnew=(*func)(ans);
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