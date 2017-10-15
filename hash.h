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
	};
	item** HashTable = NULL;

public:
	//Prototypes:
	hashClass(int table_size); //Constructor for our Hash Table;
	void insert(int key, int value); // A simple linear hash function returns k % p;
	void linearInsert(int key, int value);
	int numberOfItemsInBucket(int bucket);
	void printTable();
	void printItemsInBucket(int bucket);
	void chainedSearch(int key, int value);
	int chainedHash(int value);
	int linearHash(int value);
	void linearSearch(int key, int value);
	int getTableSize();
	void setAlpha(double alpha);
	double getAlpha();

	void printChainedHash();
	void reset();


};