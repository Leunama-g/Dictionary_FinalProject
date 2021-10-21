template <class T>
struct nodeL {
	T data;
	nodeL<T>* next;
};
template <class T>
class List { //unsorted list
public:
	List(); //default constructor
	virtual ~List(); //destructor
	bool isEmpty();
	void insert(T data);//insert always by tail
	int remove(T data);
	nodeL<T>* find(T data);
	void empty();
	void print();
	nodeL<T>* gethead();
protected:
	nodeL<T>* head;
	nodeL<T>* tail;
private:
	nodeL<T>* nodeToDelete(T data);//find predecessor of node to be deleted
};

