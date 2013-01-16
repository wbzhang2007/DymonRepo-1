#include "BondPricer.h"

using namespace instruments;

double BondPricer::getMPV(cashflowLeg* couponLeg,DiscountCurve* discountCurve){
	double MPV = 0;
	vector<cashflow> couponLegVec = couponLeg->getCashFlowLeg();
	for (unsigned int i=0; i<couponLegVec.size();i++){
		cashflow coupon = couponLegVec[i];
		date paymentDate = coupon.getPaymentDate();
		double dcf = discountCurve->getDiscountFactor(paymentDate);
		double couponAmount = coupon.getCouponRate();
		double cashFlowAmt = couponAmount +((i==(couponLegVec.size()-1))?100:0);
		MPV = MPV +	cashFlowAmt*dcf;
	}
	return MPV;
}
		
double BondPricer::getParYield(cashflowLeg* couponLeg,DiscountCurve* discountCurve){
	return 0;
}