/* 
 * File:   newfile.h
 * Author: Kevser Yolcu 131044072
 *
 * Created on November 2, 2015, 10:05 PM
 */

#ifndef _NEWFILE_H
#define	_NEWFILE_H



#endif	/* _NEWFILE_H */

#include <iostream>
#include <math.h>
#include <stdlib.h>//exit icin


using namespace std;

class Triangle
{
public:
	Triangle();
	Triangle(double sides_length);
	Triangle(double side_A, double side_B);
	Triangle(double side_A, double side_B, double side_C);
	void input();
	void outputA() const;
	void outputB() const;
	void outputC() const;
	void outputSides() const;
	void setSideA(double side);
	void setSideB(double side);
	void setSideC(double side);
	void setSides(double side1, double side2, double side3);
	double getSideA() const;
	double getSideB() const;
	double getSideC() const;
	double AngleOfA() const;//angle of sideA
	double AngleOfB() const;//angle of sideB
	double AngleOfC() const;
	bool RightAngle() const;
	double AreaOfTriangle() const;
	double PerimeterOfTriangle() const;

private:
	double sideA;
	double sideB;
	double sideC;
};

const double PI = 3.14285714;

void function1(Triangle& value);
void function2(Triangle side);
