//created by Wang Jianwei on 1 Dec 2012
#include "TestInterpolator.h"
#include "AbstractInterpolator.h"
#include <iostream>
#include <sstream>
#include <cmath>
#include <string>
#include "LinearInterpolator.h"
#include "LogLinearInterpolator.h"

using namespace UnitTest;
using namespace utilities;
using namespace std;

void TestInterpolator::runTest(){
	_EPSILON = 0.000001;
	linearTestSuit();
	logLinearTestSuit();
}

void TestInterpolator::linearTestSuit(){
	date startDate(2012,12,7);
	date endDate(2012,12,21);
	point startPoint(startDate, 1);
	point endPoint(endDate, 15);
	{
		date targetDate(2012,12,9);
		linearTest(startPoint, endPoint, targetDate, _EPSILON, 3);}
	{
		date targetDate(2012,12,15);
		linearTest(startPoint, endPoint, targetDate, _EPSILON, 9);}
	{
		date targetDate(2012,12,7);
		linearTest(startPoint, endPoint, targetDate, _EPSILON, 1);}
	{
		date targetDate(2012,12,21);
		linearTest(startPoint, endPoint, targetDate, _EPSILON, 15);}
}

void TestInterpolator::logLinearTestSuit(){
	date startDate(2012,12,7);
	date endDate(2012,12,21);
	point startPoint(startDate, 1);
	point endPoint(endDate, 15);
	{
		date targetDate(2012,12,9);
		logLinearTest(startPoint, endPoint, targetDate, _EPSILON, 1.472357);}
	{
		date targetDate(2012,12,15);
		logLinearTest(startPoint, endPoint, targetDate, _EPSILON, 4.699505);}
	{
		date targetDate(2012,12,7);
		logLinearTest(startPoint, endPoint, targetDate, _EPSILON, 1);}
	{
		date targetDate(2012,12,21);
		logLinearTest(startPoint, endPoint, targetDate, _EPSILON, 15);}
}

void TestInterpolator::linearTest(point startPoint, point endPoint, date targetDate, double tolerance, double expectedVal){
	LinearInterpolator li( startPoint, endPoint);
	double derivedVal = std::get<1>(li.interpolate(targetDate));
	compareResult("Linear Interpolation",derivedVal, expectedVal, startPoint, endPoint, targetDate);
}

void TestInterpolator::logLinearTest(point startPoint, point endPoint, date targetDate, double tolerance, double expectedVal){
	LogLinearInterpolator li( startPoint, endPoint);
	double derivedVal = std::get<1>(li.interpolate(targetDate));
	compareResult("LogLinear Interpolation",derivedVal, expectedVal, startPoint, endPoint, targetDate);
}

void TestInterpolator::compareResult(string testName, double derivedVal, double expectedVal, point startPoint, point endPoint, date targetDate){
	std::stringstream ss (stringstream::in | stringstream::out);
	if (abs(derivedVal-expectedVal)>_EPSILON)
		ss<<testName<<" Test Failed: startPoint["<<getString(startPoint)<<"], endPoint["<<getString(endPoint)<<"], value found ["<<derivedVal<<"], desired value ["<<expectedVal<<"], date ["+targetDate.toString()+"]";
	else
		ss<<testName<<" Test Passed: startPoint["<<getString(startPoint)<<"], endPoint["<<getString(endPoint)<<"], value found ["<<derivedVal<<"], date ["+targetDate.toString()+"]";
	cout<<ss.str()<<endl;
}

string TestInterpolator::getString(point point0){
	std::stringstream ss (stringstream::in | stringstream::out);
	ss<<std::get<0>(point0).toString()<<": "<<std::get<1>(point0);
	return ss.str();
}