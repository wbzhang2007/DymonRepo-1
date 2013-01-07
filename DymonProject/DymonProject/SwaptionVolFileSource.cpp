//created by Hu Kun 1 Jan
#include "SwaptionVolFileSource.h"
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

#define NA -99999

using namespace DAO;
using namespace std;
using namespace utilities;
using namespace Session;
using namespace instruments;


void SwaptionVolFileSource::init(Configuration* cfg){
	_fileName = cfg->getProperty("swaptionVolCube.usd.file",true,"");
	_persistDir = cfg->getProperty("swaptionVolCube.usd.path",false,"");
	AbstractFileSource::init(cfg);
}

void SwaptionVolFileSource::retrieveRecord(){
	AbstractFileSource::retrieveRecord();
	
	CSVDatabase db;
	readCSV(_inFile, db);

	RecordHelper::SwaptionVolMap tempMap;
	int numOfRows=db.size();
	int numOfCols=db.at(0).size();

	cout <<"numofRows="<<numOfRows<<endl;
	cout <<"numOfCols="<<numOfCols<<endl;
	for (int i=0;i<=numOfRows-1;i++) {

		std::regex ATM ("ATM(.*)");
		std::regex MO ("MO");
		std::regex YR ("YR");
		
		
		String aCell=db.at(i).at(0);
		if (std::regex_match (aCell,ATM)) {
			enums::MarketEnum market = EnumHelper::getCcyEnum(db.at(i).at(1));
			Market mkt(market);
			continue;
		}
		for (int j=2;j<=numOfCols-1;j++) {

			String topRowCell=db.at(0).at(j);
			String tagCell=db.at(i).at(1);

			if (tagCell.compare("Vol")==0) {
				int pos=aCell.find(" ");
				double optionTenor=std::stod(aCell.substr(0,pos));
				if (std::regex_match (aCell,YR)) {
					optionTenor=std::stod(aCell.substr(0,pos))*12;
				}

				double vol=db.at(i).at(j).compare("")==0?NA:std::stod(db.at(i).at(j));
				double strike=db.at(i+1).at(j).compare("")==0?NA:std::stod(db.at(i+1).at(j));

				double fSwapTenor=std::stod(topRowCell.substr(0,topRowCell.find(" ")))*12;

				//std::map<strike,std::map<tuple<double fSwapTenorNumOfMonths,double optionTenorNumOfMonths>,double swaptionVol>> SwaptionVolMap

				auto aTuple=std::make_tuple(fSwapTenor,optionTenor);
				std::map<tuple<double,double>,double> aPair;
				aPair.insert(std::make_pair(aTuple,vol));
				//pair<tuple<double,double>,double>
				tempMap.insert(std::make_pair(strike,aPair));
				//<double,std::map<tuple<double,double>,double>>
					
			}
			else {
				continue;
			}
			

		}

	}

	RecordHelper::getInstance()->setSwaptionVolMap(tempMap);
	_inFile.close();
	//DAO::SwaptionVolFileSource::swaptionTest();
}

void SwaptionVolFileSource::readCSV(std::ifstream &input, CSVDatabase &db) {
	String csvLine;
	// read every line from the stream
	while( std::getline(input, csvLine) ){
		std::istringstream csvStream(csvLine);
		CSVRow csvRow;
		String csvCol;
		// read every element from the line that is seperated by commas
		// and put it into the vector or strings
		while( std::getline(csvStream, csvCol, ',') )
			csvRow.push_back(csvCol);
		db.push_back(csvRow);
	}

};

void SwaptionVolFileSource::display(const CSVRow& row) {
	if(!row.size())
		return;
	CSVRowCI i=row.begin();
	std::cout<<*(i++);
	for(;i != row.end();++i)
		std::cout<<','<<*i;
};

void SwaptionVolFileSource::display(const CSVDatabase& db) {
	if(!db.size())
		return;
	CSVDatabaseCI i=db.begin();
	for(; i != db.end(); ++i){
		display(*i);
		std::cout<<std::endl;
	}	
};

void SwaptionVolFileSource::swaptionTest() {

	std::fstream file("swaption_skew_USD.csv", std::ios::in);
	if(!file.is_open()){
		std::cout << "File not found!\n";
		return;
	}
	CSVDatabase db;
	readCSV(_inFile, db);
	display(db);

};


