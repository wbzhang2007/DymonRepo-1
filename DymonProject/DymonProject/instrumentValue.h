//created by Hu Kun on 29 Nov 2012


#include "instrumentBase.h"
#include "currency.h"
#include "date.h"
#include <vector>

namespace models{
template <type T>
class instrumentValue {
	
public:

	instrumentValue(&vector<date> cashFlowDates, &vector<double> cashFlowNotionals, &date issueDate, &date maturityDate );
	~instrumentValue();
	//value the PV of the instrument as of today today
	public double getPV(date tradeDate, date settleDate); 

	//pass the PVs of cashflows to member data cashFlowPv as of today
	public vector<double> getCashFlowPv(date tradeDate, date settleDate); 

	protected vector<double> cashFlowPv;

	private vector<date> cashFlowDates;
	private vector<double> cashFlowNotionals;
	private vector<double> accuralFactors;

};
}