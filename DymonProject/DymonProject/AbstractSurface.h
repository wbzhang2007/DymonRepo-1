//created by Wang Jianwei on 01 Dec 2012
#ifndef ABSTRACTSURFACE_H
#define ABSTRACTSURFACE_H
#include "AbstractCurve.h"
#include "AbstractInterpolator.h"
#include "AbstractDataStructure.h"
#include <map>
#include <sstream>

namespace utilities{
	template<typename T> class AbstractSurface: public AbstractDataStructure{
		
	public:		

		AbstractSurface():AbstractDataStructure(){
			_curves = new std::map<double, AbstractCurve<T>*>;
		};

		AbstractSurface(std::map<double, AbstractCurve<T>*> curves){
			setcurves(curves);
		}

		void setcurves(std::map<double, AbstractCurve<T>*> curves){
			_curves=curves;
		}

		virtual void insertcurve(double majorAxisVal, AbstractCurve<T>* curve);

		virtual AbstractCurve<T>* getcurve(double majorAxisVal);

		virtual double getValue(double majorAxisVal, T minorAxisVal);

		bool validateSurface();

		virtual std::string toString();

	private:

		std::map<double, AbstractCurve<T>*>* _curves;
	};

	template<typename T>
	void AbstractSurface<T>::insertcurve(double majorAxisVal, AbstractCurve<T>* curve){
		_curves->insert(pair<double, AbstractCurve<T>*>(majorAxisVal,curve));
	}
	
	template<typename T>
	AbstractCurve<T>* AbstractSurface<T>::getcurve(double majorAxisVal){
		if (_curves->find(majorAxisVal) == _curves->end())
			throw "Major axis value not found on surface";
		return _curves->find(majorAxisVal)->second;
	}

	template<typename T>
	double AbstractSurface<T>::getValue(double majorAxisVal, T minorAxisVal){
		AbstractCurve<T>* curve=getcurve(majorAxisVal);
		return curve->getValue(minorAxisVal);
	}

	template<typename T>
	bool AbstractSurface<T>::validateSurface(){
		bool validationPass = true;
		for (map<double, AbstractCurve<T>*>::iterator it = _curves->begin(); it!=_curves->end(); it++)
			if (!(*it).second->validateLineSections())
				validationPass = false;
		return validationPass;
	}

	template<typename T>
	std::string  AbstractSurface<T>::toString(){
		std::stringstream ss (stringstream::in | stringstream::out);
		for (map<double, AbstractCurve<T>*>::iterator it = _curves->begin(); it!=_curves->end(); it++){
			ss<<"Major axis value ["<<(*it).first<<"] has ";
			ss<<(*it).second->toString();
		}
		return ss.str();
	}

}
#endif