template <class T>
struct nodeT {
	T data;
	nodeT<T>* left;
	nodeT<T>* right;
};
template <class T>
class AVL {
public:
	AVL(); //done
	virtual ~AVL();//done
	nodeT<T>* root;
	bool isEmpty(); //done
	nodeT<T>* insert(nodeT<T>* t, T data);//done
	void preorder(nodeT<T>* t);//done
	void inorder(nodeT<T>* t);//done
	void postorder(nodeT<T>* t);//done
	nodeT<T> minValueNode(nodeT<T>* node);//done
	nodeT<T>* remove(nodeT<T>* t, T data);//done
	nodeT<T>* find(T data);//done
	nodeT<T>* search(T data, nodeT<T>* t);//done
	nodeT<T>* empty(nodeT<T>* node);//done

protected:
	int height(nodeT<T>* root); //done
	int difference(nodeT<T>* root); //done
	nodeT<T>* balance(nodeT<T>* root); //done
	nodeT<T>* RRRotate(nodeT<T>* root); //done
	nodeT<T>* RLRotate(nodeT<T>* root); //done
	nodeT<T>* LLRotate(nodeT<T>* root); //done
	nodeT<T>* LRRotate(nodeT<T>* root); //done
private:

};

