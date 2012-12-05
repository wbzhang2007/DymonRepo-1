//created by Wang Jianwei on 01 Dec 2012
#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include <string>
#include <map>

namespace utilities {
	class Configuration{
		
	public:
		Configuration();
		~Configuration();

		std::map<std::string, std::string> getConfiguration();
	
		void setConfiguration(std::map<std::string, std::string> cfg);

		std::string getProperty(std::string,bool);

		static std::map<std::string, std::string> _config;
		
	};
}
#endif