/* 
 * File:   main.cpp
 * Author: Kevser Yolcu 131044072
 *
 * Created on November 2, 2015, 10:05 PM
 */

#include "newfile.h"




int main()
{
	Triangle side1;
	Triangle side2(3.0, 4.0, 5.0);

	function1(side2);//call by reference example
	function2(side2);//call by value example


	return 0;
}





