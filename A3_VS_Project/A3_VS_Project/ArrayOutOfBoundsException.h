#pragma once
#include <iostream>
#include <cstdlib>
#include <time.h>

class ArrayOutOfBoundsException : public exception
{
public:
	virtual const char* what() const throw()
	{
		return "Error: Index is Out of Bounds";
	}

};

