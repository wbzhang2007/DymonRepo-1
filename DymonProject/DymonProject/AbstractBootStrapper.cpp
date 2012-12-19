//created by Wang Jianwei on 1 Dec 2012

#include "AbstractBootStrapper.h"

using namespace utilities;
using namespace std;

void AbstractBootStrapper::init(Configuration* cfg){
	_iterateCount = std::stoi(cfg->getProperty("numerical.iteration", false, "50"));
	_plusMinus = std::stoi(cfg->getProperty("numerical.plusminus", false, "20"));
	_tolerance = std::stod(cfg->getProperty("numerical.tolerance", false, "0.0000001"));
};