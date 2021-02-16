#include <fstream>
#include <array>
#include <sstream>
#include "BinaryTree.h"
#include "FileLogger.h"



void readFromFile(std::string path, std::map<char, int>& tempMap);
void createNodeList(std::vector<Node>& tempList, std::string);

// fills charMap
void fillCharMap(std::string path, std::map<int, std::string>& charMap) {
    // temp map holds key as char , value as frequency of that char
    std::map<char, int> tempMap;
    readFromFile(path, tempMap);
    std::map<char, int>::iterator itrTemp;
    for (itrTemp = tempMap.begin(); itrTemp != tempMap.end(); ++itrTemp)
    {
        charMap[itrTemp->second] += itrTemp->first;
    }

}

// reads input will encoded
void readFromFile(std::string path, std::map<char, int>& tempMap) {
    std::string line;
    std::ifstream file;

    file.open(path);
    if (!file) {
        std::cout << "Unable to open file." << std::endl << "Please check filename.\n";
        exit(1); // if error occurs exit from app
    }
    //itarate through commands file
    while (getline(file, line, '\n')) {

        // -- counting algorithm with hashmaps
        for (char _c : line) {
            // if tempMap has a value paired with key c add 1 to value
            char c = tolower(_c);
            if (tempMap.count(c)) {
                tempMap[c]++;
            }
            // if no value paired with key c instantiate it
            else {
                tempMap[c] = 1;
            }
        }
    }
    file.close();
}

// creates NodeList from frequency_map txt <<overloading>>
void createNodeList(std::vector<Node>& tempList, std::string path, bool from_frequency_map) {
    std::string line;
    std::ifstream file;

    file.open(path);
    if (!file) {
        std::cout << "Unable to open file." << std::endl << "Please check filename.\n";
        exit(1); // if error occurs exit from app
    }
    //itarate through commands file
    while (getline(file, line, '\n')) {
        std::array<std::string, 2> charAndFrequency{ "",""};
        std::string item;
        std::istringstream iss(line);
        int i = 0;
        while (getline(iss, item, ':')) {
            charAndFrequency[i++] = item;
        }
        char data = charAndFrequency[0][0];
        int frequency = stoi(charAndFrequency[1]);
        Node myNode(data, frequency);
        tempList.push_back(myNode);
    }
    file.close();
}

// creates NodeList from map
void createNodeList(std::vector<Node>& tempList, std::string path)
{
    std::map<int, std::string >::iterator itr;

    // (key : frequency) - (value : array of chars with same frequencies)
    std::map<int, std::string> charMap;

    fillCharMap(path, charMap);

    // For saving frequency table to file
    std::string freqMapPath = "frequency_map.txt";
    FileLogger::createNew(freqMapPath);

    //looping through map
    for (itr = charMap.begin(); itr != charMap.end(); ++itr)
    {
        // looping through char array which chars have same frequency
        for (char c : itr->second) {
            char data = c;
            int frequency = itr->first;
            Node myNode(data, frequency);
            tempList.push_back(myNode);
            std::string out;
            out.append(1, data);
            out += ":" + std::to_string(frequency) + "\n";
            FileLogger::Log(out, freqMapPath);
        }
        
    }
}

// read all lines in text files
void readAllLines(std::string path, std::string& lines) {
    std::string line;
    std::ifstream file;

    file.open(path);
    if (!file) {
        std::cout << "Unable to open file." << std::endl << "Please check filename.\n";
        exit(1); // if error occurs exit from app
    }
    //itarate through commands file
    while (getline(file, line, '\n')) {
        lines += line;
    }
    file.close();
}