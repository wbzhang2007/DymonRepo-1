//created by Wang Jianwei on 1 Dec 2012

#include "HolidayFileSource.h"
#include "AbstractFileSource.h"
#include "fileUtil.h"
#include "dateUtil.h"
#include "date.h"
#include "DymonRecordHelper.h"

using namespace DAO;
using namespace std;
using namespace utilities;
using namespace Session;

HolidayFileSource::HolidayFileSource():
	AbstractFileSource(){}

HolidayFileSource::HolidayFileSource(std::string persistDir, std::string fileName):
	AbstractFileSource(persistDir, fileName){}

HolidayFileSource::~HolidayFileSource(){}

void HolidayFileSource::init(){
	_fileName = "holiday.txt";
	_persistDir = "";
	AbstractFileSource::init();
}

void HolidayFileSource::retrieveRecord(){
	AbstractFileSource::retrieveRecord();
	
	string value;
	string country;
	while (_inFile.good()){
		_inFile>>value;
		vector<string> vec = fileUtil::split(value,':');
		country = vec[0];
		vector<string> holidays = fileUtil::split(vec[1],',');
		cout<<country<<" total holiday number:  "<<holidays.size()<<endl;
		set<long> JDNSet = buildJDNSet(holidays);
		DymonRecordHelper::holidayMap.insert(pair<string,set<long>>(country,JDNSet));
	}
	_inFile.close();
}

set<long> HolidayFileSource::buildJDNSet(vector<string> vec0){
	set<long> JDNSet;
	for(unsigned int i=0; i<vec0.size(); i++) {
		long JDN = dateUtil::getJudianDayNumber(stoi(vec0[i].substr(0,4)),stoi(vec0[i].substr(4,2)),stoi(vec0[i].substr(6,2)),date::Gregorian);
		JDNSet.insert(JDN);
	}
	return JDNSet;
}
