// Extraction of features.
// Of a singal paragraph.

#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;
using namespace cv;


int main(){

   int linecount = 0 ;
   std::string line ;
   std::string path	;
   std::string delimiter = ","; 	
   std::ifstream infile("data.csv");

   if (infile) {
      while ( getline( infile , line ) ) {
//	 std::cout << linecount << ": " << line << '\n' ;//supposing '\n' to be line end
	
	 size_t pos = 0;
	std::string token;
	while ((pos = line.find(delimiter)) != std::string::npos) {
	    token = line.substr(0, pos);
	   // std::cout << token << std::endl;
	    line.erase(0, pos + delimiter.length());
	}
	//std::cout << line << std::endl;
	 
	char *fileName = (char*)token.c_str();

//	cout << fileName << endl;

 
	char Type = char(line[0]);
	// std::cout << path <<endl;
	 linecount++ ;
      

	int array_size = 1024*20; // define the size of character array
	char * array = new char[array_size]; // allocating an array of 1kb
	int position = 0; //this will be used incremently to fill characters in the array 
	double data[14];

	ifstream fin(fileName); //opening an input stream for file test.txt
	/*checking whether file could be opened or not. If file does not exist or don't have read permissions, file
  	stream could not be opened.*/
  	if(fin.is_open()){
    //file opened successfully so we are here
    //this loop run until end of file (eof) does not occur
		while(!fin.eof() && position < array_size)
		{
			fin.get(array[position]); //reading one character from file to array
			position++;
		}
		array[position-1] = '\0'; //placing character array terminating character

    // Total words and puntuations
    int words = 0;
    int sentences = 0;	// using this we will also judge the sentence size
    double commas = 0;
    double doublequotes = 0;
    double questions = 0;
    double exclamations = 0;

    // For negations
    double negations = 0;
    // for stress words
    double stress = 0;
    // for comparative words
    double compare = 0;
    // First Person singular and plural
    double fperson = 0;
    // Third Person singular and plural
    double tperson = 0;
    // Accusative verbs
    double accusative = 0;
    // direct speech words
    double directspeechwords = 0;

		for(int i = 0; array[i] != '\0'; i++)
		{
			if(array[i] == ' ') words++; 
			if(array[i] == ',') commas++;
			if(array[i] == '"')	doublequotes++;
			if(array[i] == '?') questions++;
			if(array[i] == '!') exclamations++;

			if(array[i] == '.') {
				sentences++;}

			// for getting words like NO,NOT,NEVER,CANNOT... IMPOSSIBLE
			if(array[i] == ' ') {

				//NO 
				if(((array[i+1] == 'n')||(array[i+1] == 'N')) &&(array[i+2] == 'o')&&(array[i+3] == ' ')) {negations++; }
				//NOT
				if((array[i+1] == 'n')||(array[i+1]=='N')){
					if(array[i+2]=='o'){if(array[i+3] =='t'){negations++;
					
					}}
					}
				//NEVER
				if(((array[i+1] == 'n')||(array[i+1] == 'N')) &&(array[i+2] == 'e') &&(array[i+3] == 'v') &&(array[i+4] == 'e')&&(array[i+5] == 'r')){negations++;}
				//CANNOT
				if(((array[i+1] == 'c')||(array[i+1] == 'C')) &&(array[i+2] == 'a') &&(array[i+3] == 'n') &&(array[i+4] == 'n')&&(array[i+5] == 'o')&&(array[i+6]== 't')){negations++;
			
				}
			}

			//For getting the stress words
			// MUST, SHOULD
			if(array[i] == ' ') {

				//MUST 
				if((array[i+1] == 'm')&&(array[i+2] == 'u') &&(array[i+3] == 's')&&(array[i+4] == 't')&&(array[i+5] == ' ')) {stress++; }
				//SHOULD
				if((array[i+1] == 's')&&(array[i+2] == 'h') &&(array[i+3] == 'o')&&(array[i+4] == 'u')&&(array[i+5] == 'l')&&(array[i+6] == 'd')&&(array[i+7]==' ')) {stress++; }
			}


			// Getting a comparative degree assisting words
			// LIKE,SIMILAR,SAME,ALIKE
			if(array[i] == ' ') {

				//LIKE 
				if((array[i+1] == 'l')&&(array[i+2] == 'i') &&(array[i+3] == 'k')&&(array[i+4] == 'e')&&(array[i+5] == ' ')) {compare++; }
				//ALIKE
				if((array[i+1] == 'a')&&(array[i+2] == 'l') &&(array[i+3] == 'i')&&(array[i+4] == 'k')&&(array[i+5] == 'e')&&(array[i+6] == ' ')) {compare++; }
				//SAME
				if((array[i+1] == 's')&&(array[i+2] == 'a') &&(array[i+3] == 'm')&&(array[i+4] == 'e')&&(array[i+5] == ' ')) {compare++; }
				//SIMILAR
				if((array[i+1] == 's')&&(array[i+2] == 'i') &&(array[i+3] == 'm')&&(array[i+4] == 'i')&&(array[i+5] == 'l')&&(array[i+6] == 'a')&&(array[i+7] == 'r')&&(array[i+8] == ' ')) {compare++; }
			}

			// First Person words I and WE


			if(array[i] == ' ') {

				//I
				if((array[i+1] == 'I')&&(array[i+2] == ' ') ) {fperson++; }
				//WE
				if(((array[i+1] == 'W')||(array[i+1] == 'w')) &&(array[i+2] == 'e')&&(array[i+3] == ' ')) {fperson++; }
			}

			// Third Person with the words HE,SHE,THEY,THEM

			if(array[i] == ' ') {

				//HE
				if(((array[i+1] == 'H')||(array[i+1] == 'h')) &&(array[i+2] == 'e')&&(array[i+3] == ' ')) {tperson++; }
				//SHE
				if(((array[i+1] == 'S')||(array[i+1] == 's')) &&(array[i+2] == 'h')&&(array[i+3] == 'e')&&(array[i+4] == ' ')) {tperson++; }
				//THEY
				if(((array[i+1] == 'T')||(array[i+1] == 't')) &&(array[i+2] == 'h')&&(array[i+3] == 'e')&&(array[i+4] == 'y')&&(array[i+5] == ' ')) {tperson++; }
				//THEN
				if(((array[i+1] == 'T')||(array[i+1] == 't')) &&(array[i+2] == 'h')&&(array[i+3] == 'e')&&(array[i+4] == 'm')&&(array[i+5] == ' ')) {tperson++; }

			}

			// Direct speech, SAID,ASKED,CRIED,EXCLAMAINED,BARKED .. oh god so many.
			if(array[i] == ' ') {

				//SAID
				if(((array[i+1] == 'S')||(array[i+1] == 's')) &&(array[i+2] == 'a')&&(array[i+3] == 'i')&&(array[i+4] == 'd')&&(array[i+5] == ' ')) { directspeechwords++; }
				//ASKED
				if(((array[i+1] == 'A')||(array[i+1] == 'a')) &&(array[i+2] == 's')&&(array[i+3] == 'k')&&(array[i+4] == 'e')&&(array[i+5] == 'd')&&(array[i+6]==' ')) {directspeechwords++; }
				//CRIED
				if(((array[i+1] == 'C')||(array[i+1] == 'c')) &&(array[i+2] == 'r')&&(array[i+3] == 'i')&&(array[i+4] == 'r')&&(array[i+5] == 'd')&&(array[i+6] == ' ')) {directspeechwords++; }
				//EXCLAIMED
				if(((array[i+1] == 'E')||(array[i+1] == 'e')) &&(array[i+2] == 'x')&&(array[i+3] == 'c')&&(array[i+4] == 'l')&&(array[i+5] == 'a')&&(array[i+6] == 'i')&&(array[i+7] == 'm')&&(array[i+8] == 'e')&&(array[i+9] == 'd')&&(array[i+10] == ' ')) {directspeechwords++; }
				//BARKED
				if(((array[i+1] == 'B')||(array[i+1] == 'b')) &&(array[i+2] == 'a')&&(array[i+3] == 'r')&&(array[i+4] == 'k')&&(array[i+5] == 'e')&&(array[i+6] == 'd')&&(array[i+7] == ' ')) {directspeechwords++; }
				//SPAT
				if(((array[i+1] == 'S')||(array[i+1] == 's')) &&(array[i+2] == 'p')&&(array[i+3] == 'a')&&(array[i+4] == 't')&&(array[i+5] == ' ')) {directspeechwords++; }
			}
		}

		float avg_sentence_length = (float(words)/float(sentences));

		// every feature per the paragraph length.

		commas = (commas/double(words)); 
		doublequotes = (doublequotes/double(words));
		questions = (questions/double(words));
		exclamations = (exclamations/double(words));
		negations = (negations/double(words));
		stress = (stress/double(words));
		compare = (compare/double(words));
		fperson = (fperson/double(words));
		tperson = (tperson/double(words));
		directspeechwords = (directspeechwords/double(words));

		data[0] = words;
		data[1] = sentences;
		data[2] = avg_sentence_length;
		data[3] = commas;
		data[4] = doublequotes;
		data[5] = questions;
		data[6] = exclamations;
		data[7] = negations;
		data[8] = stress;
		data[9] = compare;
		data[10] = fperson;
		data[11] = tperson;
		data[12] = directspeechwords;

		cout <<"Paragraph "<<linecount<<" Type: "<< Type << endl;
		cout <<"Total Words: "<< words <<endl;
		cout <<"Total Sentences: "<< sentences <<endl;
		cout <<"Average sentence length: " << avg_sentence_length <<endl;
		cout <<"Total commas used: "<< commas << endl;
		cout <<"Total doublequotes used: " << doublequotes << endl;
		cout <<"Total question marks: " << questions << endl;
		cout <<"Total exclamation marks: " << exclamations << endl;
		cout <<"Total negations: "<< negations<<endl;
		cout <<"Total stress words: "<< stress<<endl;
		cout <<"Total comparative linkiage words:" << compare<<endl;
		cout <<"Total 1st person verbs: " << fperson << endl;
		cout <<"Total 3rd person words: " << tperson << endl;
		cout <<"Some common direct speech words: " << directspeechwords << endl;

		// We need to write all these to a new file. Which will be used for the naive bayes classification
		ofstream fout(output.csv);
    	// for each row
	    for (int i = 0; i < 13; ++i) {
	        // for each column
	        
	            fout << data[i] << ',';
	        fout << "\n";
	    }
    fout.close();

	}


	else //file could not be opened
	{
		cout << "File could not be opened." << endl;
	}
	
	}
}
   infile.close( ) ;
   return 0 ;
}