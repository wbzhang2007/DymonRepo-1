//created by Wang Jianwei on 1 Dec 2012

#include "CurrencyFileSource.h"
#include "AbstractFileSource.h"
#include "fileUtil.h"
#include "dateUtil.h"
#include "date.h"
#include "RecordHelper.h"
#include "EnumHelper.h"

using namespace DAO;
using namespace std;
using namespace utilities;
using namespace Session;

CurrencyFileSource::CurrencyFileSource():
	AbstractFileSource(){}

CurrencyFileSource::CurrencyFileSource(std::string persistDir, std::string fileName):
	AbstractFileSource(persistDir, fileName){}

CurrencyFileSource::~CurrencyFileSource(){}

void CurrencyFileSource::init(Configuration* cfg){
	_fileName = cfg->getProperty("currency.file",true,"");
	_persistDir = cfg->getProperty("currency.path",false,"");
	AbstractFileSource::init(cfg);
}

void CurrencyFileSource::retrieveRecord(){
	AbstractFileSource::retrieveRecord();

	string value;
	string currency;
	RecordHelper::currencyMap currencyMap;
	while (_inFile.good()){
		_inFile>>value;
		vector<string> vec = fileUtil::split(value,':');
		currency = vec[0];
		vector<string> properties = fileUtil::split(vec[1],',');

		enums::CurrencyEnum currencyName = EnumHelper::getCcyEnum(currency);
		enums::DayCountEnum dayCountCashConvention = EnumHelper::getDayCountEnum(properties[0]);
		enums::DayCountEnum dayCountSwapConvention = EnumHelper::getDayCountEnum(properties[1]);
		enums::DayRollEnum dayRollConvention = EnumHelper::getDayRollEnum(properties[2]);

		RecordHelper::currencyTuple ccyTuple(dayCountCashConvention, dayCountSwapConvention, dayRollConvention);

		cout << currency<< " -> " << dayCountCashConvention<<" "<<dayCountSwapConvention <<" "<< dayRollConvention << endl;
		currencyMap.insert(pair<enums::CurrencyEnum, RecordHelper::currencyTuple>(currencyName,ccyTuple));
	}	
	RecordHelper::getInstance()->setCurrencyMap(currencyMap);
	_inFile.close();
}
