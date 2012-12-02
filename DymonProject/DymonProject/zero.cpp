//created by Hu Kun 1 Dec 2012
#include "dateUtil.h"
#include "date.h"
#include "zero.h"
#include <math.h>
#include "instrumentBase.h"

using namespace utilities;

namespace instruments {
zero::zero() {};
zero::zero(double aSpotRate,double aNotional,date aMaturityDate,date aIssueDate) {
	spotRate=aSpotRate;
	notional=aNotional;
	maturityDate=aMaturityDate;
	price=getPrice(aSpotRate,aNotional,aMaturityDate,aIssueDate);
	issueDate=aIssueDate;

}

zero::~zero() {
	delete &price;
	delete &spotRate;
	delete &notional;
	delete &maturityDate;
	delete &issueDate;

}

double zero::getPrice(double spotRate,double notional,date maturityDate, date issueDate){
	return 0;
}

double zero::getImpliedSpotRate(double price,double notional,date maturityDate, date issueDate) {

	return 0;
}

date zero::getIssueDate() {
	return issueDate;

}

date zero::getMaturityDate() {
	return maturityDate;
}

void zero::setIssueDate(date aIssueDate) {
	issueDate=aIssueDate;

}

void zero::setMaturityDate(date aMaturityDate){
	maturityDate=aMaturityDate;
}
}