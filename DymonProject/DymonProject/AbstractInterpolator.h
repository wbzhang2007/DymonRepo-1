//created by Wang Jianwei on 01 Dec 2012
#ifndef ABSTRACTINTERPOLATOR_H
#define ABSTRACTINTERPOLATOR_H
#include <vector>
#include <tuple>
#include "date.h"
#include "Enums.h"

using namespace std;

namespace utilities{
	template<typename T> class AbstractInterpolator{

	public:

		typedef tuple<T, double> point;

		AbstractInterpolator(point startPoint, point endPoint){
			_startPoint = startPoint;
			_endPoint = endPoint;
		}

		virtual point interpolate(T xVal){return point(NULL,0);}

		point getStartPoint(){return _startPoint;}

		point getEndPoint(){return _endPoint;}

		T getStartingX();

		T getEndingX();

		virtual std::string toString();

	protected:

		void xValInRangeCheck(T xVal);

		point _startPoint;

		point _endPoint;

		enums::interpolAlgo _algo;
	};

	template <class T> 
	T AbstractInterpolator<T>::getStartingJDN(){
		point start = getStartPoint();
		return std::get<0>(start);
	}

	template <class T> 
	T AbstractInterpolator<T>::getEndingJDN(){
		point end = getEndPoint();
		return std::get<0>(end);
	}

	template <class T> 
	string AbstractInterpolator<T>::toString(){
		std::stringstream ss (stringstream::in | stringstream::out);
		ss << "line section from {";
		ss << std::get<0>(_startPoint).toString() << "," <<std::get<1>(_startPoint)<<"} to {";
		ss << std::get<0>(_endPoint).toString() << "," <<std::get<1>(_endPoint)<<"}";
		return ss.str();
	}

	template <class T> 
	void AbstractInterpolator<T>::xValInRangeCheck(T xVal){
		if (xVal<getStartingX()){
			std::stringstream ss (stringstream::in | stringstream::out);
			ss<<"Value ["<<xVal<<"] is smaller than the line section starting value ["<<getStartingX()<<"]";
			throw ss.str();
		}else if (date0.getJudianDayNumber()>getEndingJDN()){
			std::stringstream ss (stringstream::in | stringstream::out);
			ss<<"Value ["<<xVal<<"] is larger than the line section ending value ["<<getStartingX()<<"]";
			throw ss.str();
		}
	}
}
#endif