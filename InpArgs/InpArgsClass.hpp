#ifndef INP_ARGS_CLASS
#define INP_ARGS_CLASS

#include <iostream>
#include <vector>
#include <tuple>
#include <string>

class InpArgsClass{
	private:
		std::vector< std::tuple<char, std::string, std::string> > validArgList;
		std::vector< std::tuple<char, std::string, std::string> > usedArgs;
		int argc;
		char** argv;
		std::string optionsFile;
	public:
		void addArg(char, std::string, std::string, unsigned int, unsigned int);
		void addArg(char, std::string, unsigned int, unsigned int);
		void addArg(std::string, std::string, unsigned int, unsigned int);
		bool checkArg(char, std::string, std::string &);
		bool isValidArg(char);
		bool isValidArg(std::string);
		std::string listArgs();
		InpArgsClass(int, char**);
		InpArgsClass(int, char**, std::string);
		InpArgsClass(std::string);
};

#endif
