#ifndef VALID_ARGS_HPP
#define VALID_ARGS_HPP

#include <vector>
#include <tuple>
#include <string>

class ValidArgs{
	private:
		std::vector< std::tuple<char, std::string, std::string> > argList;
	public:
		void addArg(char, std::string, std::string);
		void addArg(char, std::string);
		void addArg(std::string, std::string);
		bool isValidArg(char);
		bool isValidArg(std::string);
		std::string listArgs();
		ValidArgs();
};

#endif