//created by Wang Jianwei on 01 Dec 2012
#ifndef YIELDCURVE_H
#define YIELDCURVE_H
#include "AbstractCurve.h"
#include <vector>
#include "Enums.h"

namespace utilities{
	class YieldCurve: public AbstractCurve{
		
	public:
		
		YieldCurve():AbstractCurve(){};

		YieldCurve(std::vector<AbstractInterpolator>* lineSectionVector):AbstractCurve(lineSectionVector){};

		void insertLineSection(AbstractInterpolator* lineSection);

		double getValue(date date0);

		double getDiscountFactor(date Date0);

		double getFLiborRate(date forwardStartDate,date forwardEndDate,enums::DayCountEnum dayCount);

		std::string toString();
	};
}
#endif