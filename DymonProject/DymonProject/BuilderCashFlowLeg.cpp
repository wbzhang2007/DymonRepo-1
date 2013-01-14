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
#include "DiscountCurve.h"
#include "Market.h"

using namespace Session;
using namespace utilities;
using namespace std;
using namespace enums;

using namespace instruments;

BuilderCashFlowLeg::BuilderCashFlowLeg(date accrualStartDate, date accrualEndDate,double couponRate,double notional, int paymentFreq, enums::MarketEnum market, int buildDirection){
	
	Market mkt(market);
	enums::DayCountEnum dayCountSwapConvention = mkt.getDayCountSwapConvention();
	enums::DayRollEnum dayRollSwapConvention = mkt.getDayRollSwapConvention();
	enums::DayRollEnum accrualAdjustSwapConvention = mkt.getAccrualAdjustSwapConvention();
	accrualStartDate = dateUtil::getBizDateOffSet(accrualStartDate,mkt.getBusinessDaysAfterSpot(),market);

	if (buildDirection==1) {
		int numOfMonthIncr=12/paymentFreq;
		int i=0;
		vector<cashflow> builtCashflowLeg;
		while((dateUtil::getBizDaysBetween(dateUtil::getEndDate(accrualStartDate,numOfMonthIncr*i,accrualAdjustSwapConvention,market,dateUtil::MONTH),accrualEndDate)>0)&&
			(dateUtil::getBizDaysBetween(dateUtil::getEndDate(accrualStartDate,numOfMonthIncr*(i+1),accrualAdjustSwapConvention,market,dateUtil::MONTH),accrualEndDate)>=0)){
			date calDateNewStart=dateUtil::getEndDate(accrualStartDate,numOfMonthIncr*i,accrualAdjustSwapConvention,market,dateUtil::MONTH);
			date calDateNewEnd=dateUtil::getEndDate(accrualStartDate,numOfMonthIncr*(i+1),accrualAdjustSwapConvention,market,dateUtil::MONTH);			
			date calFixingDate=dateUtil::getBizDateOffSet(calDateNewStart,-mkt.getBusinessDaysAfterSpot(),market);
			date calPaymentDate=dateUtil::dayRollAdjust(calDateNewEnd,dayRollSwapConvention,market);

			cashflow aCashflow(couponRate,notional,calFixingDate,calPaymentDate,calDateNewStart, calDateNewEnd,market);
			builtCashflowLeg.push_back(aCashflow);
			i++;
		}

		if ((dateUtil::getBizDaysBetween(dateUtil::getEndDate(accrualStartDate,numOfMonthIncr*(i-1),accrualAdjustSwapConvention,market,dateUtil::MONTH),accrualEndDate)<0)
			||(dateUtil::getBizDaysBetween(dateUtil::getEndDate(accrualStartDate,numOfMonthIncr*i,accrualAdjustSwapConvention,market,dateUtil::MONTH),accrualEndDate)<0)) {

			date calDateNewStart=dateUtil::getEndDate(accrualStartDate,numOfMonthIncr*i,accrualAdjustSwapConvention,market,dateUtil::MONTH);
			date calDateNewEnd=dateUtil::dayRollAdjust(accrualEndDate,accrualAdjustSwapConvention,market);
			date calFixingDate=dateUtil::getBizDateOffSet(calDateNewStart,-mkt.getBusinessDaysAfterSpot(),market);
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

		while((dateUtil::getBizDaysBetween(accrualStartDate,dateUtil::getEndDate(accrualEndDate,-numOfMonthIncr*(i+1),accrualAdjustSwapConvention,market,dateUtil::MONTH))>0)&&
			(dateUtil::getBizDaysBetween(accrualStartDate,dateUtil::getEndDate(accrualEndDate,-numOfMonthIncr*i,accrualAdjustSwapConvention,market,dateUtil::MONTH))>=0)){

			date calDateNewStart=dateUtil::getEndDate(accrualEndDate,-numOfMonthIncr*(i+1),accrualAdjustSwapConvention,market,dateUtil::MONTH);
			date calDateNewEnd=dateUtil::getEndDate(accrualEndDate,-numOfMonthIncr*i,accrualAdjustSwapConvention,market,dateUtil::MONTH);
			date calFixingDate=dateUtil::getBizDateOffSet(calDateNewStart,-mkt.getBusinessDaysAfterSpot(),market);
			date calPaymentDate=dateUtil::dayRollAdjust(calDateNewEnd,dayRollSwapConvention,market);

			cashflow aCashflow(couponRate,notional,  calFixingDate, calPaymentDate,calDateNewStart, calDateNewEnd,market);
			builtCashflowLeg.insert(builtCashflowLeg.begin(),aCashflow);
			i++;
		}

		if ((dateUtil::getBizDaysBetween(accrualStartDate,dateUtil::getEndDate(accrualEndDate,-numOfMonthIncr*(i-1),accrualAdjustSwapConvention,market,dateUtil::MONTH))<0)||
			(dateUtil::getBizDaysBetween(accrualStartDate,dateUtil::getEndDate(accrualEndDate,-numOfMonthIncr*i,accrualAdjustSwapConvention,market,dateUtil::MONTH))<0)) {

			date calDateNewStart=dateUtil::dayRollAdjust(accrualStartDate,accrualAdjustSwapConvention,market);
			date calDateNewEnd=dateUtil::getEndDate(accrualEndDate,-numOfMonthIncr*i,accrualAdjustSwapConvention,market,dateUtil::MONTH);
			date calFixingDate=dateUtil::getBizDateOffSet(calDateNewStart,-mkt.getBusinessDaysAfterSpot(),market);
			date calPaymentDate=dateUtil::dayRollAdjust(calDateNewEnd,dayRollSwapConvention,market);

			cashflow aCashflow(couponRate,notional,  calFixingDate, calPaymentDate,calDateNewStart, calDateNewEnd,market);
			builtCashflowLeg.insert(builtCashflowLeg.begin(),aCashflow);
		}
		_cashflowLeg=cashflowLeg(builtCashflowLeg).getCashFlowLeg();
	}
}

BuilderCashFlowLeg::BuilderCashFlowLeg(date accrualStartDate, int tenorNumOfMonths,double couponRate,double notional, int paymentFreq, enums::MarketEnum market){

	Market mkt(market);
	enums::DayCountEnum dayCountSwapConvention = mkt.getDayCountSwapConvention();
	enums::DayRollEnum dayRollSwapConvention = mkt.getDayRollSwapConvention();
	enums::DayRollEnum accrualAdjustSwapConvention = mkt.getAccrualAdjustSwapConvention();
	accrualStartDate = dateUtil::getBizDateOffSet(accrualStartDate,mkt.getBusinessDaysAfterSpot(),market);

	int numOfMonthIncr=12/paymentFreq;
	int i=0;
	vector<cashflow> builtCashflowLeg;

	while((numOfMonthIncr*i<tenorNumOfMonths)&&(numOfMonthIncr*(i+1)<=tenorNumOfMonths)){

		date calDateNewStart=dateUtil::getEndDate(accrualStartDate,numOfMonthIncr*i,accrualAdjustSwapConvention,market,dateUtil::MONTH);
		date calDateNewEnd=dateUtil::getEndDate(accrualStartDate,numOfMonthIncr*(i+1),accrualAdjustSwapConvention,market,dateUtil::MONTH);			
		date calFixingDate=dateUtil::getBizDateOffSet(calDateNewStart,-mkt.getBusinessDaysAfterSpot(),market);
		date calPaymentDate=dateUtil::dayRollAdjust(calDateNewEnd,dayRollSwapConvention,market);

		cashflow aCashflow(couponRate,notional,  calFixingDate, calPaymentDate,calDateNewStart, calDateNewEnd,market);
		builtCashflowLeg.push_back(aCashflow);
		i++;
	}

	if ((numOfMonthIncr*(i-1)>tenorNumOfMonths)||(numOfMonthIncr*(i)>tenorNumOfMonths)) {

		date calDateNewStart=dateUtil::getEndDate(accrualStartDate,numOfMonthIncr*i,accrualAdjustSwapConvention,market,dateUtil::MONTH);
		date calDateNewEnd=dateUtil::getEndDate(accrualStartDate,tenorNumOfMonths,accrualAdjustSwapConvention,market,dateUtil::MONTH);

		date calFixingDate=dateUtil::getBizDateOffSet(calDateNewStart,-mkt.getBusinessDaysAfterSpot(),market);
		date calPaymentDate=dateUtil::dayRollAdjust(calDateNewEnd,dayRollSwapConvention,market);
		cashflow aCashflow(couponRate,notional,  calFixingDate, calPaymentDate,calDateNewStart, calDateNewEnd,market);

		builtCashflowLeg.push_back(aCashflow);
	}
	_cashflowLeg=cashflowLeg(builtCashflowLeg).getCashFlowLeg();
}

BuilderCashFlowLeg::BuilderCashFlowLeg(date accrualStartDate, date accrualEndDate,DiscountCurve* yc,double notional, int paymentFreq, enums::MarketEnum market, int buildDirection){

	Market mkt(market);
	enums::DayCountEnum dayCountSwapConvention = mkt.getDayCountSwapConvention();
	enums::DayRollEnum dayRollSwapConvention = mkt.getDayRollSwapConvention();
	enums::DayRollEnum accrualAdjustSwapConvention = mkt.getAccrualAdjustSwapConvention();
	accrualStartDate = dateUtil::getBizDateOffSet(accrualStartDate,mkt.getBusinessDaysAfterSpot(),market);

	if (buildDirection==1) {
		int numOfMonthIncr=12/paymentFreq;
		int i=0;
		vector<cashflow> builtCashflowLeg;
		while((dateUtil::getBizDaysBetween(dateUtil::getEndDate(accrualStartDate,numOfMonthIncr*i,accrualAdjustSwapConvention,market,dateUtil::MONTH),accrualEndDate)>0)&&
			(dateUtil::getBizDaysBetween(dateUtil::getEndDate(accrualStartDate,numOfMonthIncr*(i+1),accrualAdjustSwapConvention,market,dateUtil::MONTH),accrualEndDate)>=0)){

			date calDateNewStart=dateUtil::getEndDate(accrualStartDate,numOfMonthIncr*i,accrualAdjustSwapConvention,market,dateUtil::MONTH);
			date calDateNewEnd=dateUtil::getEndDate(accrualStartDate,numOfMonthIncr*(i+1),accrualAdjustSwapConvention,market,dateUtil::MONTH);			
			date calFixingDate=dateUtil::getBizDateOffSet(calDateNewStart,-mkt.getBusinessDaysAfterSpot(),market);
			date calPaymentDate=dateUtil::dayRollAdjust(calDateNewEnd,dayRollSwapConvention,market);

			double FLiborRate=yc->getFLiborRate(calDateNewStart,calDateNewEnd,mkt.getDayCountSwapConvention());
			cashflow aCashflow(FLiborRate,notional, calFixingDate, calPaymentDate,calDateNewStart, calDateNewEnd,market);
			builtCashflowLeg.push_back(aCashflow);
			i++;
		}

		if ((dateUtil::getBizDaysBetween(dateUtil::getEndDate(accrualStartDate,numOfMonthIncr*(i-1),accrualAdjustSwapConvention,market,dateUtil::MONTH),accrualEndDate)<0)
			||(dateUtil::getBizDaysBetween(dateUtil::getEndDate(accrualStartDate,numOfMonthIncr*i,accrualAdjustSwapConvention,market,dateUtil::MONTH),accrualEndDate)<0)) {
			
			date calDateNewStart=dateUtil::getEndDate(accrualStartDate,numOfMonthIncr*i,accrualAdjustSwapConvention,market,dateUtil::MONTH);
			date calDateNewEnd=dateUtil::dayRollAdjust(accrualEndDate,accrualAdjustSwapConvention,market);
			date calFixingDate=dateUtil::getBizDateOffSet(calDateNewStart,-mkt.getBusinessDaysAfterSpot(),market);
			date calPaymentDate=dateUtil::dayRollAdjust(calDateNewEnd,dayRollSwapConvention,market);

			double FLiborRate=yc->getFLiborRate(calDateNewStart,calDateNewEnd,mkt.getDayCountSwapConvention());
			cashflow aCashflow(FLiborRate,notional,  calFixingDate, calPaymentDate,calDateNewStart, calDateNewEnd,market);
			builtCashflowLeg.push_back(aCashflow);
		}
		_cashflowLeg=cashflowLeg(builtCashflowLeg).getCashFlowLeg();
	}

	if (buildDirection==-1) {
		int numOfMonthIncr=12/paymentFreq;
		
		//copy_backward(FLiborRate.begin(),FLiborRate.end(),rFLiborRate.begin());

		int i=0;
		vector<cashflow> builtCashflowLeg;
			
		while((dateUtil::getBizDaysBetween(accrualStartDate,dateUtil::getEndDate(accrualEndDate,-numOfMonthIncr*(i+1),accrualAdjustSwapConvention,market,dateUtil::MONTH))>0)&&
			(dateUtil::getBizDaysBetween(accrualStartDate,dateUtil::getEndDate(accrualEndDate,-numOfMonthIncr*i,accrualAdjustSwapConvention,market,dateUtil::MONTH))>=0)){

			date calDateNewStart=dateUtil::getEndDate(accrualEndDate,-numOfMonthIncr*(i+1),accrualAdjustSwapConvention,market,dateUtil::MONTH);
			date calDateNewEnd=dateUtil::getEndDate(accrualEndDate,-numOfMonthIncr*i,accrualAdjustSwapConvention,market,dateUtil::MONTH);
			date calFixingDate=dateUtil::getBizDateOffSet(calDateNewStart,-mkt.getBusinessDaysAfterSpot(),market);
			date calPaymentDate=dateUtil::dayRollAdjust(calDateNewEnd,dayRollSwapConvention,market);

			double FLiborRate=yc->getFLiborRate(calDateNewStart,calDateNewEnd,mkt.getDayCountSwapConvention());
			cashflow aCashflow(FLiborRate,notional,  calFixingDate, calPaymentDate,calDateNewStart, calDateNewEnd,market);
			builtCashflowLeg.insert(builtCashflowLeg.begin(),aCashflow);
			i++;
		}

		if ((dateUtil::getBizDaysBetween(accrualStartDate,dateUtil::getEndDate(accrualEndDate,-numOfMonthIncr*(i-1),accrualAdjustSwapConvention,market,dateUtil::MONTH))<0)||
			(dateUtil::getBizDaysBetween(accrualStartDate,dateUtil::getEndDate(accrualEndDate,-numOfMonthIncr*i,accrualAdjustSwapConvention,market,dateUtil::MONTH))<0)) {

			date calDateNewStart=dateUtil::dayRollAdjust(accrualStartDate,accrualAdjustSwapConvention,market);
			date calDateNewEnd=dateUtil::getEndDate(accrualEndDate,-numOfMonthIncr*i,accrualAdjustSwapConvention,market,dateUtil::MONTH);
			date calFixingDate=dateUtil::getBizDateOffSet(calDateNewStart,-mkt.getBusinessDaysAfterSpot(),market);
			date calPaymentDate=dateUtil::dayRollAdjust(calDateNewEnd,dayRollSwapConvention,market);

			double FLiborRate=yc->getFLiborRate(calDateNewStart,calDateNewEnd,mkt.getDayCountSwapConvention());
			cashflow aCashflow(FLiborRate,notional,  calFixingDate, calPaymentDate,calDateNewStart, calDateNewEnd, market);
			builtCashflowLeg.insert(builtCashflowLeg.begin(),aCashflow);
		}
		_cashflowLeg=cashflowLeg(builtCashflowLeg).getCashFlowLeg();
	}
}

BuilderCashFlowLeg::BuilderCashFlowLeg(date accrualStartDate, int tenorNumOfMonths,DiscountCurve* yc,double notional, int paymentFreq, enums::MarketEnum market){
	
	Market mkt(market);
	enums::DayCountEnum dayCountSwapConvention = mkt.getDayCountSwapConvention();
	enums::DayRollEnum dayRollSwapConvention = mkt.getDayRollSwapConvention();
	enums::DayRollEnum accrualAdjustSwapConvention = mkt.getAccrualAdjustSwapConvention();
	accrualStartDate = dateUtil::getBizDateOffSet(accrualStartDate,mkt.getBusinessDaysAfterSpot(),market);

	int numOfMonthIncr=12/paymentFreq;
	int i=0;
	vector<cashflow> builtCashflowLeg;

	while((numOfMonthIncr*i<tenorNumOfMonths)&&(numOfMonthIncr*(i+1)<=tenorNumOfMonths)){

		date calDateNewStart=dateUtil::getEndDate(accrualStartDate,numOfMonthIncr*i,accrualAdjustSwapConvention,market,dateUtil::MONTH);
		date calDateNewEnd=dateUtil::getEndDate(accrualStartDate,numOfMonthIncr*(i+1),accrualAdjustSwapConvention,market,dateUtil::MONTH);			
		date calFixingDate=dateUtil::getBizDateOffSet(calDateNewStart,-mkt.getBusinessDaysAfterSpot(),market);
		date calPaymentDate=dateUtil::dayRollAdjust(calDateNewEnd,dayRollSwapConvention,market);

		double FLiborRate=yc->getFLiborRate(calDateNewStart,calDateNewEnd,mkt.getDayCountSwapConvention());
		cashflow aCashflow(FLiborRate,notional,  calFixingDate, calPaymentDate,calDateNewStart, calDateNewEnd,market);
		builtCashflowLeg.push_back(aCashflow);
		i++;
	}

	if ((numOfMonthIncr*(i-1)>tenorNumOfMonths)||(numOfMonthIncr*i>tenorNumOfMonths)) {

		date calDateNewStart=dateUtil::getEndDate(accrualStartDate,numOfMonthIncr*i,accrualAdjustSwapConvention,market,dateUtil::MONTH);
		date calDateNewEnd=dateUtil::getEndDate(accrualStartDate,tenorNumOfMonths,accrualAdjustSwapConvention,market,dateUtil::MONTH);
		date calFixingDate=dateUtil::getBizDateOffSet(calDateNewStart,-mkt.getBusinessDaysAfterSpot(),market);
		date calPaymentDate=dateUtil::dayRollAdjust(calDateNewEnd,dayRollSwapConvention,market);

		double FLiborRate=yc->getFLiborRate(calDateNewStart,calDateNewEnd,mkt.getDayCountSwapConvention());
		cashflow aCashflow(FLiborRate,notional,  calFixingDate, calPaymentDate,calDateNewStart, calDateNewEnd,market);
		builtCashflowLeg.push_back(aCashflow);
	}
	_cashflowLeg=cashflowLeg(builtCashflowLeg).getCashFlowLeg();
}
