#pragma once
#include <string>
#include <list>
#include <fstream>
#include <vector>



struct person {
	std::string name;
	std::string surname;
	int birth;
	char gender;
};

struct node {
	person* data;
	node* parent = NULL;
	node* leftChild;
	node* rightChild;
};

class bTree {
private:
	node* root;

public:
	bTree();
	~bTree();

	bool addRoot(person* p);
	node* getRoot();

	bool addLeftChild(person* p, node* parent);
	bool addRightChild(person* p, node* parent);
	void deleteNode(node* n);
	void makeNull();
	node* find(std::string name, std::string surname, int birth);
	void printData();
	
	void writeTreeTXT(node* n, std::ostream &output);
	/*std::list<node*>*/ void readTreeTXT(/*node*& n, */std::ifstream& input);
	/*std::list<node*> */void traceWantedNode(node* n);

private:
	std::list<node*> preorder(node* n, std::list<node*> preorderList);
	node* leftMostChild(node* n);
	node* rightSibling(node* n);
};
