//created by Wang Jianwei on 1 Dec 2012

#include "HolidayFileSource.h"
#include <iostream>
#include <fstream>
#include "AbstractFileSource.h"

using namespace DAO;
using namespace std;

HolidayFileSource::HolidayFileSource():
	AbstractFileSource(){}

HolidayFileSource::HolidayFileSource(std::string persistDir, std::string fileName, long fileSize):
	AbstractFileSource(persistDir, fileName, fileSize){}

HolidayFileSource::~HolidayFileSource(){}

void HolidayFileSource::init(){
	_fileName = "";
	_persistDir = "";
	_fileSize = 0;
	AbstractFileSource::init();
}

void HolidayFileSource::retrieveRecord(){
	AbstractFileSource::retrieveRecord();
	
}