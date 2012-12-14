//created by Wang Jianwei on 01 Dec 2012
#ifndef ABSTRACTCURVE_H
#define ABSTRACTCURVE_H
#include "AbstractInterpolator.h"
#include <vector>

namespace utilities{
	class AbstractCurve{
		
	public:
		
		typedef tuple<date, double> point;

		AbstractCurve();

		AbstractCurve(std::vector<AbstractInterpolator>* lineSectionVector);

		virtual void insertLineSection(const AbstractInterpolator& lineSection);

		virtual double getY(date date0);

		void setLineSectionVector(std::vector<AbstractInterpolator>* lineSectionVector);

	private:

		std::vector<AbstractInterpolator>* _lineSectionVector;

	};
}
#endif