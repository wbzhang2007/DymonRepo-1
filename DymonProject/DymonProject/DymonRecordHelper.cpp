//created by Wang Jianwei on 01 Dec 2012

#include "DymonRecordHelper.h"
#include "AbstractDao.h"
#include "Configuration.h"
#include "swapRateFileSource.h"
#include "HolidayFileSource.h"
#include "DepositFileSource.h"
#include "ConfigurationFileSource.h"

using namespace Session;
using namespace DAO;
using namespace std;

DymonRecordHelper::DymonRecordHelper(){
}

void DymonRecordHelper::init(Configuration cfg){
	buildConfiguration(cfg);
	buildHolidayMap(cfg);
	buildSwapRateMap(cfg);
	buildDepositRateMap(cfg);
}

void DymonRecordHelper::buildSwapRateMap(Configuration cfg){
	AbstractDAO* SwapRateDataSource = new SwapRateFileSource();
	SwapRateDataSource->init(cfg);
	SwapRateDataSource->retrieveRecord();
}

void DymonRecordHelper::buildDepositRateMap(Configuration cfg){
	AbstractDAO* depositRateDataSource = new DepositFileSource();
	depositRateDataSource->init(cfg);
	depositRateDataSource->retrieveRecord();
}

void DymonRecordHelper::buildHolidayMap(Configuration cfg){
	AbstractDAO* holidayDataSource = new HolidayFileSource();
	holidayDataSource->init(cfg);
	holidayDataSource->retrieveRecord();
}

void DymonRecordHelper::buildConfiguration(Configuration cfg){
	AbstractDAO* configDataSource= new ConfigurationFileSource();
	configDataSource->init(cfg);
	configDataSource->retrieveRecord();
}

std::map<std::string, std::set<long>> DymonRecordHelper::holidayMap;

std::map<std::string, std::map<int, double>> DymonRecordHelper::depositRateMap;

std::map<std::string, std::map<int, double>> DymonRecordHelper::swapRateMap;