//created by Wang Jianwei on 1 Dec 2012

#include "Configuration.h"

using namespace utilities;
using namespace std;

Configuration::Configuration(){
}

Configuration::~Configuration(){
}

map<string, string> Configuration::getConfiguration(){
	return _config;
}

void Configuration::setConfiguration(map<string, string> config){
	_config = config;
}

string Configuration::getProperty(string key, bool compulsory){
	if(_config.find(key)==_config.end()){
		if(compulsory)
			throw "Property not found: "+key;
		else
			return "";
	}else{
		return _config[key];
	}
}

std::map<std::string, std::string> Configuration::_config;
