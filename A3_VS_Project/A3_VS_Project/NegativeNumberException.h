#pragma once
#include <iostream>
#include <cstdlib>
#include <time.h>

class NegativeNumberException : public exception
{
public:
virtual const char* what() const throw()
{
return "Error: Cannot assign a negative number";
}

};


