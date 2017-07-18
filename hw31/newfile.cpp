

#include "newfile.h"


Triangle::Triangle(): sideA(1.0), sideB(1.0), sideC(1.0)
{	}

Triangle::Triangle(double sides_length)
{
	if(sides_length > 0)
	{
		sideA = sides_length;
		sideB = sides_length;
		sideC = sides_length;
	}
	else
	{
		cerr << "Illegal side length." << endl;
		exit (1);
	}
}

Triangle::Triangle(double side_A, double side_B):sideC(1.0)
{
	if(side_A > 0 && side_B > 0)
	{
		sideA = side_A;
		sideB = side_B;
	}
	else
	{
		cerr << "Illegal side length." << endl;
		exit (1);
	}
}

Triangle::Triangle(double side_A, double side_B, double side_C)
{
	if(side_A > 0 && side_B > 0 && side_C > 0)
	{
		sideA = side_A;
		sideB = side_B;
		sideC = side_C;
	}
	else
	{
		cerr << "Illegal side length." << endl;
		exit (1);
	}
}

void Triangle::input()
{
	cout << "Enter side A, side B and, side C" << endl;
	cin >> sideA >> sideB >> sideC;
	setSides(sideA, sideB, sideC);	
}

void Triangle::outputA() const
{	cout << "Side A : " << sideA << endl;	}

void Triangle::outputB() const
{	cout << "Side B : " << sideB << endl;	}

void Triangle::outputC() const
{	cout << "Side C : " << sideC << endl;	}

void Triangle::outputSides() const
{
	cout << "Side A : " << sideA << endl;
	cout << "Side B : " << sideB << endl;
	cout << "Side C : " << sideC << endl;
}

void Triangle::setSideA(double side)
{
	if(side < 0)
	{
		cerr << "Illegal length for sideA." << endl;
		exit(1);
	}
	else
		sideA = side;
}

void Triangle::setSideB(double side)
{
	if(side < 0)
	{
		cerr << "Illegal length for sideB." << endl;
		exit(1);
	}
	else
		sideB = side;
}

void Triangle::setSideC(double side)
{
	if(side < 0)
	{
		cerr << "Illegal length for sideC" << endl;
		exit(1);
	}
	else
		sideC=side;
}

void Triangle::setSides(double side1, double side2, double side3)
{
	if( side2 > fabs(side1 - side3) &&
		 (side2 < side1 + side3) &&
		  side1 > 0 && side2 > 0 && side3 > 0)
	{
		sideA = side1;
		sideB = side2;
		sideC = side3;
	}
	else
	{
		cerr << "Illegal sides of length." << endl;
		exit(1);
	}

}

double Triangle::getSideA() const
{
	return sideA;
}
double Triangle::getSideB() const
{
	return sideB;
}
double Triangle::getSideC() const
{
	return sideC;
}

double Triangle::AngleOfA() const//angle of sideA
{
	double cosA;
	cosA = (-pow(sideA,2) + pow(sideB,2) + pow(sideC,2))/(2*sideC*sideB);

	//cosinusteoremi c^2 = a^2 + b^2 -2abcosA; burada cosA yi yalniz biraktim
	return (acos(cosA)*(180.0/PI)); //radyan i dereceye cevirmek icin 180/PI ile carptim
}

double Triangle::AngleOfB() const//angle of sideB
{
	double cosB;
	cosB = (-pow(sideB,2) + pow(sideC,2) + pow(sideA,2))/(2*sideA*sideC);
	//cosinusteoremi c^2 = a^2 + b^2 -2abcosA; burada cosA yi yalniz biraktim
	return (acos(cosB)*(180.0/PI));
}

double Triangle::AngleOfC() const//angle of sideC
{
	double cosC;
	cosC = (-pow(sideC,2) + pow(sideB,2) + pow(sideA,2))/(2*sideA*sideB);

	//cosinusteoremi c^2 = a^2 + b^2 -2abcosA; burada cosA yi yalniz biraktim
	return (acos(cosC)*(180.0/PI));
}

//ucgenin dik ucgen olup olmadigini bulur
bool Triangle::RightAngle() const//a^2 b#2
{
	if( (pow(sideA, 2) == pow(sideB, 2) + pow(sideC, 2) ) ||
		(pow(sideB, 2) == pow(sideA, 2) + pow(sideC, 2) ) ||
		(pow(sideC, 2) == pow(sideB, 2) + pow(sideA, 2) ))
	{	return true;	}
	else
		return false;
}

double Triangle::AreaOfTriangle() const
{//bu fonksiyonda [u(u-a)(u-b)(u-c)]^(1/2)	formulunu kullandim
//burada u cevrenin yarisi; a,b,c kenarlar olmak uzere
	double u;
	u = (0.5)*PerimeterOfTriangle();// 0.5 yani 1/2
	return( sqrt( u*(u-sideA)*(u-sideB)*(u-sideC) ) );
}

double Triangle::PerimeterOfTriangle() const
{
	return(sideA + sideB + sideC);
}

void function1(Triangle& value)
{
	value.input();
	value.setSideA(value.getSideA());
	value.setSideB(value.getSideB());
	value.setSideC(value.getSideC());
}

void function2(Triangle side)
{
	side.outputA();
	side.outputB();
	side.outputC();
	cout << "Angle of A " << side.AngleOfA() << endl;//angle of sideA
	cout << "Angle of B " << side.AngleOfB() << endl;
	cout << "Angle of C " << side.AngleOfC() << endl << endl;
	cout << "Area of triangle " << side.AreaOfTriangle() << endl << endl;
	cout << "Perimeter of triangle " << side.PerimeterOfTriangle() << endl << endl;
	if(side.RightAngle())
	{	cout << "This triangle is right angle triangle."<< endl << endl;	}
	else
	{	cout << "This triangle is not right angle triangle."<< endl << endl;	}

	Triangle variable;
	variable.setSides(variable.getSideA(), variable.getSideB(), variable.getSideC() );
	variable.outputSides();
}


