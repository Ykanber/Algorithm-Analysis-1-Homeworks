
//!!! I did not print headers on sorted.txt file when reading line that reads headers needs to be commented
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include <time.h>
#include<stdlib.h>
using namespace std;

class sale { // creating an object to hold all 5 data
public:
	string country;
	string item_type;
	string Order_ID;
	int units_sold;
	float total_profit;
};

int main(int argc, char* argv[]) {

	if (argc != 2) return -1;  //reading from command line
	ifstream file;       // for read
	file.open("sales.txt"); //opening file to read

	if (!file) {  // if file is can not opened
		cerr << "File cannot be opened!";
		return(0);
	}

	int N = atof(argv[1]); //reading from command line
	string header;	//for reading header
	vector<sale> sale_vector; // creating a vector for dynamic storing

	void quicksort(vector<sale> & sale_vector, int l, int h); // function define

	getline(file, header); //this is the header line, this line should be commented when reading sorted.txt

	for (int i = 0; i < N; i++) {
		sale ptr; // create an object
		getline(file, ptr.country, '\t'); //country (string)
		getline(file, ptr.item_type, '\t'); //item type (string)
		getline(file, ptr.Order_ID, '\t'); //order id (string)
		file >> ptr.units_sold; //units sold (integer)
		file >> ptr.total_profit; //total profit (float)
		sale_vector.push_back(ptr); //add object to object vector
		getline(file, header, '\n'); //this is for reading the \n character into dummy variable.
	}
	file.close();  //closing input file

	clock_t t;           //for calculation of  execution time

	t = clock(); //for calculation of  execution time
	quicksort(sale_vector, 0, N); // calling quicksort on vector

	t = clock() - t;	//for calculation of  execution time
	printf("%f seconds.\n", ((float)t) / CLOCKS_PER_SEC);	//for calculation of  execution time

	ofstream outfile;	// for write 
	outfile.open("sorted.txt"); //opening file to write

	for (int c = 0; c < N; c++) { //printing the output
		outfile << sale_vector[c].country << "\t";
		outfile << sale_vector[c].item_type << "\t";
		outfile << sale_vector[c].Order_ID << "\t";
		outfile << sale_vector[c].units_sold << "\t";
		outfile << sale_vector[c].total_profit << "\n";
	}
	outfile.close();	//closing output file
	return 0;
}

void quicksort(vector<sale>& sale_vector, int l, int h) {
	int partition(vector<sale> & sale_vector, int l, int h); //partition function define(it was not working on VS without define)
	if (l < h) {
		int j = partition(sale_vector, l, h); //finding j value that will divide vector 2 
		quicksort(sale_vector, l, j); // for lower part of the vector
		quicksort(sale_vector, j + 1, h); // for higher part of the vector
	}
}

int partition(vector<sale>& sale_vector, int l, int h) {
	string Pivot = sale_vector[l].country; // pivot is taken as first element of vectir
	float Pivot_total_profit = sale_vector[l].total_profit; // Pivots total profit
	int i = l; int j = h;
	while (i < j) {
		i++;
		j--;
		if (i == h)
			i--;
		while (Pivot.compare(sale_vector[i].country) >= 0) { //finding an element greater than pivot
			if (Pivot.compare(sale_vector[i].country) == 0) { // if there is an quality we will check total number
				if (Pivot_total_profit < sale_vector[i].total_profit) //if there is an quality we will check total profit
					break;
				else
					i++;
			}
			else
				i++;
			if (i == h) {
				break;
			}
		}
		while (Pivot.compare(sale_vector[j].country) <= 0 && j != l) { //finding an element smaller than pivot
			if (Pivot.compare(sale_vector[j].country) == 0) {	// if there is an quality we will check total number
				if (Pivot_total_profit > sale_vector[j].total_profit)	//if there is an quality we will check total profit
					break;
				else
					j--;
			}
			else
				j--;
			if (j == l) {
				break;
			}
		}
		if (i < j) { // j bigger than i swap elements and their properties
			int a;
			float b;
			sale_vector[i].country.swap(sale_vector[j].country);
			sale_vector[i].item_type.swap(sale_vector[j].item_type);
			sale_vector[i].Order_ID.swap(sale_vector[j].Order_ID);
			b = sale_vector[i].total_profit;
			sale_vector[i].total_profit = sale_vector[j].total_profit;
			sale_vector[j].total_profit = b;
			a = sale_vector[i].units_sold;
			sale_vector[i].units_sold = sale_vector[j].units_sold;
			sale_vector[j].units_sold = a;
		}
	} // if i >= j swap pivot and jth element
	int a;
	float b;
	sale_vector[l].country.swap(sale_vector[j].country);
	sale_vector[l].item_type.swap(sale_vector[j].item_type);
	sale_vector[l].Order_ID.swap(sale_vector[j].Order_ID);
	b = sale_vector[l].total_profit;
	sale_vector[l].total_profit = sale_vector[j].total_profit;
	sale_vector[j].total_profit = b;
	a = sale_vector[l].units_sold;
	sale_vector[l].units_sold = sale_vector[j].units_sold;
	sale_vector[j].units_sold = a;
	return j;
}