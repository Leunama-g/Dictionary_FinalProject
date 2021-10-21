#include <iostream>
#include <fstream>
#include <string>  
#include <iomanip>
#include "linkedList.h"
#include "AVLTree.h"

using namespace std;

/*


    global variables


*/

string noun = "Noun", verb = "Verb" , pronoun = "Pronoun", adjective = "Adjective", adverb = "Adverb", preposition = "Prepostition", conjunction = "Conjunction", interjection = "Interjection";
enum { normal = 1, prefix = 2, infix = 3, postfix = 4 };
AVL dataOnTree;
List<dicIndex> dataOnList,searchResults;
int FEP=0;

/*


    utility functions


*/

int cmpData(char x[], char y[]) {
    for (int i = 0; i < 50; i++) {
        if (x[i] < y[i])
            return -1;
        else if (x[i] > y[i]) {
            return 1;
        }
    }
    return 0;
}

int charArraySize(char word[]) {
    int size;
    for (size = 0; size < 50; size++) {
        if (word[size] == NULL)
            break;
    }
    return size;
}

int searchType(char word[], int size) {
    if (word[0] == '*') {
        if (word[size - 1] == '*') {
            return infix;
        }
        return prefix;
    }
    else {
        if (word[size - 1] == '*') {
            return postfix;
        }
        return normal;
    }
}

string withoutWildcard(char word[], int size) {    
    string buffer="";
    int ctr = 0;

    for (int i = 0; i < size ; i++ ) {
        if (!(word[i] == '*'))
            buffer += word[i];      
    }    

    return buffer;
}

/*


    Structures Used


*/

struct dictionary {
	char word[50];
	char pron[60]; //pronunciation
	char type[20];
	char meaning[200];
	bool deleted = false;
};



/*


    Linked List implementation


*/

template <class T>
List<T>::List() {
    head = NULL;
    tail = NULL;
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
nodeL<T>* List<T>::gethead() {
    return head;
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

/*


    AVL tree implementation


*/


AVL::AVL() {
    root = NULL;
}


AVL::~AVL() {
    empty(root);
}


nodeT* AVL::empty(nodeT* node) {
    if (node == NULL) {
        return NULL;
    }
    else {
        empty(node->left);
        empty(node->right);
        delete node;
        
    }
    return NULL;
}

nodeT* AVL::search(char data[], nodeT* t) {
    if (t == NULL) {
        return NULL;
    }
    else if (cmpData(data, t->data.word) == 0) {
        return t;
    }
    else if (cmpData(data, t->data.word) == -1) {
        return search(data, t->left);
    }
    else {
        return search(data, t->right);
    }    
}




nodeT* AVL::find(char data[]) {
    return search(data, root);
}


bool AVL::isEmpty() {
    return root == NULL;
}


int AVL::height(nodeT* root) {
    if (root == NULL)
        return -1;
    else {
        /* compute the height of each subtree */
        int lheight = height(root->left);
        int rheight = height(root->right);

        /* use the larger one */
        if (lheight > rheight)
            return (lheight + 1);
        else return (rheight + 1);
    }
}


int AVL::difference(nodeT* root) {
    if (root == NULL)
        return -1;
    return height(root->left) - height(root->right);
}


nodeT* AVL::RRRotate(nodeT* root) {
    nodeT* y = root->right;
    root->right = y->left;
    y->left = root;
    return y;
}


nodeT* AVL::RLRotate(nodeT* root) {
    root->right = LLRotate(root->right);
    return RRRotate(root);
}


nodeT* AVL::LLRotate(nodeT* root) {
    nodeT* x = root->left;
    root->left = x->right;   
    x->right = root;
    return x;
}

nodeT* AVL::LRRotate(nodeT* root) {
    root->left = RRRotate(root->left);
    return LLRotate(root);
}


nodeT* AVL::balance(nodeT* root) {
    int bf = difference(root);

    if (bf > 1)
    {
        if (difference(root->left) > 0)
            root = LLRotate(root);
        else
            root = LRRotate(root);
    }
    else if (bf < -1)
    {
        if (difference(root->right) > 0)
            root = RLRotate(root);
        else
            root = RRRotate(root);
    }
    return root;
}

nodeT* AVL::insert(nodeT* t, dicIndex data) {
    if (t == NULL)
    {
        t = new nodeT;
        t->data = data;
        t->left = NULL;
        t->right = NULL;
        return t;
    }
    else if (cmpData(data.word, t->data.word) == -1)
    {
        t->left = insert(t->left, data);
        t = balance(t);
    }
    else if (cmpData(data.word, t->data.word) == 1)
    {
        t->right = insert(t->right, data);
        t = balance(t);
    }
}


nodeT* AVL::minValueNode(nodeT* node) {
    nodeT* current = node;
    
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}


nodeT* AVL::remove(nodeT* t, dicIndex data) {
    if (t == NULL) {
        return NULL;
    }
    else if (cmpData(data.word, t->data.word) == -1) {
        t->left = remove(t->left, data);
    }
    else if (cmpData(data.word, t->data.word) == 1) {
        t->right = remove(t->right, data);
    }
    else {
        if (t->left == NULL) {
            nodeT* temp = t->right;
            delete t;
            return temp;
        }
        else if (t->right == NULL) {
            nodeT* temp = t->left;
            
            delete t;
            return temp;
        }
        else {       
            nodeT* temp = minValueNode(t->right);
            t->data = temp->data;            
            t->right = remove(t->right, temp->data);          
        }
    }

    balance(t);

}

void AVL::inorder(nodeT* t)
{
    
    if (t == NULL) {
        return;
    }
        
    inorder(t->left);
    cout << t->data.word << " ";
    inorder(t->right);
}

void AVL::preorder(nodeT* t)
{
    if (t == NULL)
        return;
    cout << t->data.word << " ";
    preorder(t->left);
    preorder(t->right);
}


void AVL::postorder(nodeT* t)
{
    if (t == NULL)
        return;
    postorder(t->left);
    postorder(t->right);
    cout << t->data.word << " ";
}
  
/*


    file handler functions 


*/

void writeToFile(fstream& file, dictionary word, int pos) {
	if (!file.is_open()) {
		cout << "File did not open correctly!!(Writing to File Failed)";
	}
	else {
        file.seekp(pos);
		file.write((char*)&word, sizeof(dictionary));
        FEP = file.tellp();
	}
    
}


dictionary readFromFile(fstream& file, int pos) {

	dictionary readData;
	if (!file.is_open()) {
		cout << "File did not open correctly!!(Reading From File Failed)";
	}
	else {
		file.seekg(pos);
		file.read((char*)&readData, sizeof(dictionary));
	}
	return readData;
}

/*


    dictionary management functions


*/

//load dictionary records into memory
//only the word and the position of their respective meanings on the file are loaded 

void init() {
    dictionary incomingData;
    dicIndex treeNode;
    nodeT* buffer;
    int position = 0;

    fstream file("data.bin", std::ios::in | std::ios::out | std::ios::binary);
    
    while (!(file.peek() == EOF)) {
        incomingData = readFromFile(file, position);
        
        buffer = dataOnTree.find(incomingData.word);
        //check if the record that was read is deleted data
        if (!incomingData.deleted) {
            //inserting a word that has not yet been inserted to the tree
            if (buffer == NULL) {                
                strcpy_s(treeNode.word, incomingData.word);
                if (dataOnTree.isEmpty()) {
                    dataOnTree.root = dataOnTree.insert(dataOnTree.root, treeNode);
                    dataOnTree.root->data.posList.insert(position);
                }                    
                else {
                    buffer = new nodeT;
                    buffer = dataOnTree.insert(dataOnTree.root, treeNode);
                    buffer->data.posList.insert(position);
                    
                }                    
            }
            else
                buffer->data.posList.insert(position);
        } 
        position += sizeof(dictionary);
    }
    if (!dataOnTree.isEmpty()) {
        FEP = position;
    }
        

    file.close();
    
}

void addRecord() {
    int step = 0;
    dictionary newRecord;
    string input;
    nodeT* data=new nodeT;
    dicIndex word;

    fstream file("data.bin", std::ios::in | std::ios::out | std::ios::binary );

    while (step < 9) {
        switch (step)
        {
        case 0:
            system("cls");
            //enter word
            cout << "Enter ! to Exit" << endl;
            cout << "Enter The Word: ";
            cin >> input;
            if (input == "!") {
                step = 9;
            }
            else if (input.size() <= 50) {
                strcpy_s(newRecord.word, input.c_str());
                data = dataOnTree.find(newRecord.word);
                if (data == NULL) {
                    step++;
                }
                else {
                    cout << "Word already exists...try again \nEnter anything to continue: ";
                    cin >> input;
                }
                
            }
            else {
                cout << "Number of characters entered is greater than 50!!! \nEnter anything to continue. ";
                cin >> input;
            }                
            break;
        case 1:
            system("cls");
            cout << "Enter ! to Exit" << endl;
            cout << "Enter The pronounciation of the word (" << newRecord.word << "): ";
            cin >> input;
            if (input == "!") {
                step = 9;
            }
            else if (input.size() <= 60) {
                strcpy_s(newRecord.pron, input.c_str());
                strcpy_s(word.word, newRecord.word);
                if (dataOnTree.isEmpty()) {
                    dataOnTree.root = dataOnTree.insert(dataOnTree.root, word);
                    data = dataOnTree.root;
                }
                else
                {
                    cout << "h";
                    dataOnTree.insert(dataOnTree.root, word);
                }
                
                step++;
            }
            else {
                cout << "Number of characters entered is greater than 50!!! \nEnter anything to continue. ";
                cin >> input;
            }
            data = dataOnTree.find(newRecord.word);
            break;
        case 2:
            system("cls");
            cout << "Enter ! to Exit" << endl;
            cout << "Enter > to Skip this step" << endl;
            cout << "Enter The definition of the word (" << newRecord.word << ") when it is a Noun." << endl;
            cout << endl << "- ";
            cin.ignore();
            cin.getline(newRecord.meaning,200);

            if (newRecord.meaning[0] == '!') {
                if (data->data.posList.isEmpty())
                    dataOnTree.remove(dataOnTree.root, word);
                step = 9;
            }
            else if (newRecord.meaning[0] == '>') {
                step++;
            }
            else if (input.size() <= 200) {
                data = dataOnTree.find(newRecord.word);
                data->data.posList.insert(FEP);
                strcpy_s(newRecord.type, noun.c_str());
                writeToFile(file,newRecord, FEP);
                step=9;
            }
            else {
                cout << "Number of characters entered is greater than 200!!! \nEnter anything to continue. ";
                cin >> input;
            }
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:

            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        default:
            break;
        }
    }
}

void inorderDicIndex(nodeT* t) {
    if (t == NULL) {
        return;
    }

    inorderDicIndex(t->left);
    dataOnList.insert(t->data);
    inorderDicIndex(t->right);
}

int checkPrefix(char word[], char key[], int keySize) {
    for (int i = 0; i < keySize && i < 50 ; i++) {
        if (word[i] > key[i]) {
            return 1;
        }
        else if(word[i] < key[i]){
            return -1;
        }
    }
    return 0;
}

void prefixSearch(char key[]) {
    inorderDicIndex(dataOnTree.root);
    nodeL<dicIndex>* buffer = dataOnList.gethead();
    string keyS;
    char word[50];
    keyS = withoutWildcard(key, charArraySize(key));
    int res;
    strcpy_s(word, keyS.c_str());

    int sizeKey = charArraySize(word);

    while (buffer != NULL)
    {
        res = checkPrefix(buffer->data.word, word, sizeKey);
        if (res == 1) {
            break;
        }
        else if (res == 0) {
            searchResults.insert(buffer->data);
        }     
        buffer = buffer->next;
    }
    
}

int checkPostfix(char word[], int wordSize, char key[], int keySize) {
    int i = wordSize - keySize;
    for (int j = 0; j < keySize; j++, i++) {
        if (word[i] != key[j])
            return -1;
    }
    return 0;
}

void postfixSearch(char key[]) {
    inorderDicIndex(dataOnTree.root);
    nodeL<dicIndex>* buffer = dataOnList.gethead();
    string keyS;
    char word[50];
    keyS = withoutWildcard(key, charArraySize(key));
    int res;
    strcpy_s(word, keyS.c_str());

    int sizeKey = charArraySize(word);
    int sizeWord; 

    while (buffer != NULL)
    {
        sizeWord = charArraySize(buffer->data.word);
        res = checkPostfix(buffer->data.word, sizeWord, word, sizeKey);
        if (res == 0) {
            searchResults.insert(buffer->data);
        }
        buffer = buffer->next;
    }

}

int checkinfix(char word[], char key[]) {
    string str = word, str2 = key;

    if (str.find(str2) != string::npos) {
        return 0;
    }
    return -1;
}

void infixSearch(char key[]) {
    inorderDicIndex(dataOnTree.root);
    nodeL<dicIndex>* buffer = dataOnList.gethead();
    string keyS;
    char word[50];
    keyS = withoutWildcard(key, charArraySize(key));
    int res;
    strcpy_s(word, keyS.c_str());

    
    while (buffer != NULL)
    {
        res = checkinfix(buffer->data.word, word);
        if (res == 0) {
            searchResults.insert(buffer->data);
        }
        buffer = buffer->next;
    }

}

void display(nodeL<dictionary>* head) {
    system("cls");
    nodeL<dictionary>* buffer = head;
    int ctr = 1;
    string input;

    cout << "Definition For: " << buffer->data.word << "('" << buffer->data.pron << "')" << endl << endl;
    cout << "Types:" << endl;

    while (buffer != NULL) {
        cout << "\t" << ctr << ". " << buffer->data.type << ":" << endl;
        cout << "\t\t" << buffer->data.meaning << endl << endl;
        ctr++;
        buffer = buffer->next;
    }
    cout << "Enter anything to continue. ";
    cin >> input;
}

void getRecordsAndDisplay(nodeT* data) {
    fstream file("data.bin", std::ios::in | std::ios::out | std::ios::binary);
    List<dictionary> words;
    dictionary buffer;
    int f;
    nodeL<int>* positions = data->data.posList.gethead();

    if (positions== NULL) {
        cout << "jdfdfg";
        cin >> f;
    }
    
    while (positions != NULL)
    {
        buffer = readFromFile(file, positions->data);
        words.insert(buffer);
        positions = positions->next;
    }   
        
    display(words.gethead());

    words.empty();

}



dicIndex* displaySearchResults() {
    cout << "Search Results" << endl << endl;
    int ctr = 1;
    nodeL<dicIndex>* buffer = searchResults.gethead();
    dicIndex results[100];
    while (buffer != NULL)
    {
        cout << ctr << ". " << buffer->data.word << endl;
        if (ctr < 100)
            results[ctr - 1] = buffer->data;

        buffer = buffer->next;
    }
    cout << "Pick from The above choices: ";
    cin >> ctr;

    dicIndex* x = new dicIndex;
    strcpy_s(x->word, results[ctr].word);
    x->posList = results->posList;

    return x;

}

void search() {
    system("cls");
    string key;
    char keyArr[50];
    nodeT* data = NULL;
    dicIndex* x = NULL;
    cout << "Enter the word: ";
    cin >> key;
    strcpy_s(keyArr, key.c_str());
    
    switch (searchType(keyArr, charArraySize(keyArr)))
    {
    case normal:
        data = dataOnTree.find(keyArr);
        if (data != NULL) {
            getRecordsAndDisplay(data);
            break;
        }
    case prefix:
        prefixSearch(keyArr);
        if (searchResults.isEmpty()) {
            cout << "word is not found and no close matches...";
            cin >> key;
        }
        else {
            x = displaySearchResults();
            data = dataOnTree.find(x->word);
            getRecordsAndDisplay(data);
            searchResults.empty();
            dataOnList.empty();
            system("cls");
        }
        break;
    case infix:
        infixSearch(keyArr);
        if (searchResults.isEmpty()) {
            cout << "word is not found and no close matches...";
            cin >> key;
        }
        else {
            x = displaySearchResults();
            data = dataOnTree.find(x->word);
            getRecordsAndDisplay(data);
            searchResults.empty();
            dataOnList.empty();
            system("cls");
        }
        break;
    case postfix:
        postfixSearch(keyArr);
        if (searchResults.isEmpty()) {
            cout << "word is not found and no close matches...";
            cin >> key;
        }
        else {
            x = displaySearchResults();
            data = dataOnTree.find(x->word);
            getRecordsAndDisplay(data);
            searchResults.empty();
            dataOnList.empty();
            system("cls");
        }
        break;
    default:
        break;
    }


}

void about() {
    system("cls");
    string input;
    cout << "Group Members:" << endl;
    cout << "\t1. Amanuel Getachew" << endl;
    cout << "\t2. Mahlet Zelalem" << endl;
    cout << "\t3. Sara Tilahun" << endl;
    cout << endl << endl << "Enter anything to go back: ";
    cin >> input;
}




int main()
{
    //load data to memory
    init();
    char input='0';
    dicIndex word;

    //test
    char c[200];
    dicIndex treeNode;
    string str("There are two needles in this haystack.");
    string str2("needle");
    int position = 5;
    nodeL<dicIndex>* buffer;

    while (input != '4') {
        cout << "Welcome To The Application" << endl << endl;
        cout << "\t1. Serach the definition of a word." << endl;
        cout << "\t2. Add a dictionary record." << endl;
        cout << "\t3. About the dev team." << endl;
        cout << "\t4. Exit." << endl << endl;

        cout << "Enter Your Choice: ";
        cin >> input;

        switch (input)
        {
        case '1':  
            search();
            system("cls");
            break;
        case '2':
            //code implementation for add record
            addRecord();
            system("cls");
            break;
        case '3':
            about();
            system("cls");
            break;
        case '4':            
            break;
        default:
            input = '0';
            system("cls");
            
            cout << "Wrong input detected!!!(enter only one character from 1-4)"<<endl<<endl;
            break;
        }
    }
    

    
    
    //empty AVLtree
    

}
