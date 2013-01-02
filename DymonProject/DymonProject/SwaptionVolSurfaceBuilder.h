//created by Wang Jianwei on 01 Dec 2012
//Added cashflowleg creating - Kun
#ifndef SWAPTIONVOLSURFACEBUILDER_H
#define SWAPTIONVOLSURFACEBUILDER_H
#include "SwaptionVolSurface.h"
#include "AbstractBuilder.h"
#include <vector>

using namespace instruments;

namespace utilities{
	class SwaptionVolSurfaceBuilder: public AbstractBuilder{
		
	public:
		
		SwaptionVolSurfaceBuilder():AbstractBuilder(){}

		void init(Configuration* cfg);

		SwaptionVolSurface* build();

		currency getMarket(){return _market;}
		void setMarket(currency market){_market = market;}

		enums::interpolAlgo getInterpolAlgo(){return _interpolAlgo;}
		void setInterpolAlgo(enums::interpolAlgo interpolAlgo){_interpolAlgo=interpolAlgo;}


	private:

		currency _market;
		enums::interpolAlgo _interpolAlgo;
	};
}
#endif