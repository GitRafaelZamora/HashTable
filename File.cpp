#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

#include "File.h"

using namespace std;

File::File(string filename) {
	this->file.open(filename.c_str());
	if (this->file) {
	    cout << "Input File Open." << endl;
	} else {
		cout << "Error Opening File." << endl;
	}
}


// Goes through an open file's data line by line inorder to store data in an array.
//		Returns pointer to the array.
double* File::parseData(double file_data[]) {
  string str; //Holds one line of the inputFile
  
  getline(this->file, str);
  int p = stoi(str);
  getline(this->file, str);
  double a = stod(str);
  getline(this->file, str);
  int n = stoi(str);

  file_data = new double[n+4];
  file_data[0] = p;
  file_data[1] = a;
  file_data[2] = n;

  //Process data  
  for (int i = 3; i < n+4; i++) {
    getline(this->file, str);
    file_data[i] = stoi(str);
  }
  return file_data;
}

// Closes THIS instance file.
void File::close() {
	this->file.close();
	cout << "File closed..." << endl;
}

// Print data takes an array and writes it out.
void File::printData(int n, double A[]) {
  for (int i = 0; i < n+4; i++) {
    cout << i << ":  " << A[i] << endl;
  }
  cout << endl;
}