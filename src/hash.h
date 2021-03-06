#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <string>


using namespace std;

class hashClass {

private:
	int table_size; // Size of our Hash Table;
	double alpha;
	const static int EMPTY = -1;

	struct item {
		int key;
		int value;
		item* next;
	} *head;
	item** HashTable = NULL;

public:
	//Prototypes:
	hashClass(int table_size); //Constructor for our Hash Table;

	void chainedInsert(int key, int value); // A simple linear hash function returns k % p;
	void linearInsert(int key, int value);
	void insertDoubleHash(int key, int value, int i);
	string doubleHashSearch(int key, int value, int i, string outString);

	int numberOfItemsInBucket(int bucket);
	void printTable();
	void printItemsInBucket(int bucket);

	string chainedSearch(int key, int value);
	int chainedHash(int value);
	int linearHash(int value);
	string linearSearch(int key, int value, string outString);
	int doubleHash(int i, int value);
	int hash1(int value);
	int h2(int value);


	int getTableSize();
	void setAlpha(double alpha);
	double getAlpha();

	string printChainedHash();
	void reset();


};
#endif