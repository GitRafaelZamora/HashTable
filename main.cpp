#include <iostream>
#include <fstream>
#include <string>

#include "hash.h"
#include "File.h"

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
	cout << Hashy.printChainedHash();
	Hashy.chainedSearch(Hashy.chainedHash(searchVal), searchVal);
	Hashy.reset();

	//TEST 2
	// cout << "LINEAR HASHTABLE" << endl;
	// for (int i = 0; i < numValues; i++) {
	// 	value = file_data[i+3];
	// 	// cout << value << " " << endl;
	// 	key = Hashy.linearHash(value);
	// 	// cout << key << " " << endl;
	// 	Hashy.linearInsert(key, value);
	// }
	// cout << Hashy.printChainedHash();
	// Hashy.linearSearch(Hashy.linearHash(35), 35);
	// Hashy.reset();

	//TEST 3 
	// for (int i = 0; i < numValues; i++) {
	// 	// cout << i+3;
	// 	value = file_data[i+3];
	// 	// cout << ": " << value << " " << endl;
	// 	key = Hashy.hash1(value);
	// 	// cout << "Key: " << key << " " << endl;
	// 	Hashy.insertDoubleHash(key, value);
	// }
	// cout << "DOUBLE HASHTABLE" << endl;
	// cout << Hashy.printChainedHash();
	// Hashy.linearSearch(Hashy.linearHash(35), 35);
	// Hashy.reset();

	


	return 0;
}