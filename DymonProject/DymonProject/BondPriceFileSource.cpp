//implemented by Kun from bloomberg market data sources on 13 Jan 2013
#include "BondPriceFileSource.h"
#include "AbstractFileSource.h"
#include "fileUtil.h"
#include "dateUtil.h"
#include "date.h"
#include "RecordHelper.h"
#include "Enums.h"
#include "EnumHelper.h"
#include "Market.h"
#include <tuple>
#include <regex>
#include "Constants.h"

using namespace DAO;
using namespace std;
using namespace utilities;
using namespace Session;
using namespace instruments;

using namespace DAO;
void BondPriceFileSource::init(Configuration* cfg){
	_fileName = cfg->getProperty("bondPrice.file",true,"");
	_persistDir = cfg->getProperty("bondPrice.path",false,"");
	AbstractFileSource::init(cfg);
}

void BondPriceFileSource::retrieveRecord(){
	AbstractFileSource::retrieveRecord();

	CSVDatabase db;
	readCSV(_inFile, db);

	int numOfRows=db.size();
	int numOfCols=db.at(0).size();
	int bondTenorNumOfMonths=0;
	
	RecordHelper::BondRateMap bondRateMap;
	enums::MarketEnum market;
	std::regex CURR ("[A-Z]{3}");
	std::regex YR("[0-9]+Y");
	
	for (int i=0;i<=numOfRows-1;i++) {

		String aCell=db.at(i).at(0);

		if (std::regex_match (aCell,CURR)) {
			
			market = EnumHelper::getCcyEnum(aCell);
			Market mkt(market);
			continue;
		}

		if (std::regex_match (aCell,YR)) {
			bondTenorNumOfMonths=std::stoi(aCell.substr(0,aCell.find("Y")))*12;
		}
		else {
			bondTenorNumOfMonths=std::stoi(aCell.substr(0,aCell.find("M")));
		}

		double bondYield=std::stoi(db.at(i).at(3));
		std::map<int,double> temp;
		temp.insert(std::make_pair(bondTenorNumOfMonths,bondYield));
		
		bondRateMap.insert(std::make_pair(market,temp));

	}

	RecordHelper::getInstance()->setBondRateMap(bondRateMap);
	
	_inFile.close();

}
