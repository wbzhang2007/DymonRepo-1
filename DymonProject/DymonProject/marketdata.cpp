//created by Hu Kun 30 Nov 2012
#include "marketdata.h"


using namespace markets;
bool marketdata::instanceFlag = false;
marketdata* marketdata::single = NULL;

marketdata* marketdata::getInstance()
{
	if(! instanceFlag)
	{
		single = new marketdata();
		instanceFlag = true;
		return single;
	}
	else
	{
		return single;
	}
}

marketdata::marketdata(){}


marketdata::~marketdata() {
	delete single;
	delete &price;

	instanceFlag = false;

}

double marketdata::getPrice() {
	return price;
}

void marketdata::setPrice(double aPrice){
	price=aPrice;
}

