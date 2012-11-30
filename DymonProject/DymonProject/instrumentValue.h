//created by Hu Kun on 29 Nov 2012
#ifndef INSTRUMENTVALUE_H
#define INSTRUMENTVALUE_H
#include "date.h"
#include <vector>

using namespace std;

namespace models{
	template <class T>
	class instrumentValue {
	
	public:

		instrumentValue(vector<utilities::date> cashFlowDates, vector<double> cashFlowNotionals, utilities::date issueDate, utilities::date maturityDate );
		~instrumentValue();
	//value the PV of the instrument as of today today
		double getPV(utilities::date tradeDate, utilities::date settleDate); 

	//pass the PVs of cashflows to member data cashFlowPv as of today
		vector<double> getCashFlowPv(utilities::date tradeDate, utilities::date settleDate); 

	protected:
		vector<double> cashFlowPv;

	private:
		vector<utilities::date> cashFlowDates;
		vector<double> cashFlowNotionals;
		vector<double> accuralFactors;

	};
}
#endif