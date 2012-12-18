//created by Wang Jianwei on 1 Dec 2012

#include "SwapRateFileSource.h"
#include "AbstractFileSource.h"
#include "fileUtil.h"
#include "dateUtil.h"
#include "date.h"
#include "RecordHelper.h"
#include "Enums.h"
#include "EnumHelper.h"

using namespace DAO;
using namespace std;
using namespace utilities;
using namespace Session;

SwapRateFileSource::SwapRateFileSource():
	AbstractFileSource(){}

SwapRateFileSource::SwapRateFileSource(std::string persistDir, std::string fileName):
	AbstractFileSource(persistDir, fileName){}

SwapRateFileSource::~SwapRateFileSource(){}

void SwapRateFileSource::init(Configuration* cfg){
	_fileName = cfg->getProperty("swapRate.file",true,"");
	_persistDir = cfg->getProperty("swapRate.path",false,"");
	AbstractFileSource::init(cfg);
}

void SwapRateFileSource::retrieveRecord(){
	AbstractFileSource::retrieveRecord();
	
	string value;
	enums::CurrencyEnum market;
	RecordHelper::RateMap tempMap;
	while (_inFile.good()){
		_inFile>>value;
		vector<string> vec = fileUtil::split(value,':');
		market = EnumHelper::getCcyEnum(vec[0]);
		vector<string> deposits = fileUtil::split(vec[1],',');
		cout<<market<<" market has total swap rate number:  "<<deposits.size()<<endl;

		std::map<long, double> rateMap;
		for (unsigned int i = 0; i<deposits.size(); i++)
		{
			// 2Y-3.134
			vector<string> tenureRate = fileUtil::split(deposits[i],'-');
			char letterDateUnit = *tenureRate[0].rbegin(); // 'Y'
			int increment = std::stoi(tenureRate[0].substr(0,tenureRate[0].size()-1)); // 2
			double swapRate = std::stod(tenureRate[1]); // 3.134
			long JDN = dateUtil::getEndDate(dateUtil::getToday(),increment, true, dateUtil::getDateUnit(letterDateUnit), market).getJudianDayNumber();
			rateMap.insert(pair<long, double>(JDN, swapRate));
			cout << market<< " -> " << tenureRate[0]<<" "<<JDN <<" "<< swapRate << endl;
		}
		tempMap.insert(pair<enums::CurrencyEnum, map<long, double>>(market,rateMap));
	}
	RecordHelper::getInstance()->setSwapRateMap(tempMap);
	_inFile.close();
}
