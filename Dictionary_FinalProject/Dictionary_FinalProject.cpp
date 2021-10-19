#include <iostream>
#include <fstream>
#include <string>  
#include "linkedList.h"
#include "AVLTree.h"

using namespace std;

/*


    string enumerations for word types


*/

string noun = "noun", pronoun = "pron", adjective = "adje", adverb = "adve", preposition = "prep", conjunction = "conj", interjection = "inte";

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

void writeToFile(dictionary word, fstream& file) {
	if (!file.is_open()) {
		cout << "File did not open correctly!!(Writing to File Failed)";
	}
	else {
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


int main()
{
	

	

}
