//created by Wang Jianwei on 01 Dec 2012

#include "DymonRecordHelper.h"
#include "AbstractDao.h"
#include "HolidayFileSource.h"

using namespace Session;
using namespace DAO;

DymonRecordHelper::DymonRecordHelper(){
}

void DymonRecordHelper::init(){
	buildHolidayMap();
}


void DymonRecordHelper::buildHolidayMap(){
	AbstractDAO* holidayDataSource = new HolidayFileSource();
	holidayDataSource->init();
	holidayDataSource->retrieveRecord();
}

std::map<std::string, std::set<long>> DymonRecordHelper::holidayMap;