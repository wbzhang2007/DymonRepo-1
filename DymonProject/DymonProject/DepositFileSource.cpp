//created by Wang Jianwei on 1 Dec 2012

#include "DepositFileSource.h"
#include "AbstractFileSource.h"
#include "fileUtil.h"
#include "dateUtil.h"
#include "date.h"
#include "RecordHelper.h"

using namespace DAO;
using namespace std;
using namespace utilities;
using namespace Session;

DepositFileSource::DepositFileSource():
	AbstractFileSource(){}

DepositFileSource::DepositFileSource(std::string persistDir, std::string fileName):
	AbstractFileSource(persistDir, fileName){}

DepositFileSource::~DepositFileSource(){}

void DepositFileSource::init(Configuration* cfg){
	_fileName = cfg->getProperty("depositRate.file",true,"");
	_persistDir = cfg->getProperty("depositRate.path",false,"");
	AbstractFileSource::init(cfg);
}

void DepositFileSource::retrieveRecord(){
	AbstractFileSource::retrieveRecord();
	
	string value;
	string country;
	RecordHelper::RateMap tempMap;
	while (_inFile.good()){
		_inFile>>value;
		vector<string> vec = fileUtil::split(value,':');
		country = vec[0];
		vector<string> deposits = fileUtil::split(vec[1],',');
		cout<<country<<" total deposits number:  "<<deposits.size()<<endl;

		std::map<long, double> rateMap;
		for (unsigned int i = 0; i<deposits.size(); i++)
		{
			// 2D-0.1
			vector<string> tenureRate = fileUtil::split(deposits[i],'-');
			char letterDateUnit = *tenureRate[0].rbegin(); // 'D'
			int increment = std::stoi(tenureRate[0].substr(0,tenureRate[0].size()-1)); // 2
			double depositRate = std::stod(tenureRate[1]); // 0.1
			long JDN = dateUtil::getEndDate(dateUtil::getToday(),increment, true, dateUtil::getDateUnit(letterDateUnit)).getJudianDayNumber();
			rateMap.insert(pair<long, double>(JDN, depositRate));
			cout << country<< " -> " << tenureRate[0]<<" "<<JDN <<" "<< depositRate << endl;
		}
		tempMap.insert(pair<string, map<long, double>>(country,rateMap));
	}
	RecordHelper::getInstance()->setDepositRateMap(tempMap);
	_inFile.close();
}
