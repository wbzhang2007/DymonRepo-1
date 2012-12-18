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
	string market;
	RecordHelper::currencyMap currencyMap;
	while (_inFile.good()){
		_inFile>>value;
		vector<string> vec = fileUtil::split(value,':');
		market = vec[0];
		vector<string> properties = fileUtil::split(vec[1],',');

		enums::CurrencyEnum currencyName = EnumHelper::getCcyEnum(market);
		enums::DayCountEnum dayCountCash = EnumHelper::getDayCountEnum(properties[0]);
		enums::DayCountEnum dayCountSwap = EnumHelper::getDayCountEnum(properties[1]);
		enums::DayRollEnum dayRollCash = EnumHelper::getDayRollEnum(properties[2]);
		enums::DayRollEnum dayRollSwap = EnumHelper::getDayRollEnum(properties[3]);
		enums::DayRollEnum accrualAdjustCash = EnumHelper::getDayRollEnum(properties[4]);
		enums::DayRollEnum accrualAdjustSwap = EnumHelper::getDayRollEnum(properties[5]);

		RecordHelper::currencyTuple ccyTuple(dayCountCash, dayCountSwap, dayRollCash, dayRollSwap, accrualAdjustCash, accrualAdjustSwap);

		cout << market<< " -> "<< "DayCountCashConvention "<< dayCountCash<<endl;
		cout << market<< " -> "<< "DayCountSwapConvention "<< dayCountSwap<<endl;
		cout << market<< " -> "<< "DayRollCashConvention "<< dayRollCash<<endl;
		cout << market<< " -> "<< "DayRollSwapConvention "<< dayRollSwap<<endl;
		cout << market<< " -> "<< "AccrualAdjustCashConvention "<< accrualAdjustCash<<endl;
		cout << market<< " -> "<< "AccrualAdjustSwapConvention "<< accrualAdjustSwap<<endl;

		currencyMap.insert(pair<enums::CurrencyEnum, RecordHelper::currencyTuple>(currencyName,ccyTuple));
	}	
	RecordHelper::getInstance()->setCurrencyMap(currencyMap);
	_inFile.close();
}
