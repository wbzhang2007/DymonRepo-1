//created by Jianwei on 30 Nov\

#include "EnumHelper.h"
#include "Enums.h"

using namespace utilities;

enums::MarketEnum EnumHelper::getCcyEnum(std::string ccyName){
	if (ccyName =="EUR")
		return EUR;
	else if (ccyName == "USD")
		return USD;
	else if (ccyName == "THB")
		return THB;
	else if (ccyName == "KRW")
		return KRW;
	else if (ccyName == "SGD")
		return SGD;
	else if (ccyName == "JPY")
		return JPY;
	throw "Market name not foud: "+ccyName;
}

enums::DayRollEnum EnumHelper::getDayRollEnum(std::string dayRoll){
	if (dayRoll =="Following")
		return Following;
	else if (dayRoll == "Preceding")
		return Preceding;
	else if (dayRoll == "Mfollowing")
		return Mfollowing;
	else if (dayRoll == "Mfollowingbi")
		return Mfollowingbi;
	else if (dayRoll == "EOM")
		return EOM;
	else if (dayRoll == "Null")
		return Null;
	throw "Day roll name not foud: "+dayRoll;
}

enums::DayCountEnum EnumHelper::getDayCountEnum(std::string dayCount){
	if (dayCount =="thirty_360US")
		return thirty_360US;
	else if (dayCount == "thirthE_360")
		return thirthE_360;
	else if (dayCount == "ACT_360" || dayCount == "ACT/360")
		return ACT_360;
	else if (dayCount == "ACT_365" || dayCount == "ACT/365")
		return ACT_365;
	else if (dayCount == "ACT_ACT" || dayCount == "ACT/ACT")
		return ACT_ACT;
	else if (dayCount == "BUS_252")
		return BUS_252;
	throw "Day count name not foud: "+dayCount;
}

enums::interpolAlgo EnumHelper::getInterpolAlgo(std::string interpolAlgo){
	if (interpolAlgo == "LINEAR")
		return LINEAR;
	else if ( interpolAlgo == "LOGLINEAR")
		return LOGLINEAR;
	throw "Interpolation algo not foud: "+interpolAlgo;
}

enums::NumericAlgo EnumHelper::getNumericalAlgo(std::string numericalAlgo){
	if (numericalAlgo == "BISECTION")
		return BISECTION;
	else if ( numericalAlgo == "RIDDER")
		return RIDDER;
	else if ( numericalAlgo == "SECANT")
		return SECANT;
	else if ( numericalAlgo == "FALSEPOSITION")
		return FALSEPOSITION;
	throw "Numerical algo not foud: "+numericalAlgo;
}