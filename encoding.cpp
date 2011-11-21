/* File: encoding.cpp
* -----------------
* Put your Encoding class implementation here!
*/

#include "encoding.h"
#include "pqueue.h"
#include <map>
#include <iostream>

const int _EOF_ = 127;
//for testing
void Encoding::PrintTree(node* tree){
	cout << tree->letter  << " at weight " << tree->weight << endl;
	if (tree->leftChild != NULL){
		PrintTree(tree->leftChild);
	}
	if (tree->rightChild != NULL){
		PrintTree(tree->rightChild);
	}
}

void Encoding::BuildEncodingMap(node* tree, string path, int letter){
	if (tree->letter == letter){
		mp[letter] = path;
		return;
	}
	else {
		if (tree->leftChild != NULL) BuildEncodingMap(tree->leftChild, path+'0', letter);
		if (tree->rightChild != NULL) BuildEncodingMap(tree->rightChild, path+'1', letter);
	}
	return;
	
	
	//FindLetter(tree, mp[letter], letter);
	//char temp = letter;
}
void Encoding::FindLetter(node* tree, string path, int letter){

	
}

void getCharCount(ibstream& infile, map<int, int>& charMap){

	int ch = infile.get(); 
	while (ch != EOF){
		if (charMap.count(ch) > 0){
			charMap[ch] += 1;
		}
		else
			charMap[ch] = 1;
		ch = infile.get();
	}
}


Encoding::Encoding(){
}

Encoding::~Encoding(){}

bool Encoding::compress(ibstream &inStream, obstream &outStream){
	buildEncodingForInput(inStream);
	int input;
	string code;

	map<int, string>::iterator it;
	outStream.put(mp.size());
	outStream.put('|');
	for (it = mp.begin(); it != mp.end(); it++){
		outStream.put(it->first);
		//cout << it->first << " has the code ";
		for (int i = 0; i < it->second.size(); i++){
			outStream.put(it->second[i]);
			//cout << it->second[i];
		}
		outStream.put('|');
		//cout << endl;
	}

	inStream.rewind();
	string temp;
	int letter;
	int temps;
	for (int i = 0; i < inStream.size(); i++){
		temps = inStream.size();
		input = inStream.get();
		code = mp[input];
		for (int i = 0; i < code.length(); i++){
			temp = code[i];
			outStream.writebit(StringToInteger(temp));
			//cout << code[i];
		}
		//cout << endl;
	}
	outStream.put(_EOF_);
	outStream.close();


	return true;

}
bool Encoding::decompress(ibstream &inStream, obstream &outStream){
	int mapSize = inStream.get();
	char kill = inStream.get(); //get rid of pipe

	map<string, int> dmap; //remove this after testing
	for (int i = 0; i < mapSize; i++){
		int code;
		string key;
		code = inStream.get();
		int val = inStream.get();
		while (val != '|'){
			key += val;
			val = inStream.get();
		}
		dmap[key] = code;
	}

		int input;
		string code;

	while (true){
			code += IntegerToString(inStream.readbit());
			if (dmap.count(code) > 0){
				input = dmap[code];
				//cout << input << endl;
				outStream.put(input);
				code.clear();
				if (inStream.peek() == _EOF_)
				break;
			}
	}


	cout << " made it out of the loop";
		outStream.close();


	return true;
}







void Encoding::buildEncodingForInput(ibstream& infile){


	map<int, int> charMap;
	getCharCount(infile, charMap);
	PQueue<node*> pq;
	map<int, int>::iterator iter;
	for (iter = charMap.begin(); iter != charMap.end(); iter++){
		node* tempNode = new node;
		tempNode->letter = iter->first;
		tempNode->weight = iter->second;
		tempNode->leftChild = tempNode->rightChild = NULL;
		//cout << tempNode->letter << endl;
		pq.add(tempNode, iter->second);
	}
	map <int, string> encodingMap;
	while (pq.size() != 1){
		node *parent = new node;
		parent->letter = 26;

		parent->weight = 0; //probably don't need this
		parent->leftChild = pq.extractMin();
		parent->leftChild->path +='0';

		parent->rightChild = pq.extractMin();

		parent->rightChild->path += '1';


		parent->weight = parent->leftChild->weight+parent->rightChild->weight;
		pq.add(parent, parent->weight);
	}

	//for testing

	map<int, int>::iterator it;
	node* tree = pq.extractMin();
	for (it = charMap.begin(); it != charMap.end(); it++){
		BuildEncodingMap(tree, mp[it->first], it->first);
		string temps = mp[it->first];
		char tempc = it->first;
		//cout << tempc << " has the encoding " << temps << endl;
	}

	//PrintTree(tree);
}


