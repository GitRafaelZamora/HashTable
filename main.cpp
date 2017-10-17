#include <iostream>
#include <fstream>
#include <string>

#include "hash.h"
#include "File.h"
#include "hash.cpp"
#include "File.cpp"


using namespace std;

int main () {
	double* file_data;
	int table_size;
	double alpha;
	int numValues;
	int searchVal;

	// Processing file data.
	File inFile("input.txt", "in");
	file_data = inFile.parseData(file_data);
	// file.printData(file_data[2], file_data);
	inFile.close();

	// Grabbing the size of the table from file_data.
	table_size = file_data[0];
	numValues = file_data[2];
	searchVal = file_data[(numValues+2)];
	
	// Constructing a HashTable of size table_size
	hashClass Hashy(table_size);
	Hashy.setAlpha(file_data[1]);

	int key;
	int value;

	// TEST 1
	// Going through all the file_data and hashing them then inserting values into the HASHTABLE.
	File outFile("output.txt", "out");
	cout << "CHAINED HASHTABLE" << endl;
	for (int i = 0; i < numValues; i++) {
		value = file_data[i+3];
		key = Hashy.chainedHash(value);
		Hashy.chainedInsert(key, value);
	}
	outFile.write(Hashy.printChainedHash());
	outFile.write(Hashy.chainedSearch(Hashy.chainedHash(searchVal), searchVal));
	Hashy.reset();

	//TEST 2
	cout << "LINEAR HASHTABLE" << endl;
	for (int i = 0; i < numValues; i++) {
		value = file_data[i+3];
		// cout << value << " " << endl;
		key = Hashy.linearHash(value);
		// cout << key << " " << endl;
		Hashy.linearInsert(key, value);
	}
	outFile.write(Hashy.printChainedHash());
	outFile.write(Hashy.linearSearch(Hashy.linearHash(searchVal), searchVal, ""));
	cout << endl;
	Hashy.reset();

	//TEST 3 
	cout << "DOUBLE HASHTABLE" << endl;
	for (int i = 0; i < numValues; i++) {
		// cout << i+3;
		value = file_data[i+3];
		// cout << ": " << value << " " << endl;
		key = Hashy.hash1(value);
		// cout << "Key: " << key << " " << endl;
		Hashy.insertDoubleHash(key, value, 0);
	}
	outFile.write(Hashy.printChainedHash());
	outFile.write(Hashy.doubleHashSearch(Hashy.chainedHash(searchVal), searchVal, 0, ""));
	Hashy.reset();

	return 0;
}