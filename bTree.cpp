#include "bTree.h"
#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>
#include <stdexcept>




bTree::bTree() {
	root = NULL;
}

bTree::~bTree() {
	makeNull();
}




node* bTree::getRoot() {
	if (!root) return NULL;
	return root;
}



bool bTree::addRoot(person* p) {
	node* n = new node;
	if (!n) return false;
	n->data = p;
	n->parent = NULL;
	n->leftChild = NULL;
	n->rightChild = NULL;
	root = n;

	return true;
}



void bTree::printData() {
	if (!root) return;

	std::list<node*> nodeList;
	nodeList = preorder(root, nodeList);
	node* p;
	while (!nodeList.empty()) {
		p = nodeList.front();
		nodeList.pop_front();
		std::cout << p->data->name << " " << p->data->surname << ", " << p->data->birth << "\n";

	}
}



bool bTree::addRightChild(person* p, node* parent) {
	node* n = new node;
	if (!n) return false;
	n->data = p;
	n->leftChild = NULL;
	n->rightChild = NULL;
	n->parent = parent;
	parent->rightChild = n;

	return true;
}



bool bTree::addLeftChild(person* p, node* parent) {
	node* n = new node;
	if (!n) return false;
	n->data = p;
	n->leftChild = NULL;
	n->rightChild = NULL;
	n->parent = parent;
	parent->leftChild = n;

	return true;
}



node* bTree::find(std::string name, std::string surname, int birth){
	std::list<node*> nodeList;
	nodeList = preorder(root, nodeList);
	node* p;
	while (!nodeList.empty()) {
		p = nodeList.front();
		nodeList.pop_front();
		if (p->data->name == name && p->data->surname == surname && p->data->birth == birth)
			return p;
	}
	return NULL;
}



std::list<node*> bTree::preorder(node* n, std::list<node*> preorderList) {
	preorderList.push_back(n);
	node* p = leftMostChild(n);
	while (p) {
		preorderList = preorder(p, preorderList);
		p = rightSibling(p);
	}
	return preorderList;
}



node* bTree::leftMostChild(node* n) {
	if (n->leftChild) return n->leftChild;
	return n->rightChild;
}



node* bTree::rightSibling(node* n) {
	if (n->parent->rightChild == n) return NULL;
	return n->parent->rightChild;
}



void bTree::deleteNode(node* n) {
	if (!n) return;
	if (!n->parent) { root = NULL; return; }

	node* temp = n->parent;
	if (n->data->gender == 'f' || n->data->gender == 'F')
		temp->rightChild = NULL;
	if (n->data->gender == 'm' || n->data->gender == 'M')
		temp->leftChild = NULL;

	deleteNode(n->leftChild);
	deleteNode(n->rightChild);

	delete n;

}



void bTree::makeNull() { bTree::deleteNode(root);}



void bTree::writeTreeTXT(node* n, std::ostream& output) {
	if (!root) return;

	if (!n) output << "#\n";
	else {
		output
			<< n->data->name << " "
			<< n->data->surname << " "
			<< n->data->birth << " "
			<< n->data->gender << "\n";
		writeTreeTXT(n->leftChild, output);
		writeTreeTXT(n->rightChild, output);
	}
}



void bTree::readTreeTXT(std::ifstream& input) {
	std::vector<node*> nodeVector;
	std::queue<node*> nodeQueue;
	std::string str;
	//node* n;

	while(std::getline(input, str)) {
		node* nLocal = new node;
		if (str == "#")
			nLocal = NULL;
			
		else {
			std::istringstream ss(str);
			std::vector<std::string> tokens;
			std::string word;
			person* p = new person;

			while (ss >> word)
				tokens.push_back(word);
			
			p->name = tokens.at(0);
			p->surname = tokens.at(1);
			p->birth = std::stoi(tokens.at(2));
			p->gender = tokens.at(3).at(0);
			nLocal->data = p;
		}
		nodeVector.push_back(nLocal);
	}

	root = nodeVector.at(0);
	nodeQueue.push(root);

	for (int i = 1; i < nodeVector.size(); i++) {
		node* nLocal = nodeQueue.front();
		nodeQueue.pop();

		if (!nodeVector.at(i))
			nLocal->leftChild = NULL;
		else {
			nLocal->leftChild = nodeVector.at(i);
			nLocal->leftChild->parent = nLocal;
			nodeQueue.push(nLocal->leftChild);
		}
		if (!nodeVector.at(++i))
			nLocal->rightChild = NULL;
		else {
			nLocal->rightChild = nodeVector.at(i);
			nLocal->rightChild->parent = nLocal;
			nodeQueue.push(nLocal->rightChild);
		}
	}
}



/*std::list<node*>*/ void bTree::traceWantedNode(node* n) {
	if (!n) return;
	std::list<node*> nodeList;
	
	while (true) {
		nodeList.push_front(n);
		if (n->parent)
			n = n->parent;
		else break;
	}
	
	std::cout << "\n";
	while (!nodeList.empty()) {
		n = nodeList.front();
		nodeList.pop_front();
		if(nodeList.size() == 0)
			std::cout << n->data->name << " " << n->data->surname << ", " << n->data->birth << "\n";
		else
			std::cout << n->data->name << " " << n->data->surname << ", " << n->data->birth << "\n\tv\n";
	}
}
