//created by Wang Jianwei on 01 Dec 2012
#ifndef ABSTRACTDATASOURCE_H
#define ABSTRACTDATASOURCE_H
#include <string>
#include <fstream>
#include <map>
#include "AbstractDAO.h"

using namespace utilities;

namespace DAO {
	class  AbstractFileSource: public AbstractDAO{

	public:
		AbstractFileSource();
		AbstractFileSource(std::string persistDir, std::string fileName);
		~AbstractFileSource();

		virtual void init(Configuration);

		virtual char* readRecord();

		virtual void retrieveRecord();
		
		virtual void writeRecord(char* content);

		virtual void appendRecord(char* content);
		
		std::string getFileName();
		virtual void closeDataSource();
		virtual void deleteDataSource();		

	private:			
		std::ofstream _outFile;		
		long _fileSize;
		bool isModified;

	protected:
		std::string _fileName;
		std::string _persistDir;
		char* _journal;
		std::ifstream _inFile;
	};
}
#endif