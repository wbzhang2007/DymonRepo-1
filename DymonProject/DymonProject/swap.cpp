//created by Hu Kun 04 Dec 2012
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

swap::swap(date tradeDate, date maturityDate, double notional, double couponRate, vector<double> FLiborRate, currency fixLegCurr, currency floatingLegCurr, int paymentFreqFixLeg, int paymentFreqFloatingLeg, bool rollAccuralDates, RecordHelper::HolidayMap holidayMap) {
	
	/*_fixLegRate=fixLegRate;
	_floatLegSpread=floatLegSpread;
	_floatLegBenchMark=floatLegBenchMark;
    _notional=notional;

	_issueDate=issueDate;
	_maturityDate=maturityDate;
	_fixLegCurr=fixLegCurr;
	_floatLegCurr=floatLegCurr;
*/
	//date startDate(2013,11,2);
	//date maturityDate(2015,2,6);
	////date accuralStartDate(2013,11,3);
	////date accuralEndDate(2014,2,5);
	//
	//double notional=1000000;
	//double couponRate=0.05;
	//int paymentFreq=4;
	//build from start to end (build forward)
	int buildDirection=1;
	//RecordHelper::HolidayMap holidayMap;
	//bool rollAccuralDates=false;

	//currency cashFlowLegCurr=currency(enums::USD,enums::ACT_360, enums::ACT_ACT, enums::Mfollowing);

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

