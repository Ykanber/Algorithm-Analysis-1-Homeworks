#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include <time.h>
#include<stdlib.h>
#include <math.h>
using namespace std;

const double HOTEL_LONGITUDE = 33.40819;	// Hotels location
const double HOTEL_LATITUDE = 39.19001;

class taxi { // creating an object to hold all 3 data
public:
	double longitude;
	double latitude;
	double distance;
	taxi(double longitude, double latitude);
};

taxi::taxi(double longitude, double latitude) {//constructor to find distance
	this->latitude = latitude;
	this->longitude = longitude;
	this->distance = sqrt((longitude - HOTEL_LONGITUDE) * (longitude - HOTEL_LONGITUDE) + (latitude - HOTEL_LATITUDE) * (latitude - HOTEL_LATITUDE));
}


int main(int argc, char* argv[]) {

	//if (argc != 3) return -1;  //reading from command line

	clock_t t;          //for calculation of  execution time
	t = clock();			//for calculation of  execution time	

	ifstream file;       // for read
	file.open("locations.txt"); //opening file to read

	if (!file) {  // if file is can not opened
		cerr << "File cannot be opened!";
		return(0);
	}

	string header;	//for reading header

	int N = 20;  // initializing heap with 20 element to work properly

	vector<taxi> taxi_vector; // creating a vector for dynamic storing
	vector<double> distance_vector; // creating a vector for holding distances of called taxis

	getline(file, header);
	void minheapify(vector<taxi> & taxi_vector, int n, int i); // function define

	double longit;
	double latit;
	taxi first_taxi(0, 0); // first element of array is not used on heap 
	taxi_vector.push_back(first_taxi);

	for (int i = 1; i < N + 1; i++) {
		file >> longit; //Longitute (double)
		file >> latit; //Latitute (double)
		taxi ptr(longit, latit); // create an object
		taxi_vector.push_back(ptr); //add object to object vector
		getline(file, header, '\n'); //this is for reading the \n character into dummy variable.
		if (i > 2) {
			for (int x = i / 2; x >= 1; x = x / 2) { // places first 20 element on proper places
				minheapify(taxi_vector, i, x);
			}
		}
	}

	float p = 0.1; //reading from command line
	int update_probability = p * 100;
	int operation_count = 0;
	int update_count = 0;
	int add_count = 0;;
	int operation_assumed = 100000;
	int taxi_called = 0;
	for (int c = 0; c < operation_assumed; c++) {
		int choice = rand() % 100;
		operation_count++;
		if (operation_count % 100 == 0 && operation_count <= operation_assumed) { // if 100 operation is occured
			c--;
			taxi_called++;
			choice = -1;
		}
		if (choice >= update_probability) { // add to heap
			double latit2, longit2;
			file >> longit2; //Longitute (double)
			file >> latit2; //Latitute (double)
			getline(file, header, '\n'); //this is for reading the \n character into dummy variable.
			taxi ptr2(longit2, latit2);
			taxi_vector.push_back(ptr2);
			N = N + 1;
			int i = N;
			while (taxi_vector[i / 2].distance > taxi_vector[i].distance) { // check if the added element is smaller than the parent
				if (i == 1) { // if parent == 0 break element 0 is not used on heap
					break;
				}
				i = i / 2;
				minheapify(taxi_vector, N, i);
			}
			add_count++;
		}
		else if (choice < update_probability && choice >= 0) { // update
			if (N == 0) {						// this is if not used because array initialized with 20 elements
				cout << "Every taxi is busy right now try again later \n";
				operation_count--;
			}
			else {
				int taxi_number = rand() % N; // choose random element
				taxi_number = taxi_number + 1; // since element 0 is not used add with 1
				taxi_vector[taxi_number].distance = taxi_vector[taxi_number].distance - 0.01;
				if (taxi_vector[taxi_number].distance < 0) // if negative make 0
				{
					taxi_vector[taxi_number].distance = 0;
				}
				int i = taxi_number;
				while (taxi_vector[i / 2].distance > taxi_vector[i].distance) { // check if the updated element is smaller than the parent
					if (i == 1) {
						break;
					}
					i = i / 2;
					minheapify(taxi_vector, N, i);
				}
				update_count++;
			}
		}
		else if (choice == -1) { // delete element
			for(int z = 1; z <= N; z++){
				if (taxi_vector[1].distance > taxi_vector[z].distance) {
					cout << "bozuk";
					return 0;
				}
			}
			double a;
			int index = taxi_vector.size() - 1; // swapping first element with last element
			a = taxi_vector[index].distance;
			taxi_vector[index].distance = taxi_vector[1].distance;
			taxi_vector[1].distance = a;

			a = taxi_vector[index].latitude;
			taxi_vector[index].latitude = taxi_vector[1].latitude;
			taxi_vector[1].latitude = a;

			a = taxi_vector[index].longitude;
			taxi_vector[index].longitude = taxi_vector[1].longitude;
			taxi_vector[1].longitude = a; // swapping ends

			distance_vector.push_back(taxi_vector[index].distance); // distance is taken for print at end
			taxi_vector.pop_back(); // last element is deleted
			N = N - 1;
			if (N > 0) {
				minheapify(taxi_vector, N, 1); //sorting the changed first element
			}
		}
	}
	file.close(); // close file
	t = clock() - t;	//for calculation of  execution time

	for (int a = 0; a < taxi_called; a++) {
		cout << distance_vector[a] << "\n";
	}
	cout << "\n update count is " << update_count << "\n add count is " << add_count << "\n";
	printf("\n%f seconds.\n", ((float)t) / CLOCKS_PER_SEC);	//for calculation of  execution time
	return 0;
}

void minheapify(vector<taxi>& taxi_vector, int n, int i) {
	int smallest = i; //parent node
	int l = (2 * i);  // left child
	int r = (2 * i) + 1; // right child

	if (l <= n && taxi_vector[l].distance < taxi_vector[smallest].distance) { // compare values change if bigger change with left child
		smallest = l;
	}

	if (r <= n && taxi_vector[r].distance < taxi_vector[smallest].distance) {// compare values change if bigger change with right child
		smallest = r;
	}

	if (smallest != i) { // if parent is not smallest change with proper child
		double a;
		a = taxi_vector[smallest].distance;
		taxi_vector[smallest].distance = taxi_vector[i].distance;
		taxi_vector[i].distance = a;

		a = taxi_vector[smallest].latitude;
		taxi_vector[smallest].latitude = taxi_vector[i].latitude;
		taxi_vector[i].latitude = a;

		a = taxi_vector[smallest].longitude;
		taxi_vector[smallest].longitude = taxi_vector[i].longitude;
		taxi_vector[i].longitude = a;
		minheapify(taxi_vector, n, smallest); // call same method for root that its place has changed
	}
}