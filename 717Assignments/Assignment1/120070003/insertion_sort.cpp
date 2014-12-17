#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
using namespace std;

// Read data from inputfile, perform Insertion Sort and wirte back result & runtime(milliseconds) into outputfile
void insertionSort(string inputfile, string outputfile){
	
	// Read Data from inputfile
	ifstream infile(inputfile.c_str());
	
	int N;
	infile>>N; // N = size of Array
	
	int *inputArray;
	inputArray = new int[N];
	for(int i=0; i<N; i++){
		infile>>inputArray[i];
	}
	
	// Record time before algorithm execution
	clock_t start,end;
	start = clock();
	
	
	// Insertion Sort Algorithm

		
	for(int i = 1;i<N;i++){

		int instant_value = inputArray[i];
		int j = i-1;

		while((instant_value < inputArray[j])&&(j>=0)){

			inputArray[j+1] = inputArray[j];
			inputArray[j] = instant_value;
			j--;
		}
	}
	
	// Record time after algorithm execution, and calculate time elapsed
	end = clock();
	double runtime = (end - start)/(double)(CLOCKS_PER_SEC/1000); //Runt time of algorithm in "Milliseconds"
	
	// Write runtime & Result(Sorted Array) into outputfile
	ofstream outfile(outputfile.c_str());
	outfile<<runtime<<endl;
	for(int i=0; i<N; i++){
		outfile<<inputArray[i]<<endl;
	}

	delete(inputArray);
}


int main (void)
{
	insertionSort("input100.txt","output100.txt");
	return 0;
}



