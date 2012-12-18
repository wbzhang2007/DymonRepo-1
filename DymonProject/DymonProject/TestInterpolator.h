//created by Wang Jianwei on 01 Dec 2012
#ifndef TESTINTERPOLATOR_H
#define TESTINTERPOLATOR_H

#include "AbstractInterpolator.h"
#include <string>
#include "date.h"
#include "AbstractTest.h"

using namespace std;
using namespace utilities;

namespace UnitTest{
	class TestInterpolator: public AbstractTest{

	public:
		typedef tuple<date, double> point;

		TestInterpolator():AbstractTest(){}

		void runTest();

		void linearTestSuit();

		void logLinearTestSuit();

	private:

		void linearTest(point startPoint, point endPoint, date targetDate, double tolerance, double expectedVal);

		void logLinearTest(point startPoint, point endPoint, date targetDate, double tolerance, double expectedVal);

		bool compareResult(std::string testName, double derivedVal, double expectedVal, point startPoint, point endPoint, date targetDate);
	};
}
#endif