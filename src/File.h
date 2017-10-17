#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

class File {
private:
	fstream file;

public:
	File(string filename, string IO);
	void openFile(string filename);
	double* parseData(double file_data[]);
	void printData(int n, double A[]);
	void write(string inString);
	void close();
};

#endif