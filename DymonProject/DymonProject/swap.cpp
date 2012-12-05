//created by Hu Kun 04 Dec 2012
#include "swap.h"

using namespace instruments;
using namespace utilities;
using namespace std;
using namespace enums;

swap::swap(double notional, double fixLegRate, double floatLegSpread, tuple<double,date,double> floatLegBenchMark,date issueDate, date maturityDate, currency fixLegCurr, currency floatLegCurr) {
	_fixLegRate=fixLegRate;
	_floatLegSpread=floatLegSpread;
	_floatLegBenchMark=floatLegBenchMark;
    _notional=notional;

	_issueDate=issueDate;
	_maturityDate=maturityDate;
	_fixLegCurr=fixLegCurr;
	_floatLegCurr=floatLegCurr;


}

swap::~swap() {

}

double swap::getParRate() {
		
	return 0.0;
}

vector<date> swap::getFloatingFixingDate() {
	//date _issueDate;
	//date _maturityDate;
	
	vector<date> dummy;
	//currency _fixLegCurr;
	//for (i=0;i<=252;i=i+252/_floatLegCurr.paymentFreq) { 
	 //_floatLegCurr.paymentFreq;

	//}
	return dummy;
}

vector<date> swap::getFixLegPaymentDate() {
	vector<date> dummy;

	return dummy;

}

vector<date> swap::getFloatLegPaymentDate() {
	vector<date> dummy;

	return dummy;

}

vector<date> swap::getFloatLegAccuralBeginDate() {
	vector<date> dummy;

	return dummy;

}

double swap::getSwapValue() {

	return 0.0;

}

