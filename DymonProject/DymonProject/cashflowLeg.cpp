//created by Hu Kun 13 Dec

#include "cashflowLeg.h"
#include "cashflow.h"
#include <math.h>
#include <stdio.h>
#include <iterator>
#include <iostream>
#include <sstream>

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

	vector<date> cashflowLeg::getAccuralDates() {
		vector<date> aDates;

		std::vector<cashflow>::iterator itT=_cashflowLeg.begin();
		for (;itT!=_cashflowLeg.end();itT++) {
			cashflow aCF=*itT;
			aDates.push_back(aCF.getAccuralStartDate());
		}

		return aDates;
	}

	void cashflowLeg::printCashFlowLeg() {
		std::vector<cashflow>::iterator itT=_cashflowLeg.begin();

		for (;itT!=_cashflowLeg.end();itT++) {
			cashflow aCF=*itT;

			aCF.printCashFlow();

		}
	}

	void cashflowLeg::printTimeLine() {
		std::stringstream ss (stringstream::in | stringstream::out);
		ss<<"Accrual Time Line: \n";
		std::vector<cashflow>::iterator itT=_cashflowLeg.begin();
		for (;itT!=_cashflowLeg.end();itT++) {
			cashflow aCF=*itT;
			ss<<aCF.getAccuralStartDate().toString()<<"\n";
		}
		cout<<ss.str()<<endl;
	}
}