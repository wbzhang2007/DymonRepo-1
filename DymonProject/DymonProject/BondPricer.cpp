#include "BondPricer.h"

using namespace instruments;

double BondPricer::getMPV(){
	return getMPV(_couponLeg, _discountCurve);
}

double BondPricer::getMPV(cashflowLeg* couponLeg,DiscountCurve* discountCurve){
	return 0;
}
		
double BondPricer::getParYield(cashflowLeg* couponLeg,DiscountCurve* discountCurve){
	return 0;
}