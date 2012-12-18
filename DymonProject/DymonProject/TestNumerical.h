//created by Wang Jianwei on 01 Dec 2012
#ifndef TESTNUMERICAL_H
#define TESTNUMERICAL_H
#include "AbstractTest.h"

#include <string>

using namespace std;

namespace UnitTest{
	class TestNumerical: public AbstractTest{

	public:
		TestNumerical():AbstractTest(){}

		void runTest();

		void newtonTestSuit();

		void bisectionTestSuit();

	private:

		void newtonTest(double startVal, double endVal, double tolerance, int iterateCount, double expectedVal);

		void bisectionTest(double startVal, double endVal, double tolerance, int iterateCount, double expectedVal);

		void compareResult(std::string testName, double derivedVal, double expectedVal, double startVal, double endVal);

		double func(double);
	};
}
#endif