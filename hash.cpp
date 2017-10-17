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
string hashClass::chainedSearch(int key, int searchVal) {
	int bucket = key;
	bool foundVal = false;
	item* Pointer = HashTable[bucket];
	string foundBucket;

	while (Pointer != NULL) {
		if (Pointer->value == searchVal) {
			foundVal = true;
			foundBucket = to_string(Pointer->key);
		}
		Pointer = Pointer->next;
	}

	if (foundVal) {
		cout << "Search Value " << searchVal << " is in bucket: " << foundBucket << endl;
	} else {
		cout << "Search Not Found." << endl;
	}
	foundBucket += "\n";
	return foundBucket;
}

// Inserts a given value into the HashTable.
void hashClass::chainedInsert(int key, int value) {
	// cout << "Start chainedHashInsert()" << endl;

	// hash the value to get the which bucket it will be inserted to.
	int bucket = key;

	// Check if the bucket is empty. If it is then copy the value into the bucket.
	if (HashTable[bucket]->key == this->EMPTY) {
		HashTable[bucket]->key = bucket;
		HashTable[bucket]->value = value;
	} else { // Traverse through the bucket to find the last item. Then insert the item to the end of the list.
		item* head = HashTable[bucket];

		item* temp = new item;
		temp->key = head->key;
		temp->value = head->value;
		temp->next = head->next;

		head->key = bucket;
		head->value = value;
		head->next = temp;
		
		
		// while (Pointer->next != NULL) {
		// 	Pointer = Pointer->next;
		// }
		// Pointer->next = n;
	}
	// cout << "End chainedHashInsert()" << endl;
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

string hashClass::printChainedHash() {
	string outString;
	item* Pointer;
	for (int i = 0; i < this->table_size; i++) {
		Pointer = HashTable[i];
		outString += "[" + to_string(i) + "] ";
		while(Pointer != NULL) {
			if (HashTable[i]->value == this->EMPTY) {

			} else {
				outString += to_string(Pointer->value) + " ";
			}
			Pointer = Pointer->next;
		}
		outString += "\n";
	}
	return outString;
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

string hashClass::linearSearch(int key, int value, string outString) {
	int bucket = key;
	outString += to_string(key) + " ";
	if (HashTable[bucket]->value == value) {
		// cout << outString;
		// outString += to_string(bucket) + " ";
		// return outString;
	} else {
		if (key == this->table_size - 1) {
			key = 0;
			// cout << outString;
			// outString += to_string(bucket) + " ";
			return linearSearch(key, value, outString + to_string(bucket) + " ");
		} else {
			// cout << outString;
			// outString += to_string(bucket) + " " ;
			return linearSearch(key + 1, value, outString);
		}
	}
	// cout << outString;
	return outString;
}

int hashClass::hash1(int value) {
	return (value % this->table_size);
}

int hashClass::h2(int value) {
 return (1 + (value % (this->table_size - 2)));
}

int hashClass::doubleHash(int i, int value) {
	//cout << "DBHASH:" << (h1(value) + key * h2(value)) % this->table_size << endl;
	return ((hash1(value) + i * h2(value)) % this->table_size);
}

void hashClass::insertDoubleHash(int key, int value, int i) {
	// int bucket = doubleHash(key, value);
	// int bucket = key;
	int newKEY;
	// cout << "table_size: " << this->table_size << endl;
	if (HashTable[key]->key == this->EMPTY) {
		// cout << "Key: " << key << " Value: " << value << endl;
		// cout << "Insert in Bucket: " << bucket << endl;
		// cout << "Simple Insert" << endl;
		HashTable[key]->key = key;
		HashTable[key]->value = value;
	} else {
		// cout << "     Collision" << endl;
		// cout << "     Key: " << key << " Value: " << value << endl;
		newKEY = doubleHash(i, value);
		// cout << "     New Key: " << newKEY << " Value: " << value << endl;
		insertDoubleHash(newKEY, value, i + 1);
	}
}

string hashClass::doubleHashSearch(int key, int value, int i, string outString) {
	outString += to_string(key) + " ";
	if (HashTable[key]->value == value) {
		// cout << key << " ";
	} else {
		int newKEY = doubleHash(i, value);
		// cout << newKEY << " ";
		return doubleHashSearch(newKEY, value, i + 1, outString);
	}
	return outString;
}




