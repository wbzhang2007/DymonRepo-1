//created by Wang Jianwei on 01 Dec 2012
#ifndef ABSTRACTCURVE_H
#define ABSTRACTCURVE_H
#include "AbstractInterpolator.h"
#include "AbstractDataStructure.h"
#include <vector>

namespace utilities{
	template<typename T> class AbstractCurve: public AbstractDataStructure{
		
	public:
		
		typedef tuple<T, double> point;

		AbstractCurve():AbstractDataStructure(){
			_lineSectionVector = new std::vector<AbstractInterpolator<T>*>;
		};

		AbstractCurve(std::vector<AbstractInterpolator<T>*>* lineSectionVector);

		virtual void insertLineSection(AbstractInterpolator<T>* lineSection);

		virtual double getValue(T xVal);

		void setLineSectionVector(std::vector<AbstractInterpolator<T>*>* lineSectionVector){
			_lineSectionVector = lineSectionVector;		
		}

		bool validateLineSections();
		
		virtual std::string toString();

	private:

		std::vector<AbstractInterpolator<T>*>* _lineSectionVector;

	};
}
#endif