struct dicIndex {
	char word[50];
	List<int> posList;// list of position(references) of record on the file
};

struct nodeT {
	dicIndex data;
	nodeT* left;
	nodeT* right;
};

class AVL {
public:
	AVL(); //done
	virtual ~AVL();//done
	nodeT* root;
	bool isEmpty(); //done
	nodeT* insert(nodeT* t, dicIndex data);//done
	void preorder(nodeT* t);//done
	void inorder(nodeT* t);//done
	void postorder(nodeT* t);//done
	nodeT* minValueNode(nodeT* node);//done
	nodeT* remove(nodeT* t, dicIndex data);//done
	nodeT* find(char data[]);//done
	nodeT* search(char data[], nodeT* t);//done
	nodeT* empty(nodeT* node);//done

protected:
	int height(nodeT* root); //done
	int difference(nodeT* root); //done
	nodeT* balance(nodeT* root); //done
	nodeT* RRRotate(nodeT* root); //done
	nodeT* RLRotate(nodeT* root); //done
	nodeT* LLRotate(nodeT* root); //done
	nodeT* LRRotate(nodeT* root); //done
private:

};

