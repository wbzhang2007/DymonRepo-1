//created by Wang Jianwei on 01 Dec 2012
#ifndef ABSTRACTDAO_H
#define ABSTRACTDAO_H
#include <string>
#include <map>
#include "AbstractSession.h"

using namespace Session;
using namespace utilities;

namespace DAO{
	class AbstractDAO: public AbstractSession{

	public:

		virtual void init(Configuration*)=0;

		virtual void retrieveRecord()=0;

	};
}
#endif