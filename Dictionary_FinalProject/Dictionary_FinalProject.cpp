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

string noun = "noun", pronoun = "pron", adjective = "adje", adverb = "adve", preposition = "prep", conjunction = "conj", interjection = "inte";
enum { normal = 1, prefix = 2, infix = 3, postfix = 4 };
AVL dataOnTree;

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
    for (size = 0; size, 50; size++) {
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

void withoutWildcard(char* word, int size, int type) {    
    string buffer="";
    int ctr = 0;

    for (int i = 0; i < size ; i++ ) {
        if (!word[i] == '*')
            buffer += word[i];      
    }

    //use str cpy
}

/*


    Structures Used


*/

struct dictionary {
	char word[50];
	char pron[60]; //pronunciation
	char type[4];
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
    nodeT* T2 = y->left;

    // Perform rotation  
    y->left = root;
    root->right = T2;

    return y;
}


nodeT* AVL::RLRotate(nodeT* root) {
    root->right = LLRotate(root->right);
    return RRRotate(root);
}


nodeT* AVL::LLRotate(nodeT* root) {
    nodeT* x = root->left;
    nodeT* T2 = x->right;

    // Perform rotation  
    x->right = root;
    root->left = T2;

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
        file.seekg(pos);
		file.write((char*)&word, sizeof(word));
	}
}


dictionary readFromFile(fstream& file, int pos) {

	dictionary readData;
	if (!file.is_open()) {
		cout << "File did not open correctly!!(Reading From File Failed)";
	}
	else {
		file.seekg(pos);
		file.read((char*)&readData, sizeof(readData));
	}
	return readData;
}

//load dictionary records into memory
//only the word and the position of their respective meanings on the file are loaded 

void init() {
    dictionary incomingData;
    dicIndex treeNode;
    nodeT* buffer;
    int pos = 0;

    fstream file("data.bin", ios::binary | ios::in | ios::out);

    while (file.eof()) {
        incomingData = readFromFile(file, pos);
        buffer = dataOnTree.find(incomingData.word);

        //check if the record that was read is deleted data
        if (!incomingData.deleted) {
            //inserting a word that has not yet been inserted to the tree
            if (buffer == NULL) {
                strcpy_s(treeNode.word, incomingData.word);
                treeNode.posList.insert(pos);
                if (dataOnTree.isEmpty())
                    dataOnTree.root = dataOnTree.insert(dataOnTree.root, treeNode);
                else
                    dataOnTree.insert(dataOnTree.root, treeNode);
            }
            else
                buffer->data.posList.insert(pos);
        }  
        pos += sizeof(dictionary);
    }    
    file.close();
}




int main()
{
    //load data to memory
    init();

    char input='0';
    char x[50] = { '*','b','*' };
    int size = 0;
    string y;
    while (input != '4') {
        cout << "Welcome To The Application" << endl << endl;
        cout << "\t1. Serach the definition of a word." << endl;
        cout << "\t2. Add a dictionary record." << endl;
        cout << "\t3. About the dev team." << endl;
        cout << "\t4. Exit." << endl << endl;

        cout << "Enter Your Choice: ";
        cin >> setw(1) >> input;

        switch (input)
        {
        case '1':
            //code implementation for search 
            size = charArraySize(x);
            //withoutWildcard(x, size, searchType(x, size));
            //size = charArraySize(x);
            cout << x[size-1] << ", " << size << ", " << searchType(x, size);
            cin >> x;
            system("cls");
            break;
        case '2':
            //code implementation for add record
            system("cls");
            break;
        case '3':
            //code implementation for about
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
    

    
    

	

}
