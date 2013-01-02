//created by Wang Jianwei on 01 Dec 2012
#ifndef SWAPTIONVOLCUBE_H
#define SWAPTIONVOLCUBE_H
#include "AbstractSurface.h"
#include "SwaptionVolSurface.h"

using namespace utilities;

namespace utilities{
	class SwaptionVolCube{
		
	public:		

		SwaptionVolCube(){};

		double getVol(double strike, double maturity, double tenor);

		SwaptionVolSurface* getVolSurface(double strike);

	private:

		map<double,SwaptionVolSurface*> _cube;
	};
}
#endif