#include <iostream>
#include <fstream>
#include <string>  
#include "linkedList.h"

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

template <class T>
List<T>::List() {
    head = NULL;
    tail = NULL;
}

template <class T>
List<T>::List(List<T>& L) {
    head = L.head;
    tail = L.tail;
}

template <class T>
List<T>::~List() {
    empty();
}

template <class T>
bool List<T>::isEmpty() {
    return head == NULL;
}

template <class T>
void List<T>::insert(T data) {
    nodeL<T>* newData = new nodeL<T>;

    newData->data = data;
    newData->next = NULL;

    if (isEmpty()) {
        head = tail = newData;
    }
    else {
        tail->next = newData;
        tail = newData;
    }
}

template <class T>
nodeL<T>* List<T>::nodeToDelete(T data) {
    nodeL<T>* curr = NULL;
    nodeL<T>* prev = NULL;
    bool found = false;
    curr = head;
    while (curr->next != NULL) {
        
        prev = curr;
        curr = curr->next;
        if (curr->data == data) {
            found = true;
            break;
        }
    }

    if (curr->data == data) {
        return prev;
    }

    return NULL;
}

template <class T>
int List<T>::remove(T data) {
    nodeL<T>* prev = NULL;
    nodeL<T>* node_del = NULL;

    if (!isEmpty()) {
        if (head->data == data) {
            node_del = head;
            head = head->next;

            delete node_del;
            return 1;
        }
        else {
            prev = nodeToDelete(data);

            if (prev == NULL)
                return NULL;
            else {
                node_del = prev->next;

                if (node_del->data == tail->data)
                    tail = prev;

                prev->next = node_del->next;
                delete node_del;

                return 1;
            }
        }
    }
    else
        return 0;
}

template <class T>
void List<T>::empty() {
    nodeL<T>* temp;

    while (head != NULL) {
        temp = head;

        head = head->next;
        delete temp;
    }
}

template <class T>
void List<T>::print() {
    nodeL<T>* temp;
    temp = head;
    cout << temp->data << ", ";
    while (temp->next != NULL) {
        
        temp = temp->next;
        cout << temp->data << ", ";
    }
    cout << endl;
}
   
    



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
