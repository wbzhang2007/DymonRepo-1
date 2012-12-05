//created by Wang Jianwei on 01 Dec 2012
#ifndef ABSTRACTSESSION_H
#define ABSTRACTSESSION_H
#include <string>
#include <map>

namespace Session{
	class AbstractSession{

	public:
		virtual void init(std::map<std::string, std::string>)=0;

		virtual void start();

		virtual void stop();
	};
}
#endif