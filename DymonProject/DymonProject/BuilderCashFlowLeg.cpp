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

BuilderCashFlowLeg::BuilderCashFlowLeg(date startDate, date maturityDate,double couponRate,double notional, int paymentFreq, enums::CurrencyEnum market, int buildDirection){

	currency mkt(market);
	enums::DayCountEnum dayCountSwapConvention = mkt.getDayCountSwapConvention();
	enums::DayRollEnum dayRollSwapConvention = mkt.getDayRollSwapConvention();
	enums::DayRollEnum accrualAdjustSwapConvention = mkt.getAccrualAdjustSwapConvention();

	if (buildDirection==1) {
		int numOfMonthIncr=12/paymentFreq;
		int i=0;
		vector<cashflow> builtCashflowLeg;
		while((dateUtil::getBizDaysBetween(dateUtil::getEndDate(startDate,numOfMonthIncr*i,Null,market,dateUtil::MONTH),maturityDate)>=0)&&
			(dateUtil::getBizDaysBetween(dateUtil::getEndDate(startDate,numOfMonthIncr*(i+1),Null,market,dateUtil::MONTH),maturityDate)>=0)){
			date calDateNewStart=dateUtil::getEndDate(startDate,numOfMonthIncr*i,accrualAdjustSwapConvention,market,dateUtil::MONTH);
			date calDateNewEnd=dateUtil::getEndDate(startDate,numOfMonthIncr*(i+1),accrualAdjustSwapConvention,market,dateUtil::MONTH);			
			date calFixingDate=dateUtil::getBizDateOffSet(calDateNewStart,-2,market);
			date calPaymentDate=dateUtil::dayRollAdjust(calDateNewEnd,dayRollSwapConvention,market);

			cashflow aCashflow(couponRate,notional,  calFixingDate, calPaymentDate,calDateNewStart, calDateNewEnd,market);
			builtCashflowLeg.push_back(aCashflow);

			i++;
		}

		if ((dateUtil::getBizDaysBetween(dateUtil::getEndDate(startDate,numOfMonthIncr*i,Null,market,dateUtil::MONTH),maturityDate)<0)
			||(dateUtil::getBizDaysBetween(dateUtil::getEndDate(startDate,numOfMonthIncr*(i+1),Null,market,dateUtil::MONTH),maturityDate)<0)) {

			date calDateNewStart=dateUtil::getEndDate(startDate,numOfMonthIncr*i,accrualAdjustSwapConvention,market,dateUtil::MONTH);
			date calDateNewEnd=dateUtil::dayRollAdjust(maturityDate,accrualAdjustSwapConvention,market);
			date calFixingDate=dateUtil::getBizDateOffSet(calDateNewStart,-2,market);
			date calPaymentDate=dateUtil::dayRollAdjust(calDateNewEnd,dayRollSwapConvention,market);

			cashflow aCashflow(couponRate,notional,calFixingDate,calPaymentDate,calDateNewStart,calDateNewEnd,market);
			builtCashflowLeg.push_back(aCashflow);
		}
		_cashflowLeg=cashflowLeg(builtCashflowLeg).getCashFlowLeg();
	}

	if (buildDirection==-1) {
		int numOfMonthIncr=12/paymentFreq;
		int i=0;
		vector<cashflow> builtCashflowLeg;

		while((dateUtil::getBizDaysBetween(startDate,dateUtil::getEndDate(maturityDate,-numOfMonthIncr*(i+1),Null,market,dateUtil::MONTH))>=0)&&
			(dateUtil::getBizDaysBetween(startDate,dateUtil::getEndDate(maturityDate,-numOfMonthIncr*i,Null,market,dateUtil::MONTH))>=0)){

			date calDateNewStart=dateUtil::getEndDate(maturityDate,-numOfMonthIncr*(i+1),accrualAdjustSwapConvention,market,dateUtil::MONTH);
			date calDateNewEnd=dateUtil::getEndDate(maturityDate,-numOfMonthIncr*i,accrualAdjustSwapConvention,market,dateUtil::MONTH);
			date calFixingDate=dateUtil::getBizDateOffSet(calDateNewStart,-2,market);
			date calPaymentDate=dateUtil::dayRollAdjust(calDateNewEnd,dayRollSwapConvention,market);

			cashflow aCashflow(couponRate,notional,  calFixingDate, calPaymentDate,calDateNewStart, calDateNewEnd,market);
			builtCashflowLeg.insert(builtCashflowLeg.begin(),aCashflow);
			i++;
		}

		if ((dateUtil::getBizDaysBetween(startDate,dateUtil::getEndDate(maturityDate,-numOfMonthIncr*i,Null,market,dateUtil::MONTH))<0)||
			(dateUtil::getBizDaysBetween(startDate,dateUtil::getEndDate(maturityDate,-numOfMonthIncr*(i+1),Null,market,dateUtil::MONTH))<0)) {

			date calDateNewStart=dateUtil::dayRollAdjust(startDate,accrualAdjustSwapConvention,market);
			date calDateNewEnd=dateUtil::getEndDate(maturityDate,-numOfMonthIncr*i,accrualAdjustSwapConvention,market,dateUtil::MONTH);
			date calFixingDate=dateUtil::getBizDateOffSet(calDateNewStart,-2,market);
			date calPaymentDate=dateUtil::dayRollAdjust(calDateNewEnd,dayRollSwapConvention,market);

			cashflow aCashflow(couponRate,notional,  calFixingDate, calPaymentDate,calDateNewStart, calDateNewEnd,market);
			builtCashflowLeg.insert(builtCashflowLeg.begin(),aCashflow);
		}
		_cashflowLeg=cashflowLeg(builtCashflowLeg).getCashFlowLeg();
	}

}

BuilderCashFlowLeg::BuilderCashFlowLeg(date startDate, int tenorNumOfMonths,double couponRate,double notional, int paymentFreq, enums::CurrencyEnum market){

	currency mkt(market);
	enums::DayCountEnum dayCountSwapConvention = mkt.getDayCountSwapConvention();
	enums::DayRollEnum dayRollSwapConvention = mkt.getDayRollSwapConvention();
	enums::DayRollEnum accrualAdjustSwapConvention = mkt.getAccrualAdjustSwapConvention();

	int numOfMonthIncr=12/paymentFreq;
	int i=0;
	vector<cashflow> builtCashflowLeg;

	while((numOfMonthIncr*i<=tenorNumOfMonths)&&(numOfMonthIncr*(i+1)<=tenorNumOfMonths)){

		date calDateNewStart=dateUtil::getEndDate(startDate,numOfMonthIncr*i,accrualAdjustSwapConvention,market,dateUtil::MONTH);
		date calDateNewEnd=dateUtil::getEndDate(startDate,numOfMonthIncr*(i+1),accrualAdjustSwapConvention,market,dateUtil::MONTH);			
		date calFixingDate=dateUtil::getBizDateOffSet(calDateNewStart,-2,market);
		date calPaymentDate=dateUtil::dayRollAdjust(calDateNewEnd,dayRollSwapConvention,market);

		cashflow aCashflow(couponRate,notional,  calFixingDate, calPaymentDate,calDateNewStart, calDateNewEnd,market);
		builtCashflowLeg.push_back(aCashflow);
		i++;
	}

	if (((numOfMonthIncr*i>tenorNumOfMonths)||(numOfMonthIncr*(i+1)>tenorNumOfMonths))&&(numOfMonthIncr*i!=tenorNumOfMonths)) {

		date calDateNewStart=dateUtil::getEndDate(startDate,numOfMonthIncr*i,accrualAdjustSwapConvention,market,dateUtil::MONTH);
		date calDateNewEnd=dateUtil::getEndDate(startDate,tenorNumOfMonths,accrualAdjustSwapConvention,market,dateUtil::MONTH);

		date calFixingDate=dateUtil::getBizDateOffSet(calDateNewStart,-2,market);
		date calPaymentDate=dateUtil::dayRollAdjust(calDateNewEnd,dayRollSwapConvention,market);
		cashflow aCashflow(couponRate,notional,  calFixingDate, calPaymentDate,calDateNewStart, calDateNewEnd,market);

		builtCashflowLeg.push_back(aCashflow);
	}
	_cashflowLeg=cashflowLeg(builtCashflowLeg).getCashFlowLeg();
}

BuilderCashFlowLeg::BuilderCashFlowLeg(date startDate, date maturityDate,vector<double> FLiborRate,double notional, int paymentFreq, enums::CurrencyEnum market, int buildDirection){

	currency mkt(market);
	enums::DayCountEnum dayCountSwapConvention = mkt.getDayCountSwapConvention();
	enums::DayRollEnum dayRollSwapConvention = mkt.getDayRollSwapConvention();
	enums::DayRollEnum accrualAdjustSwapConvention = mkt.getAccrualAdjustSwapConvention();

	if (buildDirection==1) {
		int numOfMonthIncr=12/paymentFreq;
		int i=0;
		vector<cashflow> builtCashflowLeg;
		while((dateUtil::getBizDaysBetween(dateUtil::getEndDate(startDate,numOfMonthIncr*i,Null,market,dateUtil::MONTH),maturityDate)>=0)&&
			(dateUtil::getBizDaysBetween(dateUtil::getEndDate(startDate,numOfMonthIncr*(i+1),Null,market,dateUtil::MONTH),maturityDate)>=0)){

			date calDateNewStart=dateUtil::getEndDate(startDate,numOfMonthIncr*i,accrualAdjustSwapConvention,market,dateUtil::MONTH);
			date calDateNewEnd=dateUtil::getEndDate(startDate,numOfMonthIncr*(i+1),accrualAdjustSwapConvention,market,dateUtil::MONTH);			
			date calFixingDate=dateUtil::getBizDateOffSet(calDateNewStart,-2,market);
			date calPaymentDate=dateUtil::dayRollAdjust(calDateNewEnd,dayRollSwapConvention,market);

			cashflow aCashflow(FLiborRate.at(i),notional,  calFixingDate, calPaymentDate,calDateNewStart, calDateNewEnd,market);
			builtCashflowLeg.push_back(aCashflow);

			i++;
		}

		if ((dateUtil::getBizDaysBetween(dateUtil::getEndDate(startDate,numOfMonthIncr*i,Null,market,dateUtil::MONTH),maturityDate)<0)
			||(dateUtil::getBizDaysBetween(dateUtil::getEndDate(startDate,numOfMonthIncr*(i+1),Null,market,dateUtil::MONTH),maturityDate)<0)) {
			
			date calDateNewStart=dateUtil::getEndDate(startDate,numOfMonthIncr*i,accrualAdjustSwapConvention,market,dateUtil::MONTH);
			date calDateNewEnd=dateUtil::dayRollAdjust(maturityDate,accrualAdjustSwapConvention,market);
			date calFixingDate=dateUtil::getBizDateOffSet(calDateNewStart,-2,market);
			date calPaymentDate=dateUtil::dayRollAdjust(calDateNewEnd,dayRollSwapConvention,market);

			cashflow aCashflow(FLiborRate.at(i),notional,  calFixingDate, calPaymentDate,calDateNewStart, calDateNewEnd,market);
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
			
		while((dateUtil::getBizDaysBetween(startDate,dateUtil::getEndDate(maturityDate,-numOfMonthIncr*(i+1),Null,market,dateUtil::MONTH))>=0)&&
			(dateUtil::getBizDaysBetween(startDate,dateUtil::getEndDate(maturityDate,-numOfMonthIncr*i,Null,market,dateUtil::MONTH))>=0)){

			date calDateNewStart=dateUtil::getEndDate(maturityDate,-numOfMonthIncr*(i+1),accrualAdjustSwapConvention,market,dateUtil::MONTH);
			date calDateNewEnd=dateUtil::getEndDate(maturityDate,-numOfMonthIncr*i,accrualAdjustSwapConvention,market,dateUtil::MONTH);
			date calFixingDate=dateUtil::getBizDateOffSet(calDateNewStart,-2,market);
			date calPaymentDate=dateUtil::dayRollAdjust(calDateNewEnd,dayRollSwapConvention,market);

			cashflow aCashflow(rFLiborRate.at(i),notional,  calFixingDate, calPaymentDate,calDateNewStart, calDateNewEnd,market);
			builtCashflowLeg.insert(builtCashflowLeg.begin(),aCashflow);
			i++;
		}

		if ((dateUtil::getBizDaysBetween(startDate,dateUtil::getEndDate(maturityDate,-numOfMonthIncr*i,Null,market,dateUtil::MONTH))<0)||
			(dateUtil::getBizDaysBetween(startDate,dateUtil::getEndDate(maturityDate,-numOfMonthIncr*(i+1),Null,market,dateUtil::MONTH))<0)) {

			date calDateNewStart=dateUtil::dayRollAdjust(startDate,accrualAdjustSwapConvention,market);
			date calDateNewEnd=dateUtil::getEndDate(maturityDate,-numOfMonthIncr*i,accrualAdjustSwapConvention,market,dateUtil::MONTH);
			date calFixingDate=dateUtil::getBizDateOffSet(calDateNewStart,-2,market);
			date calPaymentDate=dateUtil::dayRollAdjust(calDateNewEnd,dayRollSwapConvention,market);

			cashflow aCashflow(rFLiborRate.at(i),notional,  calFixingDate, calPaymentDate,calDateNewStart, calDateNewEnd, market);
			builtCashflowLeg.insert(builtCashflowLeg.begin(),aCashflow);
		}
		_cashflowLeg=cashflowLeg(builtCashflowLeg).getCashFlowLeg();
	}

}

BuilderCashFlowLeg::BuilderCashFlowLeg(date startDate, int tenorNumOfMonths,vector<double> FLiborRate,double notional, int paymentFreq, enums::CurrencyEnum market){
	
	currency mkt(market);
	enums::DayCountEnum dayCountSwapConvention = mkt.getDayCountSwapConvention();
	enums::DayRollEnum dayRollSwapConvention = mkt.getDayRollSwapConvention();
	enums::DayRollEnum accrualAdjustSwapConvention = mkt.getAccrualAdjustSwapConvention();

	int numOfMonthIncr=12/paymentFreq;
	int i=0;
	vector<cashflow> builtCashflowLeg;

	while((numOfMonthIncr*i<=tenorNumOfMonths)&&(numOfMonthIncr*(i+1)<=tenorNumOfMonths)){

		date calDateNewStart=dateUtil::getEndDate(startDate,numOfMonthIncr*i,accrualAdjustSwapConvention,market,dateUtil::MONTH);
		date calDateNewEnd=dateUtil::getEndDate(startDate,numOfMonthIncr*(i+1),accrualAdjustSwapConvention,market,dateUtil::MONTH);			
		date calFixingDate=dateUtil::getBizDateOffSet(calDateNewStart,-2,market);
		date calPaymentDate=dateUtil::dayRollAdjust(calDateNewEnd,dayRollSwapConvention,market);

		cashflow aCashflow(FLiborRate.at(i),notional,  calFixingDate, calPaymentDate,calDateNewStart, calDateNewEnd,market);
		builtCashflowLeg.push_back(aCashflow);
		i++;
	}

	if (((numOfMonthIncr*i>tenorNumOfMonths)||(numOfMonthIncr*(i+1)>tenorNumOfMonths))&&(numOfMonthIncr*i!=tenorNumOfMonths)) {

		date calDateNewStart=dateUtil::getEndDate(startDate,numOfMonthIncr*i,accrualAdjustSwapConvention,market,dateUtil::MONTH);
		date calDateNewEnd=dateUtil::getEndDate(startDate,tenorNumOfMonths,accrualAdjustSwapConvention,market,dateUtil::MONTH);
		date calFixingDate=dateUtil::getBizDateOffSet(calDateNewStart,-2,market);
		date calPaymentDate=dateUtil::dayRollAdjust(calDateNewEnd,dayRollSwapConvention,market);

		cashflow aCashflow(FLiborRate.at(i),notional,  calFixingDate, calPaymentDate,calDateNewStart, calDateNewEnd,market);
		builtCashflowLeg.push_back(aCashflow);
	}
	_cashflowLeg=cashflowLeg(builtCashflowLeg).getCashFlowLeg();
}
