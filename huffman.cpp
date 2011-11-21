/**
* File: huffman.cpp 
* -------------------
* Huffman main module.
*/

#include "genlib.h"
#include <iostream>
#include "simpio.h"
#include <map>
#include "encoding.h"


void CompressFile();
void DecompressFile();


int main() {
	cout << "Welcome to CS106 Shrink-It(tm)!" << endl;
	cout << "This program uses the Huffman coding algorithm for compression." << endl;
	cout << "Any file can be compressed by this method, often with substantial" << endl;
	cout << "savings. Decompression will faithfully reproduce the original." << endl << endl;
	while (true){
		cout << "Do you want to compress or decompress a file? " << endl;
		string response = GetLine();
		if (response[0]== 'y' || response[0] == 'Y'){
			cout << "Are we compressing?" << endl;
			while (true){
				response = GetLine();
				if (response[0] == 'y' || response[0] == 'Y'){
					CompressFile();
					break;
				}
				else if (response[0] == 'n' || response[0] == 'N'){
					DecompressFile();
					break;
				}
				else 
					cout << "Please enter yes of no, it's not hard. " << endl;
			}
		}
		else if (response[0] == 'n' || response[0] == 'N'){
			break;
		}
	}


	cout << endl << "Thanks for using Shrink-It" << endl;
	return 0;
}



void CompressFile(){
	Encoding inputFile;
	cout << " What is the file name? " << endl;
	string inputFileName = GetLine();
	ibstream infile;
	infile.open(inputFileName.c_str());
	if (infile.fail()) Error("Can't open input file!");					
	cout << " What do you want to name the compressed file? " << endl;
	string newFileName = GetLine();
	obstream outfile;
	outfile.open(newFileName.c_str());
	if (outfile.fail())Error("That is not a valid file name");
	inputFile.compress(infile, outfile);
}

void DecompressFile(){
	cout << " What is the name of the file you want to decompress? " << endl;
	string compressedFileName = GetLine();
	ibstream filetoDecompress;
	filetoDecompress.open(compressedFileName.c_str());
	if (filetoDecompress.fail()) Error(" Failed to open the specified file");
	cout << " What should we name the decompressed file? " << endl;
	string newDecompedFile = GetLine();

	Encoding dfile;
	obstream decompedFile;
	decompedFile.open(newDecompedFile.c_str());
	dfile.decompress(filetoDecompress, decompedFile);
}

