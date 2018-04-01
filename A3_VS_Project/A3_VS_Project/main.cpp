#include "main.h"
#include "SmartPointer.h"


int main()
{
	
	cout << "--- Question 2 ---" << endl;
	SmartPointer<int> sPointer1;
	SmartPointer<int> sPointer2(2);
	
	
	cout << "sPointer1 default value = " << sPointer1.getValue() << endl;
	sPointer1.setValue(3);
	cout << "sPointer1 newly set value = " << sPointer1.getValue() << endl;

	cout << "sPointer2 value = " << sPointer2.getValue() << endl;

	cout << endl;

	cout << "--- Question 3 ---" << endl;

	cout << "Trying to set negative number to sPointer1" << endl;

	try
	{
		sPointer1.setValue(-1);
	}
	catch(exception &e)
	{
		cout << e.what() << endl;
	}
	
	cout << "Value of sPointer1 is still " << sPointer1.getValue() << endl << endl;


	cout << "Attempt to construct sPointer3 with negative value of -1" << endl;
	SmartPointer<int> sPointer3(-1);
	cout << "Value of sPointer3 = " << sPointer3.getValue() << endl << endl;


	cout << "--- Question 4 ---" << endl;

	cout << "Creating sPointer of different types" << endl;
	SmartPointer<double> sPointerDouble1(13.1);
	SmartPointer<float> sPointerFloat1;
	sPointerFloat1.setValue(1.5);
	SmartPointer<float> sPointerFloat2(2.5);

	cout << "Value of sPointerDouble1 = " << sPointerDouble1.getValue() << endl;
	cout << "Value of sPointerFloat1 = " << sPointerFloat1.getValue() << endl << endl;

	cout << "--- Question 5 ---" << endl;

	cout << "Using operator+ overloading of operator+ and operator- on SmartPointer class" << endl;
	cout << "operator+" << endl;
	SmartPointer<float> sPointerFloat3 = sPointerFloat1 + sPointerFloat2;
	cout << "sPointerFloat3 value -> 1.5 + 2.5 = " << sPointerFloat3.getValue() << endl;

	cout << "operator-" << endl;
	SmartPointer<float> sPointerFloat4 = sPointerFloat2 - sPointerFloat1;
	cout << "sPointerFloat4 value -> 2.5 - 1.5 = " << sPointerFloat4.getValue() << endl << endl;

	//SmartPointer<float> sPointerFloat5 = sPointerFloat1 * sPointerFloat2;
	//cout << "sPointerFloat3 value = " << sPointerFloat5.getValue() << endl;

	cout << "--- Question 6 ---" << endl;

	cout << "Initializing Array SmartPointer" << endl;

	int intArray_size2[2]{ 1,2 };
	SmartPointer<int> sPointerArray1(intArray_size2, 2);
	cout << "Array of Size 2 initialized to:" << endl;
	sPointerArray1.displayContent();

	int intArray_size3[3]{ 1,2,3 };
	SmartPointer<int> sPointerArray2(intArray_size3, 3);
	SmartPointer<int> sPointerArray3(intArray_size3, 3);

	cout << "Array of Size 3 initialized to:" << endl;
	sPointerArray2.displayContent();

	cout << "Array of Size 3 initialized to:" << endl;
	sPointerArray3.displayContent();

	//Question 6 with Question 5 Extended -> Operator Overloading for arrays
	cout << "Question 6 with Question 5 Extended -> Operator Overloading for arrays" << endl;
	cout << "Adding array with another array with mismatched dimensions" << endl;
	try 
	{
		SmartPointer<int> sPointerArray_invalid_op = sPointerArray1 + sPointerArray2;
	}
	catch (exception &e)
	{
		cout << e.what() << endl;
	
	}

	cout << "Adding array with another array" << endl;
	try
	{
		SmartPointer<int> sPointerArray_valid_op = sPointerArray3 + sPointerArray2;
		sPointerArray_valid_op.displayContent();
	}
	catch (exception &e)
	{
		cout << e.what() << endl;
	}

	cout << "Substracting array with another array" << endl;
	try
	{
		SmartPointer<int> sPointerArray_valid_op = sPointerArray3 - sPointerArray2;
		sPointerArray_valid_op.displayContent();
	}
	catch (exception &e)
	{
		cout << e.what() << endl;
	}

	return 0;
}
