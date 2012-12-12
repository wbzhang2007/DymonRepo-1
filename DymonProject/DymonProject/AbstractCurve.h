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

		AbstractCurve(std::vector<AbstractInterpolator>* lineSectionVector, AbstractInterpolator::interpolAlgo algo);

		virtual void insertLineSection(const AbstractInterpolator& lineSection);

		virtual double getY(date date0);

		void setAlgo(AbstractInterpolator::interpolAlgo algo);

		void setLineSectionVector(std::vector<AbstractInterpolator>* lineSectionVector);

	private:

		AbstractInterpolator::interpolAlgo _algo;

		std::vector<AbstractInterpolator>* _lineSectionVector;

	};
}
#endif