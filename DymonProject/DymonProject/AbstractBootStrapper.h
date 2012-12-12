//created by Wang Jianwei on 01 Dec 2012
#ifndef ABSTRACTBOOTSTRAPPER_H
#define ABSTRACTBOOTSTRAPPER_H
#include "AbstractSession.h"
#include "AbstractCurve.h"

using namespace Session;

namespace utilities{
	class AbstractBootStrapper: public AbstractSession{
	public:

		AbstractBootStrapper(){};

		virtual void init(Configuration*)=0;

		virtual void start();

		virtual void stop();

		virtual AbstractCurve bootStrap();

	};
}
#endif