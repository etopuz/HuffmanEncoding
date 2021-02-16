#include "BinaryTree.h"

void BinaryTree::writeToFile(Node* root) 
{
	if (root == nullptr)
		return;
	bool isLeaf = (root->data != '\0');

	if (isLeaf)
		std::cout << root->data << ":" << root->frequency << ":" << root->huffmanCode << std::endl;
	writeToFile(root->left);
	writeToFile(root->right);

}

void BinaryTree::createHufmannCodes(Node* root, std::string code)
{
	if (root == nullptr)
		return;
	root->huffmanCode = code;
	createHufmannCodes(root->left, code+"0"); // goes left, add 0 to code
	createHufmannCodes(root->right, code+"1"); // goes right, add 1 to code
}

void BinaryTree::printTree(Node* node, int cell) 
{
	if (node == NULL)
		return;

	printTree(node->right, cell+6);
	for (int i = 0; i < cell; i++)
		std::cout << "  ";

	if (node->data != '\0') // if current node is leaf
		std::cout << node->frequency << std::endl;
	else { // if current node is not leaf
		std::cout << node->frequency;
		std::cout << "----------";
		std::cout << std::endl;
	}

	std::cout << "\n";

	printTree(node->left, cell+6);
}

void BinaryTree::createTree(std::vector<Node> nodes)
{
	Node* nodeNotLeaf1 = new Node('\0', -2);
	Node* nodeNotLeaf2 = new Node('\0', -2);

	// if only one or two unique char
	if (nodes.size() < 3) {
		for (int i = 0; i < nodes.size(); i++) {
			char data = nodes.at(i).data;
			int freq = nodes.at(i).frequency;
			Node* node = new Node(data, freq);
			if (i == 0) {
				root->left = node;
				root->frequency += root->left->frequency;
			}
				
			else if (i == 1) {
				root->right = node;
				root->frequency += root->right->frequency;
			}
				
		}
	}

	// if only 3 unique char
	else if (nodes.size() == 3) {
		for (int i = 0; i < nodes.size(); i++) {
			char data = nodes.at(i).data;
			int freq = nodes.at(i).frequency;
			Node* node = new Node(data, freq);
			if (i == 0)
				nodeNotLeaf1->left = node;
			if (i == 1)
				nodeNotLeaf1->right = node;
			if (i == 2) {
				nodeNotLeaf1->frequency = nodeNotLeaf1->right->frequency + nodeNotLeaf1->left->frequency;
				root->left = nodeNotLeaf1;
				root->right = node;
				root->frequency = root->left->frequency + root->right->frequency;
			}
		}
	}

	// if there is more than 3 unique char
	else {
		for (int i = 0; i < nodes.size(); i++) {
			char data = nodes.at(i).data;
			int freq = nodes.at(i).frequency;
			Node* node = new Node(data, freq);
			if (i == 0) 
				nodeNotLeaf1->left = node;

			else if (i == 1) 
				nodeNotLeaf1->right = node;

			else if (i == 2)
				nodeNotLeaf2->left = node;

			else if (i == 3) {
				nodeNotLeaf2->right = node;
				nodeNotLeaf1->frequency = nodeNotLeaf1->right->frequency + nodeNotLeaf1->left->frequency;
				nodeNotLeaf2->frequency = nodeNotLeaf2->right->frequency + nodeNotLeaf2->left->frequency;
			}
				

			else if (i % 2 == 0) {
				Node* tempSibling = new Node('\0', nodeNotLeaf1->frequency);
				tempSibling->right = nodeNotLeaf1->right;
				tempSibling->left = nodeNotLeaf1->left;
				nodeNotLeaf1->left = tempSibling;
				nodeNotLeaf1->right = node;
				nodeNotLeaf1->frequency = nodeNotLeaf1->right->frequency + nodeNotLeaf1->left->frequency;
			}

			else if (i % 2 == 1) {
				Node* tempSibling = new Node('\0', nodeNotLeaf2->frequency);
				tempSibling->right = nodeNotLeaf2->right;
				tempSibling->left = nodeNotLeaf2->left;
				nodeNotLeaf2->right = tempSibling;
				nodeNotLeaf2->left = node;
				nodeNotLeaf2->frequency = nodeNotLeaf2->right->frequency + nodeNotLeaf2->left->frequency;
			}

		}
		root->left = nodeNotLeaf1;
		root->right = nodeNotLeaf2;
		root->frequency = root->left->frequency + root->right->frequency;
	}

	createHufmannCodes(root, "");
}

void BinaryTree::encode(Node* node, char c, std::string& output)
{
	if (node == nullptr)
		return ;

	if (c == node->data)
		output+= node->huffmanCode;

	encode(node->left,c,output);
	encode(node->right,c,output);
}

void BinaryTree::decode(Node* node, std::string code, std::string& output)
{
	if (node == nullptr)
		return;

	for (char c : code) {
		if (node) {
			if (c == '0')
				node = node->left;
			else if (c == '1')
				node = node->right;
			if (node->data != '\0') {
				output += node->data;
				node = this->root;
			}
		}

	}
}


