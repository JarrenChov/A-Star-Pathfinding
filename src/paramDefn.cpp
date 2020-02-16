#include "../include/paramDefn.h"
#include "../include/initDefn.h"
#include <iostream>
#include <fstream>
#include <locale>
#include <string>

using namespace std;

// Check if user wishes for a detailed information output
bool get_details() {
	bool answered = false;
	bool response = true;
	string detail = "";

	cout << "Output detailed information (yes/no)?: " << flush;

	while (answered == false) {
		getline(cin, detail);

		// Convert all input into lowercase and grab the first char
		if (tolower(detail.at(0)) == 'y') {
			answered = true;
		}else if (tolower(detail.at(0)) == 'n') {
			answered = true;
			response = false;
		}else {
			cout << "Invalid. Try again." << endl << endl;
			cout << "Output detailed information (yes/no)?: " << flush;
		}	
	}
	cout << endl;
	return response;
}

// Obtain the grid enviroment's realtive location in te filesystem from the user
string get_environment() {
	bool valid = false;
	string path = "";

	cout << "Please enter a environment file path or select one from below: " << endl;
	cout << "Sample environment files: " << endl;
	cout << "\t( 1 ) grid-small" << endl;
	cout << "\t( 2 ) grid-large" << endl << endl;
	cout << "File Path / Number Selection: " << flush;

	while (valid == false) {
		getline(cin, path);
		// Default file paths for sample grids
		if (path == "1" || path == "2") {
			if (path == "1") {
				path = "./build/sample-grid/grid-small.txt";
			}

			if (path == "2") {
				path = "./build/sample-grid/grid-large.txt";
			}
			valid = true;
		}

		// Check if file exists
		ifstream envFile(path.c_str());
		if (envFile) {
			// Print contents of file to terminal
			cout << "= = = = = = = = =" << endl;
			cout << envFile.rdbuf();
			cout << "= = = = = = = = =" << endl;
			valid = true;
		}else {
			cout << "Please check the file exists or file path is correct." << endl << endl;
			cout << "File Path / Number Selection: " << flush;
		}
	}

	cout << endl;
	return path;
}

// Obtain the user specified x, y positions 
int* get_postion(string type, string envPath) {
	int* coordiantes = new int[2];
	int x_Pos = -1;
	int y_Pos = -1;

	// Check if file exists
	ifstream envFile(envPath.c_str());
	if (envFile) {
		string value = "";
 
 		// Loop whilst both x and y have not been determiend to be a valid input
		while ((x_Pos == -1) || (y_Pos == -1)) {
			if (type == "START") {
				cout << "Start " << flush;
			}else if (type == "END") {
				cout << "End " << flush;
			}

			if (x_Pos == -1) {
				cout << "Coordinate (x): " << flush;
			}else {
				cout << "Coordinate (y): " << flush;
			}

			getline(cin, value);
			// Conversion from a string literal into a integer (initDefn.h)
			int posValue = integer_conversion(value);
			// Update corresponding positions from valid input based on the order:
			//	x position, y position
			if (posValue != -1) {
				if (x_Pos == -1) {
					x_Pos = posValue;
				}else {
					y_Pos = posValue;
				}
			}else {
				cout << "Try again." << endl << endl;
			}
		}
	}else {
		cout << "File could not be opended." << endl;
		return NULL;
	}

	cout << endl;
	coordiantes[0] = x_Pos;
	coordiantes[1] = y_Pos;
	return coordiantes;
}
