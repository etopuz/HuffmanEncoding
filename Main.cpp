#include <fstream>
#include "BinaryTree.h"
#include "FileLogger.h"

void readAllLines(std::string path, std::string& lines);
void readFromFile(std::string path, std::map<char, int>& tempMap);
void fillCharMap(std::string path, std::map<int, std::string>& charMap);
void createNodeList(std::vector<Node>& tempList, std::string path);
void executeEncodeOperation(BinaryTree& bt, std::string message, bool writeToFile);
void executeDecodeOperation(BinaryTree& bt, std::string encodedMessage);
void createNodeList(std::vector<Node>& tempList, std::string path, bool from_frequency_map);

int main(int argc, char* argv[])
{
	BinaryTree bt;
	// first command can be -i, -s or ,l
	// second command can be -encode or -decode
	std::string  firstCommand = argv[1];
	if (firstCommand == "-i") {
		std::vector<Node> nodeList;
		std::string filePath = argv[2];
		std::string secondCommand = argv[3];
		bool encode = ("-encode" == secondCommand);
		bool decode = ("-decode" == secondCommand);
		if (encode) {

			createNodeList(nodeList, filePath);
			bt.createTree(nodeList);
			std::string message;
			readAllLines(filePath, message);
			executeEncodeOperation(bt, message,1);
		}
		else if(decode) {
			createNodeList(nodeList, "frequency_map.txt", 1);
			bt.createTree(nodeList);
			std::string encodedMessage;
			readAllLines(filePath, encodedMessage);
			executeDecodeOperation(bt, encodedMessage);
		}
		else {
			std::cout << "please give command as  -encode or -decode \n";
		}
	}

	else if (firstCommand == "-l") {
		std::vector<Node> nodeList;
		createNodeList(nodeList, "frequency_map.txt", 1);
		bt.createTree(nodeList);
		bt.printTree(bt.root, 0);
	}

	else if (firstCommand == "-s") {
		std::vector<Node> nodeList;
		std::string character = argv[2];
		createNodeList(nodeList, "frequency_map.txt", 1);
		bt.createTree(nodeList);
		executeEncodeOperation(bt, character, 0);
	}
}


void executeEncodeOperation(BinaryTree& bt, std::string message, bool writeToFile) {
    std::string output = "";
    for (char c : message)
        bt.encode(bt.root, std::tolower(c), output);
    std::cout << output + "\n";
	if(writeToFile){
		std::string outputPath = "encoded_message_b21827905.txt";
    	FileLogger::createNew(outputPath);
    	FileLogger::Log(output + "\n", outputPath);
	}

}


void executeDecodeOperation(BinaryTree& bt, std::string encodedMessage) {
    std::string output = "";
    bt.decode(bt.root, encodedMessage, output);
    std::cout << output + "\n";
}

