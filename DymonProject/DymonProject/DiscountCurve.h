//created by Wang Jianwei on 01 Dec 2012
#ifndef DiscountCurve_H
#define DiscountCurve_H
#include "AbstractCurve.h"
#include <vector>
#include "Enums.h"

namespace utilities{
	class DiscountCurve: public AbstractCurve{
		
	public:
		
		DiscountCurve():AbstractCurve(){};

		DiscountCurve(std::vector<AbstractInterpolator*>* lineSectionVector):AbstractCurve(lineSectionVector){};

		void insertLineSection(AbstractInterpolator* lineSection);

		double getValue(date date0);

		double getDiscountFactor(date Date0);

		double getFLiborRate(date forwardStartDate,date forwardEndDate,enums::DayCountEnum dayCount);

		std::string toString();
	};
}
#endif