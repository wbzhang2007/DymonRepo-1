//created by Jianwei 04 Dec 2012
#include "OptionPricer.h"
#include "Enums.h"
#define Pi 3.141592653589793238462643 

using namespace utilities;
using namespace instruments;

double OptionPricer::blackScholesFormula(enums::CallPut callPutFlag, double S, double K, double vol, double r, double T){
	double d1, d2;
	
	d1=(log(S/K)+(r+vol*vol/2)*T)/(vol*sqrt(T));
	d2=d1-vol*sqrt(T);

	if (callPutFlag == enums::Call)
		return S *CDF(d1)-K * exp(-r*T)*CDF(d2);
	return K * exp(-r * T) * CDF(-d2) - S * CDF(-d1);
	
}

double OptionPricer::blackFormula(enums::CallPut callPutFlag, double FwdS, double K, double vol, double discountFactor, double T){
	double d1, d2;

	d1=(log(FwdS/K)+vol*vol/2*T)/(vol*sqrt(T));
	d2=d1-vol*sqrt(T);

	if (callPutFlag == enums::Call)
		return discountFactor*(FwdS *CDF(d1)-K * CDF(d2));
	return discountFactor*(K * CDF(-d2) - FwdS * CDF(-d1));
}

double OptionPricer::CDF(double x){
	double L, K, w ;

	double const a1 = 0.31938153, a2 = -0.356563782, a3 = 1.781477937, a4 = -1.821255978, a5 = 1.330274429;

	L = fabs(x);
	K = 1.0 / (1.0 + 0.2316419 * L);
	w = 1.0 - 1.0 / sqrt(2 * Pi) * exp(-L *L / 2) * (a1 * K + a2 * pow(K,2) + a3 * pow(K,3) + a4 * pow(K,4) + a5 * pow(K,5));

	if (x < 0 )	w= 1.0 - w;
	return w;
} 
