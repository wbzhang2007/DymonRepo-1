//created by Wang Jianwei on 01 Dec 2012
#ifndef ABSTRACTDAO_H
#define ABSTRACTDAO_H

#include "AbstractSession.h"
using namespace Session;

namespace DAO{
	class AbstractDAO: public AbstractSession{

	public:

		virtual void init()=0;

		virtual void retrieveRecord()=0;

	};
}
#endif