//created by Wang Jianwei on 01 Dec 2012
#ifndef ABSTRACTTEST_H
#define ABSTRACTTEST_H

#include <string>
#include "date.h"

using namespace std;
using namespace utilities;

namespace UnitTest{
	class AbstractTest{

	public:

		typedef tuple<date, double> point;

		virtual void runTest(){};

	protected:

		bool compareResult(double derivedVal, double expectedVal);

		bool compareResult(std::string derivedVal, std::string expectedVal);

		std::string getString(point point0);

		double _EPSILON;
	};
}
#endif