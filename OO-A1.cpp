/* ----------------- Assignment 1 -- 159.234 ----------------- */
/* ----------- Name: Andrew Creevey -- ID: 12236284 ---------- */
/*  This program manipulates a data file data.txt to find the  */
/* sum, average, standard deviation, maximum and minimum value */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <cfloat>
#include <cmath>

using namespace std;

void displayInfo ();

//function declarations
double stdDev (double data[], int count);
void CheckMax (double maxarray[], double value);
void CheckMin (double minarray[], double value);
double CalcSum (double myarray[], int arraysize);
void printResults (int counter, double numbers[]);

int main (int argc, char** argv) {
	displayInfo (); //call this so it will always appear first
	
	//open file
	ifstream File;
	File.open ("OO-A1-data.txt");
	// check if file opened correctly.
	if (File.is_open() == false) {
		cout << "Could not read file." << endl; 
		exit (0);
	}

	string firstline, nextline;
	int numlines = 0, count = 0;
	
	getline (File,firstline); //gets first line which signals number of lines to come 
	numlines = atoi (firstline.c_str()); //converts string to integer	

	double *values = new double[numlines]; 
	
	while(!File.eof ()) { //while not at the end of file
		getline (File, nextline); //get lines following the first
		if (nextline[0] != '#') { //if the first letter is not '#'
			//convert line to double and store in array
			values[count] = atof (nextline.c_str());
			count++; //increase count
		}
	}	
	//print all results on the screen
	printResults(count,values);
	
	File.close();
	delete[] values;
	values = NULL;
}

void printResults (int counter, double numbers[]) {
	
	cout << "Total records: " << counter << endl;
	
	//calculate the sum
	double sum = 0.0;
	cout << "Sum: " << (sum = CalcSum(numbers,counter)) << endl;
	
	//calculate the average
	double average = 0.0;
	cout << "Average of the records: " << setprecision(5) << (average = sum/counter) << endl;
	
	//calculate the standard deviation
	double deviation = 0.0;
	deviation = stdDev(numbers, counter);
	cout << "Standard Deviation of the records: " << setprecision(5) << deviation << endl;
	
	//calculate the max and display
	//set max[] to absolute min so any number will always be higher
	double max[3] = {DBL_MIN, DBL_MIN, DBL_MIN};
	for (int i = 0; i < counter; i++) { CheckMax (max,numbers[i]); }
	cout << "Highest three values found: " << max[0] << " " << max[1]<< " " << max[2] << endl;
	
	//calculate the min and display
	//set min[] to absolute max so any number will always be lower
	double min[3] = {DBL_MAX, DBL_MAX, DBL_MAX};
	for (int i = 0; i < counter; i++) { CheckMin (min,numbers[i]); }
	cout << "Lowest three values found: " << min[0] << " " << min[1] << " " << min[2] << endl;
}	

double stdDev (double data[], int count) {
	double mean = 0.0, sumDev = 0.0;
	//add all numbers to the mean
	for (int i = 0; i < count; i++) { mean += data[i]; }
	mean = mean/count; //get average
	for (int i = 0; i < count; i++) { sumDev += (data[i] - mean) * (data[i] - mean); }
	return sqrt (sumDev/(count-1));
}

void CheckMax (double maxarray[], double value) {
	//this function stores the 3 largest variables
	double temp = 0;
	//maximum value
	if (value > maxarray[0]) {
		temp = maxarray[0];
		maxarray[0] = value;
		CheckMax (maxarray,temp);
		//second highest value
	} else if (value > maxarray[1]) {
		temp = maxarray[1];
		maxarray[1] = value;
		CheckMax (maxarray,temp);
		//third highest value
	} else if (value > maxarray[2]) {
		maxarray[2] = value;
		return;
	} else {
		return; //no new max variables so exit
	}
}

void CheckMin (double minarray[], double value) {
	//this function stores the 3 largest variables
	double temp = 0;
	//lowest value
	if (value < minarray[0]) {
		temp = minarray[0];
		minarray[0] = value;
		CheckMin (minarray,temp);
		//second lowest value
	} else if (value < minarray[1]) {
		temp = minarray[1];
		minarray[1] = value;
		CheckMin (minarray,temp);
		//third lowest value
	} else if (value < minarray[2]) {
		temp = minarray[2];
		minarray[2] = value;
		return;
	} else {
		return; //no new max variables so exit
	}
}

double CalcSum (double array[], int arraysize) {
	double total = 0;	
	//add all variables together
	for (int i = 0; i < arraysize; i++) {
		total += array[i]; 
	}
	//return total of all variables
	return total;
}

void displayInfo () {
	//display this info on the screen
	cout << "----------------------------------------" << endl;
	cout << "     Assignment 1 -- Semester 2 2015    " << endl;
	cout << " Submitted by: Andrew Creevey, 12236284 " << endl;
	cout << "----------------------------------------" << endl;
	cout << endl;
}
