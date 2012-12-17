//implemented by Hu Kun on 16 Dec 2012

#include "Secant.h"
#include "math.h"
#include <iostream>

using namespace std;
using namespace utilities;


double Secant::findRoot(double (*func)(double), double x1, double x2, float xacc, int iterateCount){

	int j;
	double fl,f,dx,temp,xl,rts;

	fl=(*func)(x1);
	f=(*func)(x2);
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
		f=(*func)(rts);
		if ((fabs(dx)<xacc)|| f==0.0) return rts;
	}

	cout<<"Maximum number of iterations exceeded in Secant"<<endl;
	return 0.0;
}