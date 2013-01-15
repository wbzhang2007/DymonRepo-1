#include "BondPricer.h"

using namespace instruments;

double BondPricer::getMPV(){
	return getMPV(_couponLeg, _bondCurve);
}

double BondPricer::getMPV(cashflowLeg* couponLeg,BondCurve* bondCurve){
	return 0;
}
		
double BondPricer::getParYield(cashflowLeg* couponLeg,BondCurve* bondCurve){
	return 0;
}