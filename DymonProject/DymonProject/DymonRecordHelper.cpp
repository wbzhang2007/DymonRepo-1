//created by Wang Jianwei on 01 Dec 2012

#include "DymonRecordHelper.h"
#include "AbstractDao.h"
#include "Configuration.h"
#include "swapRateFileSource.h"
#include "HolidayFileSource.h"
#include "DepositFileSource.h"

using namespace Session;
using namespace DAO;

DymonRecordHelper::DymonRecordHelper(){
}

void DymonRecordHelper::init(){
	buildConfiguration();
	buildHolidayMap();
	buildSwapRateMap();
	buildConfiguration();
}

void DymonRecordHelper::buildSwapRateMap(){
	AbstractDAO* SwapRateDataSource = new SwapRateFileSource();
	SwapRateDataSource->init(configuration);
	SwapRateDataSource->retrieveRecord();
}

void DymonRecordHelper::buildDepositRateMap(){
	AbstractDAO* depositRateDataSource = new DepositFileSource();
	depositRateDataSource->init(configuration);
	depositRateDataSource->retrieveRecord();
}

void DymonRecordHelper::buildHolidayMap(){
	AbstractDAO* holidayDataSource = new HolidayFileSource();
	holidayDataSource->init(configuration);
	holidayDataSource->retrieveRecord();
}

void DymonRecordHelper::buildConfiguration(){
	AbstractDAO* configDataSource= new Configuration();
	configDataSource->init(configuration);
	configDataSource->retrieveRecord();
}

std::map<std::string, std::set<long>> DymonRecordHelper::holidayMap;

std::map<std::string, std::map<int, double>> depositRateMap;

std::map<std::string, std::map<int, double>> swapRateMap;

std::map<std::string, std::string> configuration;