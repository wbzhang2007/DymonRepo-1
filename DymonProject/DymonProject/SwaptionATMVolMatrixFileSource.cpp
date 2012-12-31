#include "SwaptionATMVolMatrixFileSource.h"

using namespace DAO;


void SwaptionATMVolMatrixFileSource::init(Configuration* cfg){
	_fileName = cfg->getProperty("swaptionPrice.file",true,"");
	_persistDir = cfg->getProperty("swaptionPrice.path",false,"");
	AbstractFileSource::init(cfg);
}

void SwaptionATMVolMatrixFileSource::retrieveRecord(){
	AbstractFileSource::retrieveRecord();
	
	_inFile.close();
}

void SwaptionATMVolMatrixFileSource::readCSV(std::istream &input, CSVDatabase &db) {
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

void SwaptionATMVolMatrixFileSource::display(const CSVRow& row) {
	if(!row.size())
		return;
	CSVRowCI i=row.begin();
	std::cout<<*(i++);
	for(;i != row.end();++i)
		std::cout<<','<<*i;
};

void SwaptionATMVolMatrixFileSource::display(const CSVDatabase& db) {
	if(!db.size())
		return;
	CSVDatabaseCI i=db.begin();
	for(; i != db.end(); ++i){
		display(*i);
		std::cout<<std::endl;
	}	
};

void SwaptionATMVolMatrixFileSource::swaptionTest() {

	std::fstream file("file.csv", std::ios::in);
	if(!file.is_open()){
		std::cout << "File not found!\n";
		return;
	}
	CSVDatabase db;
	readCSV(file, db);
	display(db);

};
