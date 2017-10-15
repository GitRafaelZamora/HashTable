#include <iostream>
#include <string>
#include <math.h>

#include "hash.h"
using namespace std;

// Constructor to intilize the hashtable.
hashClass::hashClass(int size) {
	// cout << "Start Constructor: hashClass()" << endl;
	this->table_size = size;
	HashTable = new item*[size];

	// Initialize all the buckets;
	for(int i = 0; i < this->table_size; i++) {
		HashTable[i] = new item;
		HashTable[i]->key = this->EMPTY;
		HashTable[i]->value = this->EMPTY;
		HashTable[i]->next = NULL;

		// cout << "Key: " << HashTable[i]->key <<
		// 	    " Value: " << HashTable[i]->value <<
		// 		" Next: " << HashTable[i]->next << endl;
	}
	// cout << "End Constructor: hashClass()" << endl;
}

void hashClass::reset() {
	// Initialize all the buckets;
	for(int i = 0; i < this->table_size; i++) {
		HashTable[i] = new item;
		HashTable[i]->key = this->EMPTY;
		HashTable[i]->value = this->EMPTY;
		HashTable[i]->next = NULL;

		// cout << "Key: " << HashTable[i]->key <<
		// 	    " Value: " << HashTable[i]->value <<
		// 		" Next: " << HashTable[i]->next << endl;
	}
}


// A simple hash function. Returns a key for a given value.
int hashClass::chainedHash(int value) {
	return value % this->table_size;
}
	
// Inserts a given value into the HashTable.
void hashClass::insert(int key, int value) {
	// cout << "Start chainedHashInsert()" << endl;

	// hash the value to get the which bucket it will be inserted to.
	int bucket = key;

	// Check if the bucket is empty. If it is then copy the value into the bucket.
	if (HashTable[bucket]->key == this->EMPTY) {
		HashTable[bucket]->key = bucket;
		HashTable[bucket]->value = value;
	} else { // Traverse through the bucket to find the last item. Then insert the item to the end of the list.
		item* Pointer = HashTable[bucket];
		item* n = new item;
		n->key = bucket;
		n->value = value;
		n->next = NULL;
		while (Pointer->next != NULL) {
			Pointer = Pointer->next;
		}
		Pointer->next = n;
	}
	// cout << "End chainedHashInsert()" << endl;
}



// Traverses through given bucket incrementing count until it reachs the last node in the list.
//		Returns the size of the bucket.
int hashClass::numberOfItemsInBucket(int bucket) {
	int count = 0;
	if (HashTable[bucket]->key == this->EMPTY) {
		return count;
	} else {
		count++;
		item* Pointer = HashTable[bucket];
		while(Pointer->next != NULL) {
			count++;
			Pointer = Pointer->next;
		}
	}
	return count;
}

// Prints the HashTable.
void hashClass::printTable() {
	int number;
	for (int i = 0; i < this->table_size; i++) {
		number = numberOfItemsInBucket(i);
		cout << "--------------" << endl;
		cout << "index = " << i << endl;
		cout << HashTable[i]->key << endl;
		cout << HashTable[i]->value << endl;
		cout << "# of items = " << number << endl;
		cout << "--------------" << endl;
	}
}

// Prints the contents of a given Bucket.
void hashClass::printItemsInBucket(int bucket) {
	item* Pointer = HashTable[bucket];

	if (Pointer->key == this->EMPTY) {
		cout << "Bucket: " << bucket << " is empty." << endl;
	} else {
		cout << "Bucket: " << bucket << " contains the following." << endl;
		while (Pointer != NULL) {
			cout << "-------------" << endl;
			cout << "Key: " << Pointer->key << endl;
			cout << "Value: " <<Pointer->value << endl;
			cout << "-------------" << endl;
			Pointer = Pointer->next;
		}
	}
}

// Searches for the value given a key and a value.
void hashClass::chainedSearch(int key, int searchVal) {
	int bucket = key;
	bool foundVal = false;
	item* Pointer = HashTable[bucket];

	while (Pointer != NULL) {
		if (Pointer->value == searchVal) {
			foundVal = true;
		}
		Pointer = Pointer->next;
	}

	if (foundVal) {
		cout << "Search Successful!" << endl;
	} else {
		cout << "Search Not Found." << endl;
	}
}



// A simple getter function to access the size of the table.
int hashClass::getTableSize() {
	return this->table_size;
}

double hashClass::getAlpha() {
	return this->alpha;
}

void hashClass::setAlpha(double alpha) {
	this->alpha = alpha;
}

void hashClass::printChainedHash() {
	string outString;
	item* Pointer;
	for (int i = 0; i < this->table_size; i++) {
		Pointer = HashTable[i];
		cout << "[" << i << "] ";
		while(Pointer != NULL) {
			if (HashTable[i]->value == this->EMPTY) {

			} else {
				cout << Pointer->value << " ";
			}
			Pointer = Pointer->next;
		}
		cout << endl;
	}
}

void hashClass::linearInsert(int key, int value) {
	int bucket = key;

	if (HashTable[bucket]->key == this->EMPTY) {
		// cout << "Insert in Bucket: " << bucket << endl;
		HashTable[bucket]->key = bucket;
		HashTable[bucket]->value = value;
	} else {
		if (bucket == this->table_size - 1) {
			// cout << "WrapAround key = 0" << endl;
			key = 0;
			linearInsert(key, value);
		} else {
			// cout << "Try to Insert: " << key << " " ;
			linearInsert(key + 1, value);
		}
		
	}
}

// 
int hashClass::linearHash(int value) {
	return floor(this->table_size * (fmod((this->alpha * value), 1)));
}

void hashClass::linearSearch(int key, int value) {
	int bucket = key;
	int startKey = key;
	if (HashTable[bucket]->value == value) {
		//Successful Search
		cout << "Successful Search!" << endl;
	} else {
		if (bucket == this->table_size - 1) {
			// cout << "WrapAround key = 0" << endl;
			key = 0;
			linearSearch(key, value);
		} else if (startKey == key) {
			cout << "Unsuccessful Search!" << endl;
		} else {
			// cout << "Try to Insert: " << key << " " ;
			linearSearch(key + 1, value);
		}
		
	}
}










