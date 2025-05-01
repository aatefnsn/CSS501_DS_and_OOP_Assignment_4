#pragma once
#include "pch.h"
#include <vector>
#include <string>
#include <iterator>
#include <iostream>
#include "CompressedString.h"
using namespace std;

CompressedString::CompressedString(string str) { // Big-O is O(n) Constructor as defined takes a String and then stores it inside a vector then compresses it

	vector<char> vec(str.begin(), str.end());	// creating a Char vector to hold the values of the string from begin till end
	char lastchar; // a temp variable to hold the char that we are comparing to 
	vector<char>::iterator vi = vec.begin(); // defining the itirator
	
	while (vi != vec.end()){ // itirating over the char vector once and seeing if the chars are repeating (drop a pointer) 
		//then count occurance in a variable, once the occurances end put that counter into the pointer location 
		
		if (vi == vec.begin()) {	// first iteration to get the last char 		
			lastchar = *vi; 
			vi++;
			continue;
		}
		if (*vi == lastchar) { // check if there is an occurance at least one occurance
			char * p = &(*--vi); // pointer that points to where the counter should be 
			vi++; // move the pointer
			int counter = 1; // and set counter to 1
			while (vi != vec.end() && *vi == lastchar) { // if we are not at the end and if the occurance keeps going, keep incrementing counter
					counter++;	
					if (counter > 2) {
						vi=vec.erase(vi); // if counter is greater than 2 then start removing those extra chars from the vector, 
						//they will be replaced by the number in the begining to represent them
						continue;
					}
					vi++;					
			}
			*p = '0'+ counter;	// dereference the pointer with the value of the counbter + char of 0 to represnet the integer in ASCII 		
		}
		if (vi != vec.end()) { // if wqe are not at the end .. keep on going 
			lastchar = *vi; // update lastChar 
			vi++; // move itirator 
		}				
	}
	this->charVector = vec; // put the final result vector to the vector memeber variable of the class

	cout << "Compression rate is " << calculateCompressionRate(charVector, str) << "%" << endl; // output the compression rate
}

double CompressedString::calculateCompressionRate(vector<char> vec, string str) { // function to calculate the compression rate 
	return (1.0 - ((double)vec.size() / (double)str.size()))*100;
}

ostream& operator<<(ostream &outstream, const CompressedString &compressedstring) { // Big-O O(n) operator overload for cout to print the 
	//decompressed string once again
	vector<char>::const_iterator vi = compressedstring.charVector.begin();	// iterator over the vector
	string st; //result string 
	int counter = 0;	// counter to act as index for where to insert inside the string 
	while (vi != compressedstring.charVector.end()) {				
		string tempstring; // temp string to hold the values of the chars that are being decompressed to be apeended to the resultant string
		if (int(*vi) > 57) { // char because ASCII int value is over 57
			tempstring.push_back(*vi); // if it is just a char, just push back as it is 
			st.insert(counter, tempstring); // insert the temp string into the st resultant string 
			counter++; // increment the counter by just one place
		}
		if (int(*vi) >= 48 && int(*vi) <= 57) { // integer	if it is in the range of 48 - 57 in ASCII
			int value = (int) *vi-48; // get the int value of the ASCII char by subtracting -48 
			for (int i = 0; i < value; i++) { // do a for loop and keep in pushing back the same letter as many times as the integer
				tempstring.push_back(*(vi+1)); // push back the char that is in the iterator position after the integer hence vi +1 
			}
			st.insert(counter, tempstring); // insert that string to the resulting 
			counter+=value; // increase the counter index by the value of the integer 
			vi++; // move the iterator to go past the integer 
		}
		vi++; // move the iterator one more time to go past the char to the next char
	}
	outstream << "Decompressed string: \n" << st << endl; // input everthing into outstream 
		return outstream;  // return the outstream
}

void CompressedString::printCompressedString() { // function to print the compressed vector 

	vector<char>::iterator v = this->charVector.begin(); // itirator 
	cout << "Compressed string: " << endl;
	while (v != this->charVector.end()) {		 // go over each value in the vector and print it
		cout /*<< "value of v = "*/ << *v;
		v++;
	}
}