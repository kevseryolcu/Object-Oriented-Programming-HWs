/*
 * File:   main.cpp
 * Author: Kevser Yolcu
 *
 * Created on 25 Ekim 2015
 *
 *
 *Verilen bir arrayde en cok tekrar eden elemanın
 * indexini donduren program
 */

#include <iostream>
using namespace std;

//again arrayinin size i
const int N(150);

class DayOfYear
{
public:
        int day;
	int month;
	int year;
};

class Person
{
public:
	double height;
	double weight;

};

bool (equals_int)(const void * x, const void *y);
bool (equals_double)(const void * x, const void *y);
bool (equals_char)(const void * x, const void *y);
bool (equals_DayOfYear)(const void * x, const void *y);
bool (equals_Person)(const void * x, const void *y);

int return_mode(const void* base, size_t num, size_t size,
				bool (*equals)(const void * , const void *));

int find_max_count(int arr[], int size);


int main()
{
    int array1[9] = {-2,-2,-50,4,33,0,-2,3};
    double array2[8] = {4.12, 3.12, 30.1, 21.6, 21.6, 0.1, 21.6, 0.8};
    char  array3[8] = {'k','y','x','a','i','x', '5' ,'x'};
    DayOfYear array4[4] = {{13,12,1996},{10,04,2004},{23,9,2015},{23,9,2015}};
    Person array5[7] = {{1.2, 22.0},{1.9, 82.0},{1.9, 82.0},{1.72, 51.0},{2.0, 105.0},{1.65, 47.5},{1.72, 51.0}};
    int max1, max2, max3, max4, max5;

    cout << "int arrayde gercek index " << 0 << endl;
    max1 =  return_mode(array1,8,sizeof(int),equals_int);
    cout << "int arrayde fonksiyonun buldugu index " << max1 << endl<<endl;

    cout << "double arrayde gercek index " << 3 << endl;
    max2 = return_mode(array2,8,sizeof(double),equals_double);
    cout << "double arrayde fonksiyonun buldugu index " << max2 << endl << endl;

    cout << "char arrayinde gercek index " << 2 << endl;
    max3 = return_mode(array3,8,sizeof(char),equals_char);
    cout << "char arrayinde fonksiyonun buldugu index " << max3 << endl<< endl;

    cout << "DayOfYear  arrayinde gercek index " << 2 << endl;
    max4 = return_mode(array4,4,sizeof(DayOfYear),equals_DayOfYear);
    cout << "DayOfYear arrayinde fonksiyonun buldugu index " << max4 << endl << endl;

    cout << "Person arrayinde gercek index " << 1 << endl;
    max5 = return_mode(array5,7,sizeof(Person),equals_Person);
    cout << "Person arrayinde fonksiyonun buldugu index " << max5 << endl<< endl;

    return 0;
}


//Verilen bir arrayde en cok tekrar eden elemanın
 // indexini dondurur
int return_mode(const void* base, size_t num, size_t size,
				bool (*equals)(const void * , const void *))
{
	bool k;//equals fonksiyonunun sonucu bu degiskene atanir
	int   tmp_count = 0, //bir degerin kac kere tekrar ettigini tutan degisken
                i = 0,
                j = 0,
                index;// en cok tekrar eden elemanin indexini
                         //find_max_count fonksiyonundan alir
	void  *tmp_value;// arrayin bulundugu elemani tutuyor
	char* array = (char*)base;// array eleman larini sayabilmek icin yaptim
        int again[N] = {};// tekrar sayilarini tutar

	if(num > 0)//array elemana sahip mi diye kontrol eder
	{
		for(j = 0; j < num; ++j)
		{
                        tmp_value = (array + j*size);
			for(i = j;  i< num; ++i)
			{
				k = (*equals)((void*)(tmp_value), (void*)(array + i*size));
				if(k)// gonderilen iki eleman esitse tmp_countu 1 arttirir
				{
					tmp_count += 1;
				}
			}
                        again[j] = tmp_count;//arrayin o anki elemaninin tekrarini
                                                            //again arrayine atar
                        tmp_count = 0;
		}

                //max tekrari bulur
                 index = find_max_count(again, num);
                 return index;
	}
        else    //array elemana sahip degilse 0 return eder
            return i;

}

//return_mode icinde kullanılır
//verilen arraydeki en buyuk elemani bulur
int find_max_count(int arr[], int size)
{
    int max;
    int i, index = 0;
    max = arr[0];

    for(i  = 0; i <size; ++i)
    {
        if(arr[i] > max)
        {
            max = arr[i];
            index = i;
        }
    }
    return index;
}

bool (equals_int)(const void * x, const void *y)
{
	return(*(int*)x == *(int*)y);
}

bool (equals_double)(const void * x, const void *y)
{
	return(*(double*)x == *(double*)y);
}

bool (equals_char)(const void * x, const void *y)
{
	return(*(char*)x == *(char*)y);
}

bool (equals_DayOfYear)(const void * x, const void *y)
{
	return(          ((*(DayOfYear*)x).month == (*(DayOfYear*)y).month)
		      && ((*(DayOfYear*)x).day == (*(DayOfYear*)y).day)
		      &&  ((*(DayOfYear*)x).year == (*(DayOfYear*)y).year)       );
}

bool (equals_Person)(const void * x, const void *y)
{
	return(( (*(Person*)x).height == (*(Person*)y).height) &&
		   ( (*(Person*)x).weight == (*(Person*)y).weight));
}
