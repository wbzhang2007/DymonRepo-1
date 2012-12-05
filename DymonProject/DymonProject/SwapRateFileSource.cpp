//created by Wang Jianwei on 1 Dec 2012

#include "SwapRateFileSource.h"
#include "AbstractFileSource.h"
#include "fileUtil.h"
#include "dateUtil.h"
#include "date.h"
#include "DymonRecordHelper.h"

using namespace DAO;
using namespace std;
using namespace utilities;
using namespace Session;

SwapRateFileSource::SwapRateFileSource():
	AbstractFileSource(){}

SwapRateFileSource::SwapRateFileSource(std::string persistDir, std::string fileName):
	AbstractFileSource(persistDir, fileName){}

SwapRateFileSource::~SwapRateFileSource(){}

void SwapRateFileSource::init(){
	_fileName = "swapRate.txt";
	_persistDir = "";
	AbstractFileSource::init();
}

void SwapRateFileSource::retrieveRecord(){
	SwapRateFileSource::retrieveRecord();
	
	string value;
	string currency;
	while (_inFile.good()){
		_inFile>>value;
		vector<string> vec = fileUtil::split(value,':');
		currency = vec[0];
		vector<string> swapRates = fileUtil::split(vec[1],',');
		cout<<currency<<" total deposits number:  "<<swapRates.size()<<endl;
		//set<long> JDNSet = buildJDNSet(holidays);
		//DymonRecordHelper::depositRateMap.insert(pair<string,set<long>>(country,JDNSet));
	}
	_inFile.close();
}
