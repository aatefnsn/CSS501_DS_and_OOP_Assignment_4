#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <iterator>
using namespace std; 

class CompressedString {
public:
	vector <char> charVector; // char vector memeber variable of the class 

	CompressedString(string str); // constructor 
	void printCompressedString(); // print the compressed string vector 
	double calculateCompressionRate(vector<char> vec, string str); // calculate the compression rate
	friend ostream& operator<<(ostream &outstream, const CompressedString &compressedstring); // operator overload 
	//to decompress the vector back into the original string
};