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
#include <algorithm>

using namespace Session;
using namespace utilities;
using namespace std;
using namespace enums;

using namespace instruments;

BuilderCashFlowLeg::BuilderCashFlowLeg(date startDate, date maturityDate,double couponRate,double notional, int paymentFreq, currency cashFlowLegCurr,bool rollAccuralDates, int buildDirection,RecordHelper::HolidayMap holidayMap) {

	if (buildDirection==1) {
		int numOfMonthIncr=12/paymentFreq;
		int i=0;
		vector<cashflow> builtCashflowLeg;
		date calDateNewStart=dateUtil::getEndDate(startDate,numOfMonthIncr*i,true);
		while((dateUtil::getBizDaysBetween(dateUtil::getEndDate(startDate,numOfMonthIncr*i,true),maturityDate)>=0)&&(dateUtil::getBizDaysBetween(dateUtil::getEndDate(startDate,numOfMonthIncr*(i+1),true),maturityDate)>=0)){
			date calDateNewStart=dateUtil::getEndDate(startDate,numOfMonthIncr*i,true);
			date calDateNewEnd=dateUtil::getEndDate(startDate,numOfMonthIncr*(i+1),true);

			if (rollAccuralDates) {
				calDateNewStart=dateUtil::dayRollAdjust(calDateNewStart,cashFlowLegCurr.getDayRollSwapConvention(),"");
				calDateNewEnd=dateUtil::dayRollAdjust(calDateNewEnd,cashFlowLegCurr.getDayRollSwapConvention(),"");
			}
			date calFixingDate=dateUtil::getBizDate(calDateNewStart,-2,cashFlowLegCurr.getDayRollSwapConvention(),"");
			date calPaymentDate=dateUtil::dayRollAdjust(calDateNewEnd,cashFlowLegCurr.getDayRollSwapConvention(),"");

			cashflow aCashflow(couponRate,notional,  calFixingDate, calPaymentDate,calDateNewStart, calDateNewEnd,cashFlowLegCurr);
			builtCashflowLeg.push_back(aCashflow);

			i++;
		}

		if ((dateUtil::getBizDaysBetween(dateUtil::getEndDate(startDate,numOfMonthIncr*i,true),maturityDate)<0)||(dateUtil::getBizDaysBetween(dateUtil::getEndDate(startDate,numOfMonthIncr*(i+1),true),maturityDate)<0)) {
			date calDateNewStart=dateUtil::getEndDate(startDate,numOfMonthIncr*i,true);
			date calDateNewEnd=maturityDate;

			if (rollAccuralDates) {
				calDateNewStart=dateUtil::dayRollAdjust(calDateNewStart,cashFlowLegCurr.getDayRollSwapConvention(),"");
				calDateNewEnd=dateUtil::dayRollAdjust(calDateNewEnd,cashFlowLegCurr.getDayRollSwapConvention(),"");
			}

			date calFixingDate=dateUtil::getBizDate(calDateNewStart,-2,cashFlowLegCurr.getDayRollSwapConvention(),"");
			date calPaymentDate=dateUtil::dayRollAdjust(calDateNewEnd,cashFlowLegCurr.getDayRollSwapConvention(),"");
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
		while((dateUtil::getBizDaysBetween(startDate,dateUtil::getEndDate(maturityDate,-numOfMonthIncr*(i+1),true))>=0)&&(dateUtil::getBizDaysBetween(startDate,dateUtil::getEndDate(maturityDate,-numOfMonthIncr*i,true))>=0)){
			date calDateNewStart=dateUtil::getEndDate(maturityDate,-numOfMonthIncr*(i+1),true);
			date calDateNewEnd=dateUtil::getEndDate(maturityDate,-numOfMonthIncr*i,true);

			if (rollAccuralDates) {
				calDateNewStart=dateUtil::dayRollAdjust(calDateNewStart,cashFlowLegCurr.getDayRollSwapConvention(),"");
				calDateNewEnd=dateUtil::dayRollAdjust(calDateNewEnd,cashFlowLegCurr.getDayRollSwapConvention(),"");
			}

			date calFixingDate=dateUtil::getBizDate(calDateNewStart,-2,cashFlowLegCurr.getDayRollSwapConvention(),"");
			date calPaymentDate=dateUtil::dayRollAdjust(calDateNewEnd,cashFlowLegCurr.getDayRollSwapConvention(),"");

			cashflow aCashflow(couponRate,notional,  calFixingDate, calPaymentDate,calDateNewStart, calDateNewEnd,cashFlowLegCurr);

			builtCashflowLeg.insert(builtCashflowLeg.begin(),aCashflow);

			i++;
		}

		if ((dateUtil::getBizDaysBetween(startDate,dateUtil::getEndDate(maturityDate,-numOfMonthIncr*i,true))<0)||(dateUtil::getBizDaysBetween(startDate,dateUtil::getEndDate(maturityDate,-numOfMonthIncr*(i+1),true))<0)) {
			date calDateNewStart=startDate;
			date calDateNewEnd=dateUtil::getEndDate(maturityDate,-numOfMonthIncr*i,true);
			date calFixingDate=dateUtil::getBizDate(calDateNewStart,-2,cashFlowLegCurr.getDayRollSwapConvention(),"");
			date calPaymentDate=dateUtil::dayRollAdjust(calDateNewEnd,cashFlowLegCurr.getDayRollSwapConvention(),"");

			if (rollAccuralDates) {
				calDateNewStart=dateUtil::dayRollAdjust(calDateNewStart,cashFlowLegCurr.getDayRollSwapConvention(),"");
				calDateNewEnd=dateUtil::dayRollAdjust(calDateNewEnd,cashFlowLegCurr.getDayRollSwapConvention(),"");
			}

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

	int numOfMonthIncr=12/paymentFreq;
	int i=0;
	vector<cashflow> builtCashflowLeg;

	date calDateNewStart=dateUtil::getEndDate(startDate,numOfMonthIncr*i,true);
	while((numOfMonthIncr*i<=tenorNumOfMonths)&&(numOfMonthIncr*(i+1)<=tenorNumOfMonths)){
		date calDateNewStart=dateUtil::getEndDate(startDate,numOfMonthIncr*i,true);
		date calDateNewEnd=dateUtil::getEndDate(startDate,numOfMonthIncr*(i+1),true);

		if (rollAccuralDates) {
			calDateNewStart=dateUtil::dayRollAdjust(calDateNewStart,cashFlowLegCurr.getDayRollSwapConvention(),"");
			calDateNewEnd=dateUtil::dayRollAdjust(calDateNewEnd,cashFlowLegCurr.getDayRollSwapConvention(),"");
		}
		date calFixingDate=dateUtil::getBizDate(calDateNewStart,-2,cashFlowLegCurr.getDayRollSwapConvention(),"");
		date calPaymentDate=dateUtil::dayRollAdjust(calDateNewEnd,cashFlowLegCurr.getDayRollSwapConvention(),"");

		cashflow aCashflow(couponRate,notional,  calFixingDate, calPaymentDate,calDateNewStart, calDateNewEnd,cashFlowLegCurr);
		builtCashflowLeg.push_back(aCashflow);

		i++;
	}

	if (((numOfMonthIncr*i>tenorNumOfMonths)||(numOfMonthIncr*(i+1)>tenorNumOfMonths))&&(numOfMonthIncr*i!=tenorNumOfMonths)) {
		date calDateNewStart=dateUtil::getEndDate(startDate,numOfMonthIncr*i,true);
		date calDateNewEnd=dateUtil::getEndDate(startDate,tenorNumOfMonths,true);

		if (rollAccuralDates) {
			calDateNewStart=dateUtil::dayRollAdjust(calDateNewStart,cashFlowLegCurr.getDayRollSwapConvention(),"");
			calDateNewEnd=dateUtil::dayRollAdjust(calDateNewEnd,cashFlowLegCurr.getDayRollSwapConvention(),"");
		}

		date calFixingDate=dateUtil::getBizDate(calDateNewStart,-2,cashFlowLegCurr.getDayRollSwapConvention(),"");
		date calPaymentDate=dateUtil::dayRollAdjust(calDateNewEnd,cashFlowLegCurr.getDayRollSwapConvention(),"");
		cashflow aCashflow(couponRate,notional,  calFixingDate, calPaymentDate,calDateNewStart, calDateNewEnd,cashFlowLegCurr);

		builtCashflowLeg.push_back(aCashflow);
	}
	_cashflowLeg=cashflowLeg(builtCashflowLeg).getCashFlowLeg();
}

BuilderCashFlowLeg::~BuilderCashFlowLeg() {
}

BuilderCashFlowLeg::BuilderCashFlowLeg(date startDate, date maturityDate,vector<double> FLiborRate,double notional, int paymentFreq, currency cashFlowLegCurr,bool rollAccuralDates, int buildDirection,RecordHelper::HolidayMap holidayMap) {

	if (buildDirection==1) {
		int numOfMonthIncr=12/paymentFreq;
		int i=0;
		vector<cashflow> builtCashflowLeg;
		date calDateNewStart=dateUtil::getEndDate(startDate,numOfMonthIncr*i,true);
		while((dateUtil::getBizDaysBetween(dateUtil::getEndDate(startDate,numOfMonthIncr*i,true),maturityDate)>=0)&&(dateUtil::getBizDaysBetween(dateUtil::getEndDate(startDate,numOfMonthIncr*(i+1),true),maturityDate)>=0)){
			date calDateNewStart=dateUtil::getEndDate(startDate,numOfMonthIncr*i,true);
			date calDateNewEnd=dateUtil::getEndDate(startDate,numOfMonthIncr*(i+1),true);

			if (rollAccuralDates) {
				calDateNewStart=dateUtil::dayRollAdjust(calDateNewStart,cashFlowLegCurr.getDayRollSwapConvention(),"");
				calDateNewEnd=dateUtil::dayRollAdjust(calDateNewEnd,cashFlowLegCurr.getDayRollSwapConvention(),"");
			}
			date calFixingDate=dateUtil::getBizDate(calDateNewStart,-2,cashFlowLegCurr.getDayRollSwapConvention(),"");
			date calPaymentDate=dateUtil::dayRollAdjust(calDateNewEnd,cashFlowLegCurr.getDayRollSwapConvention(),"");

			cashflow aCashflow(FLiborRate.at(i),notional,  calFixingDate, calPaymentDate,calDateNewStart, calDateNewEnd,cashFlowLegCurr);
			builtCashflowLeg.push_back(aCashflow);

			i++;
		}

		if ((dateUtil::getBizDaysBetween(dateUtil::getEndDate(startDate,numOfMonthIncr*i,true),maturityDate)<0)||(dateUtil::getBizDaysBetween(dateUtil::getEndDate(startDate,numOfMonthIncr*(i+1),true),maturityDate)<0)) {
			date calDateNewStart=dateUtil::getEndDate(startDate,numOfMonthIncr*i,true);
			date calDateNewEnd=maturityDate;

			if (rollAccuralDates) {
				calDateNewStart=dateUtil::dayRollAdjust(calDateNewStart,cashFlowLegCurr.getDayRollSwapConvention(),"");
				calDateNewEnd=dateUtil::dayRollAdjust(calDateNewEnd,cashFlowLegCurr.getDayRollSwapConvention(),"");
			}

			date calFixingDate=dateUtil::getBizDate(calDateNewStart,-2,cashFlowLegCurr.getDayRollSwapConvention(),"");
			date calPaymentDate=dateUtil::dayRollAdjust(calDateNewEnd,cashFlowLegCurr.getDayRollSwapConvention(),"");
			cashflow aCashflow(FLiborRate.at(i),notional,  calFixingDate, calPaymentDate,calDateNewStart, calDateNewEnd,cashFlowLegCurr);

			builtCashflowLeg.push_back(aCashflow);
		}
		_cashflowLeg=cashflowLeg(builtCashflowLeg).getCashFlowLeg();
	}

	if (buildDirection==-1) {
		int numOfMonthIncr=12/paymentFreq;
		vector<double> rFLiborRate;
		rFLiborRate.resize(FLiborRate.size());

		copy_backward(FLiborRate.begin(),FLiborRate.end(),rFLiborRate.begin());

		int i=0;
		vector<cashflow> builtCashflowLeg;
		date calDateNewStart=dateUtil::getEndDate(maturityDate,-numOfMonthIncr*i,true);
		while((dateUtil::getBizDaysBetween(startDate,dateUtil::getEndDate(maturityDate,-numOfMonthIncr*(i+1),true))>=0)&&(dateUtil::getBizDaysBetween(startDate,dateUtil::getEndDate(maturityDate,-numOfMonthIncr*i,true))>=0)){
			date calDateNewStart=dateUtil::getEndDate(maturityDate,-numOfMonthIncr*(i+1),true);
			date calDateNewEnd=dateUtil::getEndDate(maturityDate,-numOfMonthIncr*i,true);

			if (rollAccuralDates) {
				calDateNewStart=dateUtil::dayRollAdjust(calDateNewStart,cashFlowLegCurr.getDayRollSwapConvention(),"");
				calDateNewEnd=dateUtil::dayRollAdjust(calDateNewEnd,cashFlowLegCurr.getDayRollSwapConvention(),"");
			}

			date calFixingDate=dateUtil::getBizDate(calDateNewStart,-2,cashFlowLegCurr.getDayRollSwapConvention(),"");
			date calPaymentDate=dateUtil::dayRollAdjust(calDateNewEnd,cashFlowLegCurr.getDayRollSwapConvention(),"");

			cashflow aCashflow(rFLiborRate.at(i),notional,  calFixingDate, calPaymentDate,calDateNewStart, calDateNewEnd,cashFlowLegCurr);

			builtCashflowLeg.insert(builtCashflowLeg.begin(),aCashflow);

			i++;
		}

		if ((dateUtil::getBizDaysBetween(startDate,dateUtil::getEndDate(maturityDate,-numOfMonthIncr*i,true))<0)||(dateUtil::getBizDaysBetween(startDate,dateUtil::getEndDate(maturityDate,-numOfMonthIncr*(i+1),true))<0)) {
			date calDateNewStart=startDate;
			date calDateNewEnd=dateUtil::getEndDate(maturityDate,-numOfMonthIncr*i,true);
			date calFixingDate=dateUtil::getBizDate(calDateNewStart,-2,cashFlowLegCurr.getDayRollSwapConvention(),"");
			date calPaymentDate=dateUtil::dayRollAdjust(calDateNewEnd,cashFlowLegCurr.getDayRollSwapConvention(),"");

			if (rollAccuralDates) {
				calDateNewStart=dateUtil::dayRollAdjust(calDateNewStart,cashFlowLegCurr.getDayRollSwapConvention(),"");
				calDateNewEnd=dateUtil::dayRollAdjust(calDateNewEnd,cashFlowLegCurr.getDayRollSwapConvention(),"");
			}

			cashflow aCashflow(rFLiborRate.at(i),notional,  calFixingDate, calPaymentDate,calDateNewStart, calDateNewEnd,cashFlowLegCurr);

			builtCashflowLeg.insert(builtCashflowLeg.begin(),aCashflow);
		}
		_cashflowLeg=cashflowLeg(builtCashflowLeg).getCashFlowLeg();
	}

}

BuilderCashFlowLeg::BuilderCashFlowLeg(date startDate, int tenorNumOfMonths,vector<double> FLiborRate,double notional, int paymentFreq, currency cashFlowLegCurr,bool rollAccuralDates,RecordHelper::HolidayMap holidayMap) {

	int numOfMonthIncr=12/paymentFreq;
	int i=0;
	vector<cashflow> builtCashflowLeg;

	date calDateNewStart=dateUtil::getEndDate(startDate,numOfMonthIncr*i,true);
	while((numOfMonthIncr*i<=tenorNumOfMonths)&&(numOfMonthIncr*(i+1)<=tenorNumOfMonths)){
		date calDateNewStart=dateUtil::getEndDate(startDate,numOfMonthIncr*i,true);
		date calDateNewEnd=dateUtil::getEndDate(startDate,numOfMonthIncr*(i+1),true);

		if (rollAccuralDates) {
			calDateNewStart=dateUtil::dayRollAdjust(calDateNewStart,cashFlowLegCurr.getDayRollSwapConvention(),"");
			calDateNewEnd=dateUtil::dayRollAdjust(calDateNewEnd,cashFlowLegCurr.getDayRollSwapConvention(),"");
		}
		date calFixingDate=dateUtil::getBizDate(calDateNewStart,-2,cashFlowLegCurr.getDayRollSwapConvention(),"");
		date calPaymentDate=dateUtil::dayRollAdjust(calDateNewEnd,cashFlowLegCurr.getDayRollSwapConvention(),"");

		cashflow aCashflow(FLiborRate.at(i),notional,  calFixingDate, calPaymentDate,calDateNewStart, calDateNewEnd,cashFlowLegCurr);
		builtCashflowLeg.push_back(aCashflow);

		i++;
	}

	if (((numOfMonthIncr*i>tenorNumOfMonths)||(numOfMonthIncr*(i+1)>tenorNumOfMonths))&&(numOfMonthIncr*i!=tenorNumOfMonths)) {
		date calDateNewStart=dateUtil::getEndDate(startDate,numOfMonthIncr*i,true);
		date calDateNewEnd=dateUtil::getEndDate(startDate,tenorNumOfMonths,true);

		if (rollAccuralDates) {
			calDateNewStart=dateUtil::dayRollAdjust(calDateNewStart,cashFlowLegCurr.getDayRollSwapConvention(),"");
			calDateNewEnd=dateUtil::dayRollAdjust(calDateNewEnd,cashFlowLegCurr.getDayRollSwapConvention(),"");
		}

		date calFixingDate=dateUtil::getBizDate(calDateNewStart,-2,cashFlowLegCurr.getDayRollSwapConvention(),"");
		date calPaymentDate=dateUtil::dayRollAdjust(calDateNewEnd,cashFlowLegCurr.getDayRollSwapConvention(),"");
		cashflow aCashflow(FLiborRate.at(i),notional,  calFixingDate, calPaymentDate,calDateNewStart, calDateNewEnd,cashFlowLegCurr);

		builtCashflowLeg.push_back(aCashflow);
	}
	_cashflowLeg=cashflowLeg(builtCashflowLeg).getCashFlowLeg();
}
