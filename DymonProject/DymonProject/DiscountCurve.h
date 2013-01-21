//created by Wang Jianwei on 01 Dec 2012
#ifndef DiscountCurve_H
#define DiscountCurve_H
#include "AbstractCurve.h"
#include <vector>
#include "Enums.h"
#include "date.h"

namespace utilities{
	class DiscountCurve: public AbstractCurve<date>{
		
	public:
		
		DiscountCurve():AbstractCurve(){};

		DiscountCurve(std::vector<AbstractInterpolator<date>*>* lineSectionVector):AbstractCurve(lineSectionVector){};

		double getDiscountFactor(date Date0);

		double getFLiborRate(date forwardStartDate,date forwardEndDate,enums::DayCountEnum dayCount);

		std::string toString();
		
		std::string toString(int interval);
	};
}
#endif