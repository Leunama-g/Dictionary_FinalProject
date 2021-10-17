#include <iostream>
#include <fstream>
#include<string>  

using namespace std;

//string enumerations for word types
string noun = "noun", pronoun = "pron", adjective = "adje", adverb = "adve", preposition = "prep", conjunction = "conj", interjection = "inte";

struct dictionary {
	char word[50];
	char pron[60]; //pronunciation
	char type[4];
	char meaning[200];
	bool deleted = false;
};


void writeToFile(dictionary word, fstream& file) {
	if (!file.is_open()) {
		cout << "File did not open correctly!!";
	}
	else {
		file.write((char*)&word, sizeof(word));
	}
}


dictionary readFromFile(fstream& file, int pos) {

	dictionary readData;
	if (!file.is_open()) {
		cout << "File did not open correctly!!";
	}
	else {
		file.seekg(pos);
		file.read((char*)&readData, sizeof(readData));
	}
	return readData;
}




int main()
{
	//test for write to file function

	fstream file("data.bin", ios::binary | ios::out | ios::in);

	dictionary wordData;

	wordData= readFromFile(file, 0);

	cout << wordData.word;


	
	

	
}
