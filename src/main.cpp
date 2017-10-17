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
	File inFile("../input.txt", "in");
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
	File chainedFile("../out/CHAINED_HASH_INSERT.txt", "out");
	// cout << "CHAINED HASHTABLE" << endl;
	for (int i = 0; i < numValues; i++) {
		value = file_data[i+3];
		key = Hashy.chainedHash(value);
		Hashy.chainedInsert(key, value);
	}
	chainedFile.write(Hashy.printChainedHash());
	chainedFile.write(Hashy.chainedSearch(Hashy.chainedHash(searchVal), searchVal));
	chainedFile.close();
	Hashy.reset();

	//TEST 2
	// cout << "LINEAR HASHTABLE" << endl;
	File linearFile("../out/HASH_INSERT_LINEAR.txt", "out");
	for (int i = 0; i < numValues; i++) {
		value = file_data[i+3];
		// cout << value << " " << endl;
		key = Hashy.linearHash(value);
		// cout << key << " " << endl;
		Hashy.linearInsert(key, value);
	}
	linearFile.write(Hashy.printChainedHash());
	linearFile.write(Hashy.linearSearch(Hashy.linearHash(searchVal), searchVal, ""));
	linearFile.close();
	Hashy.reset();

	//TEST 3 
	// cout << "DOUBLE HASHTABLE" << endl;
	File doubleHashFile("../out/HASH_INSERT_DOUBLE.txt", "out");
	for (int i = 0; i < numValues; i++) {
		// cout << i+3;
		value = file_data[i+3];
		// cout << ": " << value << " " << endl;
		key = Hashy.hash1(value);
		// cout << "Key: " << key << " " << endl;
		Hashy.insertDoubleHash(key, value, 0);
	}
	doubleHashFile.write(Hashy.printChainedHash());
	doubleHashFile.write(Hashy.doubleHashSearch(Hashy.chainedHash(searchVal), searchVal, 0, ""));
	doubleHashFile.close();
	Hashy.reset();

	return 0;
}