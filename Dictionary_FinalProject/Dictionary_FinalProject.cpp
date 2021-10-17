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


bool writeToFile(dictionary word, fstream& file) {
	if (!file.is_open()) {
		cout << "File did not open correctly!!";
		return false;
	}
	else {
		file.write((char*)&word, sizeof(word));
		return true;
	}
	
}



int main()
{
	//test for write to file function

	fstream file("data.bin", ios::binary | ios::out);

	dictionary wordData;
	strcpy_s(wordData.word, "abebe");

	writeToFile(wordData, file);

	

	
}
