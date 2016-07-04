#ifndef INP_ARGS_CLASS_HPP
#define INP_ARGS_CLASS_HPP

#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <typeinfo> // for comparing types
#include <cctype>
#include <fstream>
#include <locale>
#include "InpArgsExceptions.hpp"
#include "InpArgsValue.hpp"

#define INP_ARG_CMD_ONLY 1
#define INP_ARG_FILE_ONLY 2
#define INP_ARG_CMD_PRIORITY 3
#define INP_ARG_FILE_PRIORITY 4
#define INP_ARG_EQUAL_PRIORITY 5

namespace inpargs{
	class InpArgsClass{
		private:
			std::vector< std::tuple<char, std::string, std::string, int, bool, int, bool> > validArgList;
			std::vector<unsigned int> optInds;
			std::vector<unsigned int> cmdNumArgs;
			std::vector< std::string > cmdOpts;
			std::vector< std::vector<std::string> > cmdArgs;
			std::vector<bool> cmdIsLong;
			std::vector<unsigned int> fileNumArgs;
			std::vector< std::string > fileOpts;
			std::vector< std::vector<std:: string> > fileArgs;
			std::vector<bool> fileIsLong;
			int argc;
			char** argv;
			unsigned int mode;
			std::string optionsFile;
			bool getOptionsFile;
			bool isCmdOption(std::string, bool &);
			bool isCmdOption(std::string);
			void gatherCmdOpts();
			void printCmdOpts();
			void gatherFileOpts();
			void printFileOpts();
			bool checkCmdArg(char, std::string, std::vector<std::string> &);
			bool checkFileArg(char, std::string, std::vector<std::string> &);

			/* convert(A, B) converts the strings in the vector A into the correct type for the vector B.
			 * If the type of B is not supported, an exception is thrown */
			static void convert(std::vector<std::string> &argsAsStrings, std::vector<std::string> &argsAsCorrectType);
			static void convert(std::vector<std::string> &argsAsStrings, std::vector<char> &argsAsCorrectType);
			static void convert(std::vector<std::string> &argsAsStrings, std::vector<bool> &argsAsCorrectType);
			static void convert(std::vector<std::string> &argsAsStrings, std::vector<int> &argsAsCorrectType);
			static void convert(std::vector<std::string> &argsAsStrings, std::vector<long> &argsAsCorrectType);
			static void convert(std::vector<std::string> &argsAsStrings, std::vector<long long> &argsAsCorrectType);
			static void convert(std::vector<std::string> &argsAsStrings, std::vector<float> &argsAsCorrectType);
			static void convert(std::vector<std::string> &argsAsStrings, std::vector<double> &argsAsCorrectType);
			static void convert(std::vector<std::string> &argsAsStrings, std::vector<long double> &argsAsCorrectType);	
			static void convert(std::vector<std::string> &argsAsStrings, std::vector<unsigned int> &argsAsCorrectType);
			static void convert(std::vector<std::string> &argsAsStrings, std::vector<unsigned long> &argsAsCorrectType);
			static void convert(std::vector<std::string> &argsAsStrings, std::vector<unsigned long long> &argsAsCorrectType);			

			/* This template catches other types that cannot currently be converted and throws an exception */
			template <typename T>
			static void convert(std::vector<std::string> &argsAsStrings, std::vector<T> &argsAsCorrectType){
					throw inpargs::CannotConvert{ };
			}

			static std::string strToUpper(std::string);
			static void trimLWSpace(std::string &);
			static void trimRWSpace(std::string &);
			static std::string splitAtFirstWS(std::string &);
		public:
			/* Add an argument */
			template <typename T>
			void addOpt(char opt_short, std::string opt_long, std::string help_text, value<T> &val){
				bool optUsed;

				/* First, check that T is a type that we can deal with */
				if ((typeid(T) != typeid(unsigned int)) &&(typeid(T) != typeid(int)) && (typeid(T) != typeid(float)) && (typeid(T) != typeid(double)) && (typeid(T) != typeid(bool)) && (typeid(T) != typeid(char)) && (typeid(T) != typeid(std::string))){
					throw inpargs::BadType{ };
				}


				/* Add to the list of valid arguments */
				std::tuple<char, std::string, std::string, int, bool, int, bool> tup (opt_short, opt_long, help_text, val.minArgs, val.minArgsSpec, val.maxArgs, val.maxArgsSpec);
				validArgList.push_back(tup);

				/* Check if this argument was used, either at the command line or in an input file */
				std::vector<std::string> argsAsStrings; // argsAsStrings will store the arguments to the option as a vector of strings
				optUsed = checkArg(opt_short, opt_long, argsAsStrings);

				/* If the option has been used, convert the arguments to the correct type and then attempt to validate and assign them */
				if (optUsed){
					std::vector<T> argsAsCorrectType;
					convert(argsAsStrings, argsAsCorrectType);
					val.validateAndAssign(argsAsCorrectType);
				}
				/* If the option has not been used but a default value was specified, assign that value */
				else {
					if (val.defSpec){
						val.useDefault();
					}
				}

			}

			bool checkArg(char, std::string, std::vector<std::string> &);
			bool isValidArg(char);
			bool isValidArg(std::string);
			std::string listArgs();
			InpArgsClass(int, char**);
			InpArgsClass(int, char**, std::string, std::string);
			InpArgsClass(std::string);
	};
}

#endif
