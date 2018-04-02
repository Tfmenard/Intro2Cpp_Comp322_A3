#pragma once
/*
SmartPointer Class.
Author: Thomas Faribault-Menard
Date: April 1st 2018
Company: $tack Bundles Inc.

How to use it:

For single value smart pointers, use the constructors with only a single argument.
For array smart pointers, user the constructors with 2 arguments.

To get and set values, make sure to use the appropriate functions for arrays and single value smart pointers.
If you mess up, the appropriate EXCEPTION will be thrown at your exceptional reading talent.

The class supports operator overloading for the add(+), substract(-) and multiply(*) operators.
For arrays, make sure to use arrays of the same dimension when using overlaoded operators.







*/




#include "NegativeNumberException.h"
#include "ArrayOutOfBoundsException.h"
#include "ArrayDimensionsMismatchException.h"

using namespace std;

//Exception objects used in member functions
NegativeNumberException negativeNumException;
ArrayOutOfBoundsException arrayOutOfBoundException;
ArrayDimensionsMismatchException arrDimensionsMismatchException;

template <typename T>
class SmartPointer
{

private:

	T * data;
	int size;

public:
	SmartPointer();
	SmartPointer(T inputData);
	~SmartPointer();

	SmartPointer(T * inputArray, int size);
	SmartPointer(T initialValue, size_t size);

	T getValue();
	void setValue(T inputData);

	void setValue(int index, T data);
	T getValue(int index);

	void displayContent();
	

	friend SmartPointer<T> operator+<T>(const SmartPointer<T>& a, const SmartPointer<T>& b);
	friend SmartPointer<T> operator-<T>(const SmartPointer<T>& a, const SmartPointer<T>& b);
	friend SmartPointer<T> operator*(const SmartPointer<T>& a, const SmartPointer<T>& b)
	{
		if (a.size != b.size)
		{
			throw arrDimensionsMismatchException;
		}

		size_t sizeT = a.size;
		SmartPointer<T> *result = new SmartPointer<T>(0, sizeT);
		result->size = a.size;
		for (int i = 0; i < a.size; i++)
		{
			result->setValue(i, *(a.data + i) * (*(b.data + i)));
		}
		return *result;
		
	}


};



//Default constructor for Single Value Array
template<typename T>
SmartPointer<T>::SmartPointer()
{
	this->data = new T;
	*(this->data) = 0;
	this->size = 1;

}

//Constructor for Single Value Array with input data
template<typename T>
SmartPointer<T>::SmartPointer(T inputData)
{
	//Check for OutOfMemory Exception
	try
	{
		this->data = new T;
	}
	catch (std::bad_alloc& ex)
	{
		cout << "Error. Exception " << ex.what() << "Could not allocate memory to member variable <data> as system is Out Of Memory" << endl;
	}

	//Check for Negative Number Exception and Set value to 0 if value is indeed negative
	try
	{
		this->setValue(inputData);
		this->size = 1;
	}
	catch (NegativeNumberException& e)
	{
		cout << e.what() << endl;
		cout << "Setting <data> to 0" << endl;
		this->setValue(0);
		return;
	}


}


//Getter for single value array. Returns the first and only value of the array
template <typename T>
T SmartPointer<T>::getValue()
{
	return *(this->data);
}


//Setter for Single Value Array. Sets the first and only value of the array
template <typename T>
void SmartPointer<T>::setValue(T inputData)
{
	//Check for Negative Number Exception
	if (inputData < 0)
	{
		throw negativeNumException;
	}

	//Set single to input value
	*(this->data) = inputData;
}


//Question 5 -> OPERATOR OVERLOADING - BEGIN 
//compatible with single value and multiple value array
template <typename T>
SmartPointer<T> operator+(const SmartPointer<T>& a, const SmartPointer<T>& b)
{
	if (a.size != b.size)
	{
		throw arrDimensionsMismatchException;
	}

	size_t sizeT = a.size;
	SmartPointer<T> *result = new SmartPointer<T>(0, sizeT);
	result->size = a.size;
	for (int i = 0; i < a.size; i++)
	{
		//cout << *(a.data+i) << endl;
		//cout << *(b.data+i) << endl;
		result->setValue(i, *(a.data+i) + *(b.data+i));
	}
	return *result;
}


template <typename T>
SmartPointer<T> operator-(const SmartPointer<T>& a, const SmartPointer<T>& b)
{

	if (a.size != b.size)
	{
		throw arrDimensionsMismatchException;
	}

	size_t sizeT = a.size;
	SmartPointer<T> *result = new SmartPointer<T>(0, sizeT);
	result->size = a.size;
	for (int i = 0; i < a.size; i++)
	{
		//cout << *(a.data + i) << endl;
		//cout << *(b.data + i) << endl;
		result->setValue(i, *(a.data + i) - *(b.data + i));
	}
	return *result;
}
//Question 5 -> OPERATOR OVERLOADING - END



//Question 6 -> Extending SmartPointer to handle arrays - BEGIN.
//**Note that small changes had to be made to previously implemented functions to properly handle array allocation

//Destructor.
//Destroys single value or allocated heap depending on array size
template <typename T>
SmartPointer<T>::~SmartPointer()
{

	if (this->size == 1)
	{
		cout << "SmartPointer Destructor Called for Single Value" << endl;
		delete this->data;
	}
	else
	{
		cout << "SmartPointer Destructor Called for Array" << endl;
		delete[] this->data;
	}
}


//Constructor to create SmartPointer to Array
template <typename T>
SmartPointer<T>::SmartPointer(T * inputArray, int size)
{
	//Check for OutOfMemory Exception
	try
	{
		this->data = new T[size];
	}
	catch (std::bad_alloc& ex)
	{
		cout << "Error. Exception " << ex.what() << "Could not allocate memory to member variable <data> as system is Out Of Memory" << endl;
	}

	//Set size of array
	this->size = size;

	//Loop through input array, Check for Negative Number Exception, and copy values into SmartPointer if valid
	//If not valid set the value to 0
	for (int i = 0; i < size; i++)
	{
		try
		{
			this->setValue(i, *(inputArray + i));
		}
		catch (NegativeNumberException &e)
		{
			cout << e.what() << endl;
			cout << "Setting <data> to 0 for index i = " << i << endl;
			this->setValue(i, 0);
		}
	}
}

//Initialize Array of a certain size with the same value for all elements
template <typename T>
SmartPointer<T>::SmartPointer(T initialValue, size_t size)
{
	//Check for OutOfMemory Exception
	try
	{
		this->data = new T[size];
	}
	catch (std::bad_alloc& ex)
	{
		cout << "Error. Exception " << ex.what() << "Could not allocate memory to member variable <data> as system is Out Of Memory" << endl;
	}

	//Set Size Of Array
	this->size = size;

	//Loop through input array, Check for Negative Number Exception, and copy values into SmartPointer if valid.
	//If not valid set the value to 0
	for (int i = 0; i < size; i++)
	{
		try
		{
			this->setValue(i, initialValue);
		}
		catch (NegativeNumberException &e)
		{
			cout << e.what() << endl;
			cout << "Setting <data> to 0 for index i = " << i << endl;
			this->setValue(i, 0);
		}
	}
}

//Function used to display all content, array of single value, pointed by SmartPointer
template <typename T>
void SmartPointer<T>::displayContent()
{
	cout << "Diplaying Content of Pointee" << endl;
	for (int i = 0; i < this->size; i++)
	{
		cout << *(this->data + i) << ",";
	}
	cout << endl;
}

//Setter function for multi value array
template <typename T>
void SmartPointer<T>::setValue(int index, T data)
{
	//Check index given to see if it points Out Of Bound and throw exception if it is the case
	if (index > size - 1)
	{
		throw arrayOutOfBoundException;
	}

	//Check for Negative Number Exception
	if (data < 0)
	{
		throw negativeNumException;
	}

	//Set input value at input index
	*(this->data + index) = data;

}

//Getter function for multi value array
template <typename T>
T SmartPointer<T>::getValue(int index)
{
	//Check index given to see if it points Out Of Bound and throw exception if it is the case
	if (index > this->size - 1)
	{
		throw arrayOutOfBoundException;
	}

	return this->data[index];
}
//Question 6 -> Extending SmartPointer to handle arrays - END

