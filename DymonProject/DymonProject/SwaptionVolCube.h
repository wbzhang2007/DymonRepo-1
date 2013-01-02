//created by Wang Jianwei on 01 Dec 2012
#ifndef SWAPTIONVOLCUBE_H
#define SWAPTIONVOLCUBE_H
#include "AbstractSurface.h"
#include "SwaptionVolSurface.h"
#include "currency.h"
#include "Enums.h"

namespace utilities{
	class SwaptionVolCube{
		
	public:		

		SwaptionVolCube(){};

		SwaptionVolCube(currency market, enums::interpolAlgo interpolAlgo){
			_market=market;
			_interpolAlgo=interpolAlgo;
		};

		double getVol(double strike, double maturity, double tenor);

		SwaptionVolSurface* getVolSurface(double strike);

		currency getMarket(){return _market;}
		void setMarket(currency market){_market = market;}

		enums::interpolAlgo getInterpolAlgo(){return _interpolAlgo;}
		void setInterpolAlgo(enums::interpolAlgo interpolAlgo){_interpolAlgo=interpolAlgo;}


	private:

		currency _market;
		enums::interpolAlgo _interpolAlgo;

		map<double,SwaptionVolSurface*> _cube;
	};
}
#endif