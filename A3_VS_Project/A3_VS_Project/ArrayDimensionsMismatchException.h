#pragma once
#include <iostream>
#include <cstdlib>
#include <time.h>

class ArrayDimensionsMismatchException : public exception
{
public:
	virtual const char* what() const throw()
	{
		return "Error: Array Dimensions Don't Match. Unable to Apply Operation";
	}

};