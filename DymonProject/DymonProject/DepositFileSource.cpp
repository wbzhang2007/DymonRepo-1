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
	_fileName = cfg->getProperty("depositRate.file",true);
	_persistDir = cfg->getProperty("depositRate.path",false);
	AbstractFileSource::init(cfg);
}

void DepositFileSource::retrieveRecord(){
	AbstractFileSource::retrieveRecord();
	
	string value;
	string currency;
	map<string, std::map<int, double>> tempMap;
	while (_inFile.good()){
		_inFile>>value;
		//vector<string> vec = fileUtil::split(value,':');
		//currency = vec[0];
		//vector<string> deposits = fileUtil::split(vec[1],',');
		//cout<<currency<<" total deposits number:  "<<deposits.size()<<endl;
		//set<long> JDNSet = buildJDNSet(holidays);
		//tempMap.insert(pair<string,set<long>>(country,JDNSet));
	}
	//RecordHelper::getInstance()->setDepositRateMap(tempMap);
	_inFile.close();
}
