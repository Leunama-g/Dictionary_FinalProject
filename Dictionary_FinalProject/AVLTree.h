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
	tree<T> insert(AVL<T>  av, T data);
	void preorder(AVL<T> t);
	void inorder(AVL<T> t);
	void postorder(AVL<T> t)
	tree<T> remove(AVL<T> t, T data);
	nodeT<T>* find(T data);
	void empty();
	virtual DList<T>* copy();
protected:
	nodeT<T>* root;
	int height(nodeT<T>* root)
	int difference(nodeT<T>* root)
	Tree balance(nodeT<T>* root)
	Tree RRRotate(nodeT<T>* root)
	Tree RLRotate(nodeT<T>* root)
	Tree LLRotate(nodeT<T>* root)
	Tree LRRotate(nodeT<T>* root)
private:

};

