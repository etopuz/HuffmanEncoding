#pragma once
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <iterator> 

struct Node {
	char data;
	int frequency;
	std::string huffmanCode;
	Node* left;
	Node* right;
	Node(char _data, int _frequency) : data(_data), frequency(_frequency), left(NULL), right(NULL) {}
};

class BinaryTree {
public:
	Node* root = new Node('\0',-1);

	// writes tree into file with preorder traversal
	void writeToFile(Node* root);

	// prints tree 
	void printTree(Node* root, int space);

	// creates huffman codes of nodes
	void createHufmannCodes(Node* root,std::string code);

	// creates tree
	void createTree(std::vector<Node> nodes);

	// encodes string add huffman codes to output
	void encode(Node* root, char c, std::string& output);

	// decodes codes ang print real message
	void decode(Node* root, std::string code, std::string& output);


};