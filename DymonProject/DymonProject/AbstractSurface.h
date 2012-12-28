//created by Wang Jianwei on 01 Dec 2012
#ifndef ABSTRACTSURFACE_H
#define ABSTRACTSURFACE_H
#include "AbstractCurve.h"
#include "AbstractInterpolator.h"
#include "AbstractDataStructure.h"
#include <map>

namespace utilities{
	class AbstractSurface: public AbstractDataStructure{
		
	public:		

		AbstractSurface():AbstractDataStructure(){
			_curves = new std::map<double, AbstractCurve*>;
		};

		AbstractSurface(std::map<double, AbstractCurve*> curves){
			setcurves(curves);
		}

		void setcurves(std::map<double, AbstractCurve*> curves){
			_curves=curves;
		}

		virtual void insertcurve(double majorAxisVal, AbstractCurve* curve);

		virtual AbstractCurve* getcurve(double majorAxisVal);

		virtual double getValue(double majorAxisVal, double minorAxisVal);

		bool validatecurves();

		virtual std::string toString();

	private:

		std::map<double, AbstractCurve*>* _curves;
	};
}
#endif