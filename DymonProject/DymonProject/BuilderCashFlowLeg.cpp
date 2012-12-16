//created by Hu Kun Dec 13
#include "cashflowLeg.h"
#include "cashflow.h"
#include "BuilderCashFlowLeg.h"
#include <math.h>
#include <stdio.h>
#include "date.h"
#include "dateUtil.h"
#include <vector>
#include "RecordHelper.h"

using namespace Session;
using namespace utilities;
using namespace std;
using namespace enums;

namespace instruments {

	BuilderCashFlowLeg::BuilderCashFlowLeg() {
	}
	
BuilderCashFlowLeg::BuilderCashFlowLeg(date startDate, date maturityDate,double couponRate,double notional, int paymentFreq, currency cashFlowLegCurr,bool rollAccuralDates, int buildDirection,RecordHelper::HolidayMap holidayMap) {
		
	if (buildDirection==1) {
		int numOfMonthIncr=12/paymentFreq;
		int i=1;
		vector<cashflow> builtCashflowLeg;
		date calDateNewStart=dateUtil::getEndDate(startDate,numOfMonthIncr*i,true);
		while((dateUtil::getBizDaysBetween(dateUtil::getEndDate(startDate,numOfMonthIncr*i,rollAccuralDates),maturityDate)>=0)&&(dateUtil::getBizDaysBetween(dateUtil::getEndDate(startDate,numOfMonthIncr*(i+1),rollAccuralDates),maturityDate)>=0)){
			date calDateNewStart=dateUtil::getEndDate(startDate,numOfMonthIncr*i,rollAccuralDates);
			date calDateNewEnd=dateUtil::getEndDate(startDate,numOfMonthIncr*(i+1),rollAccuralDates);
			date calFixingDate=dateUtil::getBizDate(calDateNewStart,-2,cashFlowLegCurr.getDayRollConvention(),"");
			date calPaymentDate=dateUtil::dayRollAdjust(calDateNewEnd,cashFlowLegCurr.getDayRollConvention(),"");
			
			cashflow aCashflow(couponRate,notional,  calFixingDate, calPaymentDate,calDateNewStart, calDateNewEnd,cashFlowLegCurr);
			builtCashflowLeg.push_back(aCashflow);

			i++;
		}

		if ((dateUtil::getBizDaysBetween(dateUtil::getEndDate(startDate,numOfMonthIncr*i,true),maturityDate)<0)||(dateUtil::getBizDaysBetween(dateUtil::getEndDate(startDate,numOfMonthIncr*(i+1),true),maturityDate)<0)) {
			date calDateNewStart=dateUtil::getEndDate(startDate,numOfMonthIncr*i,rollAccuralDates);
			date calDateNewEnd=maturityDate;
			date calFixingDate=dateUtil::getBizDate(calDateNewStart,-2,cashFlowLegCurr.getDayRollConvention(),"");
			date calPaymentDate=dateUtil::dayRollAdjust(calDateNewEnd,cashFlowLegCurr.getDayRollConvention(),"");
			cashflow aCashflow(couponRate,notional,  calFixingDate, calPaymentDate,calDateNewStart, calDateNewEnd,cashFlowLegCurr);
			
			builtCashflowLeg.push_back(aCashflow);
		}
		_cashflowLeg=cashflowLeg(builtCashflowLeg).getCashFlowLeg();
	}

	if (buildDirection==-1) {
		int numOfMonthIncr=12/paymentFreq;
		int i=0;
		vector<cashflow> builtCashflowLeg;
		date calDateNewStart=dateUtil::getEndDate(maturityDate,-numOfMonthIncr*i,true);
		while((dateUtil::getBizDaysBetween(startDate,dateUtil::getEndDate(maturityDate,-numOfMonthIncr*(i+1),rollAccuralDates))>=0)&&(dateUtil::getBizDaysBetween(startDate,dateUtil::getEndDate(maturityDate,-numOfMonthIncr*i,rollAccuralDates))>=0)){
			date calDateNewStart=dateUtil::getEndDate(maturityDate,-numOfMonthIncr*(i+1),rollAccuralDates);
			date calDateNewEnd=dateUtil::getEndDate(maturityDate,-numOfMonthIncr*i,rollAccuralDates);
			date calFixingDate=dateUtil::getBizDate(calDateNewStart,-2,cashFlowLegCurr.getDayRollConvention(),"");
			date calPaymentDate=dateUtil::dayRollAdjust(calDateNewEnd,cashFlowLegCurr.getDayRollConvention(),"");
			
			cashflow aCashflow(couponRate,notional,  calFixingDate, calPaymentDate,calDateNewStart, calDateNewEnd,cashFlowLegCurr);
			
			builtCashflowLeg.insert(builtCashflowLeg.begin(),aCashflow);

			i++;
		}

		if ((dateUtil::getBizDaysBetween(startDate,dateUtil::getEndDate(maturityDate,-numOfMonthIncr*i,rollAccuralDates))<0)||(dateUtil::getBizDaysBetween(startDate,dateUtil::getEndDate(maturityDate,-numOfMonthIncr*(i+1),rollAccuralDates))<0)) {
			date calDateNewStart=startDate;
			date calDateNewEnd=dateUtil::getEndDate(maturityDate,-numOfMonthIncr*i,rollAccuralDates);
			date calFixingDate=dateUtil::getBizDate(calDateNewStart,-2,cashFlowLegCurr.getDayRollConvention(),"");
			date calPaymentDate=dateUtil::dayRollAdjust(calDateNewEnd,cashFlowLegCurr.getDayRollConvention(),"");
			cashflow aCashflow(couponRate,notional,  calFixingDate, calPaymentDate,calDateNewStart, calDateNewEnd,cashFlowLegCurr);
			
			builtCashflowLeg.insert(builtCashflowLeg.begin(),aCashflow);
		}
		_cashflowLeg=cashflowLeg(builtCashflowLeg).getCashFlowLeg();
	}

}
	
	cashflowLeg BuilderCashFlowLeg::getCashFlowLeg() {
		return _cashflowLeg;
	}
	BuilderCashFlowLeg::BuilderCashFlowLeg(date startDate, int tenorNumOfMonths,double couponRate,double notional, int paymentFreq, currency cashFlowLegCurr,bool rollAccuralDates,RecordHelper::HolidayMap holidayMap) {

	}

	BuilderCashFlowLeg::~BuilderCashFlowLeg() {
	}	
}