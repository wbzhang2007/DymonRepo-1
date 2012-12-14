//created by Wang Jianwei on 01 Dec 2012
#ifndef BUILDER_H
#define BUILDER_H
#include "AbstractSession.h"
#include "AbstractDataStructure.h"

namespace utilities{
	class Builder: public AbstractSession{
		
	public:
		
		Builder(){}
		
		virtual void init(Configuration*);
		
		AbstractDataStructure build();

	};
}
#endif