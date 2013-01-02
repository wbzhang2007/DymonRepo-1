//created by Wang Jianwei on 01 Dec 2012
#ifndef SWAPTIONVOLCUBE_H
#define SWAPTIONVOLCUBE_H
#include "AbstractSurface.h"
#include "SwaptionVolSurface.h"
#include "AbstractCurve.h"
#include "currency.h"
#include "Enums.h"

using namespace utilities;
using namespace instruments;

namespace utilities{
	class SwaptionVolCube: public AbstractDataStructure{
		
	public:		

		typedef map<double, SwaptionVolSurface*>::iterator CubeIterator;

		SwaptionVolCube():AbstractDataStructure(){};

		SwaptionVolCube(map<double,SwaptionVolSurface*>* cube, currency market, enums::interpolAlgo interpolAlgo){
			_cube=cube;
			_market=market;
			_interpolAlgo=interpolAlgo;
		};

		double getVol(double strike, double maturity, double tenor);

		SwaptionVolSurface* getVolSurface(double strike);

		AbstractCurve<double>* getVolCurveAlongStrike(double maturity, double tenor);

		map<double,SwaptionVolSurface*>* getCube(){return _cube;}
		void setCube(map<double,SwaptionVolSurface*>* cube){_cube = cube;}

		currency getMarket(){return _market;}
		void setMarket(currency market){_market = market;}

		enums::interpolAlgo getInterpolAlgo(){return _interpolAlgo;}
		void setInterpolAlgo(enums::interpolAlgo interpolAlgo){_interpolAlgo=interpolAlgo;}


	private:

		currency _market;
		enums::interpolAlgo _interpolAlgo;

		map<double,SwaptionVolSurface*>* _cube;

		AbstractInterpolator<double>* getVolLineSectionAlongStrike(double startStrike, double startVol, double endStrike, double endVol);
	};
}
#endif