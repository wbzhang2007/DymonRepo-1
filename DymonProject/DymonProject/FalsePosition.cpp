//implemented by Hu Kun on 16 Dec 2012

#include "FalsePosition.h"
#include "math.h"

#include <iostream>

using namespace std;
using namespace utilities;




double FalsePosition::findRoot(double (*func)(double), double x1, double x2, float xacc, int iterateCount){

	int j;
	double fl,fh,xl,xh,temp,dx,del,f,rtf;

	fl=(*func)(x1);
	fh=(*func)(x2);
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
		f=(*func)(rtf);
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