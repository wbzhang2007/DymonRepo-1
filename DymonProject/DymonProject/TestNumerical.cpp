//created by Wang Jianwei on 1 Dec 2012
#include "TestNumerical.h"
#include "AbstractNumerical.h"
#include "Bisection.h"
#include <iostream>
#include <sstream>
#include <cmath>
#include <string>

using namespace UnitTest;
using namespace utilities;
using namespace std;

void TestNumerical::runTest(){
	_EPSILON = 0.000001;
	newtonTestSuit();
	bisectionTestSuit();
}

void TestNumerical::newtonTestSuit(){
}

void TestNumerical::bisectionTestSuit(){
	bisectionTest(0, 2, _EPSILON, 50, 1);
	bisectionTest(0, 1.9, _EPSILON, 50, 1);
	bisectionTest(0, 2.1, _EPSILON, 50, 1);
	bisectionTest(0, 1.1, _EPSILON, 50, 1);
	bisectionTest(0, -2, _EPSILON, 50, -1);
	bisectionTest(0, -1.5, _EPSILON, 50, -1);
	bisectionTest(-1243852, -0.123, _EPSILON, 50, -1);
	bisectionTest(-2.123, -0.9999, _EPSILON, 50, -1);
	bisectionTest(0.453, 1.234, _EPSILON, 50, 1);
	bisectionTest(0.82376, 100000, _EPSILON, 50, 1);
}

void TestNumerical::newtonTest(double startVal, double endVal, double tolerance, int iterateCount, double expectedVal){
	//Newton<TestNumerical>* nt = new Newton<TestNumerical>(this,&TestNumerical::func);
	//double derivedVal = (double) nt->findRoot(startVal,endVal,tolerance,iterateCount);
	//compareResult("Newton",derivedVal, expectedVal, startVal, endVal);
}

void TestNumerical::bisectionTest(double startVal, double endVal, double tolerance, int iterateCount, double expectedVal){	
	Bisection<TestNumerical>* bt = new Bisection<TestNumerical>(this,&TestNumerical::func);
	double derivedVal = bt->findRoot(startVal,endVal,tolerance,iterateCount);
	compareResult("Bisection",derivedVal, expectedVal, startVal, endVal);
}

double TestNumerical::func(double x){
	return pow(x,2)-1;
}

void TestNumerical::compareResult(string testName, double derivedVal, double expectedVal, double startVal, double endVal){
	std::stringstream ss (stringstream::in | stringstream::out);
	if (abs(derivedVal-expectedVal)>_EPSILON)
		ss<<"Newton Test Failed: startVal["<<startVal<<"], endVal["<<endVal<<"], root found ["<<derivedVal<<"], desired root ["<<expectedVal<<"]";
	else
		ss<<"Newton Test Passed: startVal["<<startVal<<"], endVal["<<endVal<<"], root found ["<<derivedVal<<"]";
	cout<<ss.str()<<endl;
}