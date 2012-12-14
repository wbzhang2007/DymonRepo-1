//created by Wang Jianwei on 1 Dec 2012

#include "Configuration.h"

using namespace utilities;
using namespace std;

Configuration* Configuration::single = NULL;

Configuration* Configuration::getInstance()
{
	if(! single)
		single = new Configuration();
	return single;
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

