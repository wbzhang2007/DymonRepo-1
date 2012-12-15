//created by Wang Jianwei on 01 Dec 2012
#ifndef YIELDCURVE_H
#define YIELDCURVE_H
#include "AbstractCurve.h"
#include <vector>

namespace utilities{
	class YieldCurve: public AbstractCurve{
		
	public:
		
		YieldCurve():AbstractCurve(){};

		YieldCurve(std::vector<AbstractInterpolator>* lineSectionVector):AbstractCurve(lineSectionVector){};

		void insertLineSection(const AbstractInterpolator& lineSection);

		double getY(date date0);
	};
}
#endif