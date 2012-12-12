//created by Wang Jianwei on 01 Dec 2012
#ifndef YIELDCURVEBOOTSTRAPPER_H
#define YIELDCURVEBOOTSTRAPPER_H
#include <string>
#include "AbstractBootStrapper.h"

namespace utilities {
	class YieldCurveBootStrapper: public AbstractBootStrapper{
		
	public:
		YieldCurveBootStrapper():AbstractBootStrapper(){};

		void init(Configuration*);
		
		virtual AbstractCurve bootStrap();
	};

}
#endif