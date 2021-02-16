#pragma once
#include <iostream>
#include <fstream>
#include <string>

class FileLogger {
	
public:
	static void Log(std::string line, std::string outputPath) {
		std::ofstream output;
		output.open(outputPath, std::ios::out | std::ios::app);
		output<<line;
		output.close();
	}

	static void createNew(std::string outputPath) {
		std::ofstream output;
		output.open(outputPath);
	}
};