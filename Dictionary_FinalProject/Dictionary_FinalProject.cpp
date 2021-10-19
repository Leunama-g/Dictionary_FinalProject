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

struct dicIndex {
    char word[50];
    List<int> posList;// list of position(references) of record on the file
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

template <class T>
AVL<T>::AVL() {
    root = NULL;
}

template <class T>
AVL<T>::~AVL() {
    empty();
}

template <class T>
nodeT<T>* AVL<T>::empty(nodeT<T>* node) {
    if (node == NULL) {
        return NULL;
    }
    else {
        empty(node->left);
        empty(node->right);
        delete node;
        return NULL;
    }
}

template <class T>
nodeT<T>* AVL<T>::search(T data, nodeT<T>* t) {
    if (t == NULL) {
        return NULL;
    }
    else if (data == t->data) {
        return t;
    }
    else if (data < t->data) {
        return search(data, t->left);
    }
    else {
        return search(data, t->right);
    }
}

template <class T>
nodeT<T>* AVL<T>::find(T data) {
    return search(data, root);
}

template <class T>
bool AVL<T>::isEmpty() {
    return root == NULL;
}

template <class T>
int AVL<T>::height(nodeT<T>* root) {
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

template <class T>
int AVL<T>::difference(nodeT<T>* root) {
    if (root == NULL)
        return -1;
    return height(root->left) - height(root->right);
}

template <class T>
nodeT<T>* AVL<T>::RRRotate(nodeT<T>* root) {
    nodeT<T>* y = root->right;
    nodeT<T>* T2 = y->left;

    // Perform rotation  
    y->left = root;
    root->right = T2;

    return y;
}

template <class T>
nodeT<T>* AVL<T>::RLRotate(nodeT<T>* root) {
    root->right = LLRotate(root->right);
    return RRRotate(root);
}

template <class T>
nodeT<T>* AVL<T>::LLRotate(nodeT<T>* root) {
    nodeT<T>* x = root->left;
    nodeT<T>* T2 = x->right;

    // Perform rotation  
    x->right = root;
    root->left = T2;

    return x;
}

template <class T>
nodeT<T>* AVL<T>::LRRotate(nodeT<T>* root) {
    root->left = RRRotate(root->left);
    return LLRotate(root);
}

template <class T>
nodeT<T>* AVL<T>::balance(nodeT<T>* root) {
    int bf = difference(root);

    if (bf > 1)
    {
        if (difference(root->l) > 0)
            root = LLRotate(root);
        else
            root = LRRotate(root);
    }
    else if (bf < -1)
    {
        if (difference(root->r) > 0)
            root = RLRotate(root);
        else
            root = RRRotate(root);
    }
    return root;
}

template <class T>
nodeT<T>* AVL<T>::insert(nodeT<T>* t, T data) {
    if (t == NULL)
    {
        t = new nodeT<T>*;
        t->data = data;
        t->left = NULL;
        t->right = NULL;
        return t;
    }
    else if (data < t->data)
    {
        t->left = insert(t->left, data);
        t = balance(t);
    }
    else if (data >= t->data)
    {
        t->right = insert(t->right, data);
        t = balance(t);
    }
}

template <class T>
nodeT<T> AVL<T>::minValueNode(nodeT<T>* node) {
    nodeT<T>* current = node;
    
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

template <class T>
nodeT<T>* AVL<T>::remove(nodeT<T>* t, T data) {
    if (t == NULL) {
        return NULL;
    }
    else if (data < t->data) {
        t->left = remove(t->left, data);
    }
    else if (data > t->data) {
        t->right = remove(t->right, data);
    }
    else {
        if (t->left == NULL) {
            nodeT<T>* temp = t->right;
            delete t;
            return temp;
        }
        else if (t->right == NULL) {
            nodeT<T>* temp = t->left;
            delete t;
            return temp;
        }
        else {       
            nodeT<T>* temp = minValueNode(t->right);
            t->value = temp->data;            
            t->right = remove(t->right, temp->data);          
        }
    }

    balance(t);

}

template <class T>
void AVL<T>::inorder(nodeT<T>* t)
{
    if (t == NULL)
        return;
    inorder(t->left);
    cout << t->data << " ";
    inorder(t->right);
}

template <class T>
void AVL<T>::preorder(nodeT<T>* t)
{
    if (t == NULL)
        return;
    cout << t->data << " ";
    preorder(t->left);
    preorder(t->right);
}

template <class T>
void AVL<T>::postorder(nodeT<T>* t)
{
    if (t == NULL)
        return;
    postorder(t->left);
    postorder(t->right);
    cout << t->data << " ";
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




int main()
{
	//test for write to file function

	fstream file("data.bin", ios::binary | ios::out | ios::in);

	dictionary wordData;

	wordData= readFromFile(file, 0);

	cout << wordData.word;


	

}
