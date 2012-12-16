//created by Hu Kun 04 Dec 2012
//rewrote again with cashflow constructs by Kun 16 Dec 2012
#include "swap.h"
#include <iterator>
#include "date.h"
#include "dateUtil.h"
#include "cashflow.h"
#include "cashflowLeg.h"
#include "BuilderCashFlowLeg.h"
#include "RecordHelper.h"

using namespace instruments;
using namespace utilities;
using namespace std;
using namespace enums;

namespace instruments {
swap::swap(date tradeDate, date maturityDate, double notional, double couponRate, vector<double> FLiborRate, currency fixLegCurr, currency floatingLegCurr, int paymentFreqFixLeg, int paymentFreqFloatingLeg, bool rollAccuralDates, RecordHelper::HolidayMap holidayMap) {
	
	
	int buildDirection=1;

	setTradeDate(tradeDate);
	setMaturityDate(maturityDate);

	BuilderCashFlowLeg builtCashflowLeg1(tradeDate, maturityDate,couponRate,notional, paymentFreqFixLeg, fixLegCurr, rollAccuralDates, buildDirection,holidayMap);

	BuilderCashFlowLeg builtCashflowLeg2(tradeDate, maturityDate,FLiborRate,notional, paymentFreqFloatingLeg, floatingLegCurr, rollAccuralDates, buildDirection,holidayMap);
	
	_fixCashflowLeg=builtCashflowLeg1.getCashFlowLeg();
	_floatingCashflowLeg=builtCashflowLeg2.getCashFlowLeg();
}

swap::~swap() {

}

cashflowLeg swap::getCashflowLegFix() {
	return _fixCashflowLeg;
}

cashflowLeg swap::getCashflowLegFloat() {
	return _floatingCashflowLeg;
}
}

void swap::printCashflowLegFix() {
	_fixCashflowLeg.printCashFlowLeg();
}
void swap::printCashflowLegFloat() {

	_floatingCashflowLeg.printCashFlowLeg();
	
}

//double swap::getParRate() {
//		
//	return 0.0;
//}
//
//vector<date> swap::getFloatingFixingDate() {
//		
//	int fLegFreq=_floatLegCurr.getPaymentFreq();
//	//vector<date>::iterator it;
//	//int i=0;
//	//long increment=dateUtil::getBizDaysBetween(_issueDate,_maturityDate)/fLegFreq;
//	//for (it= _floatingFixingDate.begin();it!= _floatingFixingDate.end();++it) { 
//	//        *it=dateUtil::getBizDate(_issueDate, increment*(++i), _floatLegCurr.getDayRollConvention());
//	//	}
//	return _floatingFixingDate;
//		
//}
//
//vector<date> swap::getFixLegPaymentDate() {
//	//int fixLegFreq=_fixLegCurr.getPaymentFreq();
//	//vector<date>::iterator it;
//	//int i=0;
//	//long increment=dateUtil::getBizDaysBetween(_issueDate,_maturityDate)/fixLegFreq;
//	//for (it= _floatingFixingDate.begin();it!= _floatingFixingDate.end();++it) { 
//	 //       *it=dateUtil::getBizDate(_issueDate, increment*(++i), _floatLegCurr.getDayRollConvention());
//	//	}
//	return _fixLegPaymentDate;
//
//}
//
//vector<date> swap::getFloatLegPaymentDate() {
//	/*int fLegFreq=_floatLegCurr.getPaymentFreq();
//	vector<date>::iterator it;
//	vector<date>::iterator it_floatPay=_floatLegPaymentDate.begin();
//	int i=0;
//	long increment=dateUtil::getBizDaysBetween(_issueDate,_maturityDate)/fLegFreq;
//	for (it= _floatingFixingDate.begin();it!= _floatingFixingDate.end();++it) { 
//	        *it=dateUtil::getBizDate(_issueDate, increment*(++i), _floatLegCurr.getDayRollConvention());
//			*it_floatPay=*it;
//			it_floatPay++;
//		}*/
//	return _floatLegPaymentDate;
//
//}
//
//vector<date> swap::getFloatLegAccuralBeginDate() {
//	/*int fLegFreq=_floatLegCurr.getPaymentFreq();
//	vector<date>::iterator it_fix;
//	vector<date>::iterator it_accrBeg=_accuralBeginDate.begin();
//
//	int i=0;
//	long increment=dateUtil::getBizDaysBetween(_issueDate,_maturityDate)/fLegFreq;
//	for (it_fix= _floatingFixingDate.begin();it_fix!= _floatingFixingDate.end();++it_fix) { 
//	        *it_accrBeg=dateUtil::getBizDate(*it_fix, 2, _floatLegCurr.getDayRollConvention());
//			it_accrBeg++;
//		}*/
//	return _accuralBeginDate;
//
//}
//
//double swap::getSwapValue() {
//
//	return 0.0;
//
//}

