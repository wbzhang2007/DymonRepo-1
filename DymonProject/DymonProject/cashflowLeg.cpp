//created by Hu Kun 13 Dec

#include "cashflowLeg.h"
#include "cashflow.h"
#include <math.h>
#include <stdio.h>

using namespace utilities;
using namespace std;
using namespace enums;

namespace instruments {
	cashflowLeg::cashflowLeg() {

	}
	cashflowLeg::cashflowLeg(vector<cashflow> cashflowLeg) {
		setCashFlowLeg(cashflowLeg);
	}
	cashflowLeg::~cashflowLeg() {

	}
		
	vector<cashflow> cashflowLeg::getCashFlowVector() {
		return _cashflowLeg;
	}
	
	cashflowLeg cashflowLeg::getCashFlowLeg() {
		return _cashflowLeg;
	}
	void cashflowLeg::setCashFlowLeg(vector<cashflow> cashflowLeg) {
		_cashflowLeg=cashflowLeg;
	}
	
}