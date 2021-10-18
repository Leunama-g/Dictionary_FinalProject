template <class T>
struct nodeT {
	T data;
	nodeT<T>* left;
	nodeT<T>* right;
};
template <class T>
class AVL {
public:
	AVL(); //default constructor
	AVL(AVL<T>& av); //copy constructor
	virtual ~AVL(); //destructor
	int isEmpty();
	AVL<T> insert(AVL<T>  av, T data);
	void preorder(AVL<T> t);
	void inorder(AVL<T> t);
	void postorder(AVL<T> t);
	AVL<T> remove(AVL<T> t, T data);
	nodeT<T>* find(T data);
	void empty();
protected:
	nodeT<T>* root;
	int height(nodeT<T>* root);
	int difference(nodeT<T>* root);
	AVL<T> balance(nodeT<T>* root);
	AVL<T> RRRotate(nodeT<T>* root);
	AVL<T> RLRotate(nodeT<T>* root);
	AVL<T> LLRotate(nodeT<T>* root);
	AVL<T> LRRotate(nodeT<T>* root);
private:

};

