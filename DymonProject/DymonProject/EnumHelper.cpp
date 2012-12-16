//created by Jianwei on 30 Nov\

#include "EnumHelper.h"
#include "Enums.h"

enums::CurrencyEnum getCcyEnum(std::string ccyName){
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
	throw "Currency name not foud: "+ccyName;
}

enums::DayRollEnum getDayRollEnum(std::string dayRoll){
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
	throw "Day roll name not foud: "+dayRoll;
}

enums::DayCountEnum getDayCountEnum(std::string dayCount){
	if (dayCount =="thirty_360US")
		return thirty_360US;
	else if (dayCount == "thirthE_360")
		return thirthE_360;
	else if (dayCount == "ACT_360")
		return ACT_360;
	else if (dayCount == "ACT_365")
		return ACT_365;
	else if (dayCount == "ACT_ACT")
		return ACT_ACT;
	else if (dayCount == "BUS_252")
		return BUS_252;
	throw "Day count name not foud: "+dayCount;
}