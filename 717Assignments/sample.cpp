#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
using namespace std;

int main(){
int inputArray[5] = {5,3,6,2,1};
cout<<inputArray[0] <<inputArray[1]<<inputArray[2]<<inputArray[3]<<inputArray[4]<< endl;
for(int i = 1;i<5;i++){

		int instant_value = inputArray[i];
		int j = i-1;
		cout<<"LOL "<<endl;
		while((instant_value > inputArray[j])&&(j>=0)){

			inputArray[j+1] = inputArray[j];
			inputArray[j] = instant_value;
			j--;
		}
	}
cout<<inputArray[0] <<inputArray[1]<<inputArray[2]<<inputArray[3]<<inputArray[4]<< endl;

}
