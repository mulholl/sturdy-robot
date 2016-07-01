#ifndef INP_ARGS_CLASS
#define INP_ARGS_CLASS

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
			std::vector< std::tuple<char, std::string, std::string, unsigned int, unsigned int> > validArgList;
			// std::vector< std::tuple<char, std::string, std::string> > usedArgs;
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
			template <typename T, typename A>
			bool validate(T var, T min_val, T max_val){
				return (var >= min_val && var <= max_val);
			}
			template <typename T, typename A>
			bool validate(T var, std::vector<T, A> val_list){
				/* We will perform the validation differently based on whether the value is a string or some other type */
				if (typeid(var) == typeid(std::string)){
					/* Checking if a string argument is valid */
					for (std::vector<std::string>::iterator it = val_list.begin(); it < val_list.end(); ++it){
						if (var.compare(*it) == 0){
							return true;
						}
					}
					return false;
				}
				else {
					/* Checking whether an argument of any other type is valid */
					for (typename std::vector<T>::iterator it = val_list.begin(); it < val_list.end(); ++it){
						if (var == *it){
							return true;
						}
					}
					return false;
				}
			}
			static std::string strToUpper(std::string);
			static void trimLWSpace(std::string &);
			static void trimRWSpace(std::string &);
			static std::string splitAtFirstWS(std::string &);
		public:
			/* addArg(...)
			 * 		The addArg functions are used to add options that may be specified using the command 
			 * 		line/input file, and to check whether they have been specified and to validate the 
			 * 		input provided 
			 */
			/* Add an argument without a default value, minimum value, maximum value or list of valid values */
	 	// 	template <typename T>
			// void addArg(char opt_short, std::string opt_long, std::string help_text, T &var, unsigned int min_args, unsigned int max_args){
			// 	T def_val, min_val, max_val;
			// 	std::vector<T> val_list;
			// 	bool def_provided = false;
			// 	bool min_provided = false;
			// 	bool max_provided = false;
			// 	bool list_provided = false;
			// 	bool addToHelp = true;
			// 	addArg(opt_short, opt_long, help_text, var, def_val, def_provided, min_args, max_args, min_val, min_provided, max_val, max_provided, val_list, list_provided, addToHelp);
			// }
			// /* Add an argument without a default value, but with minimum and maximum values specified */
			// template <typename T>
			// void addArg(char opt_short, std::string opt_long, std::string help_text, T &var, unsigned int min_args, unsigned int max_args, T min_val, T max_val){
			// 	T def_val;
			// 	std::vector<T> val_list;
			// 	bool def_provided = false;
			// 	bool min_provided = true;
			// 	bool max_provided = true;
			// 	bool list_provided = false;
			// 	bool addToHelp = true;
			// 	addArg(opt_short, opt_long, help_text, var, def_val, def_provided, min_args, max_args, min_val, min_provided, max_val, max_provided, val_list, list_provided, addToHelp);
			// }
			// /* Add an argument without a default value, but with a list of valid values */
			// template <typename T, typename A>
			// void addArg(char opt_short, std::string opt_long, std::string help_text, T &var, unsigned int min_args, unsigned int max_args, std::vector<T, A> val_list){
			// 	T def_val, min_val, max_val;
			// 	bool def_provided = false;
			// 	bool min_provided = false;
			// 	bool max_provided = false;
			// 	bool list_provided = true;
			// 	bool addToHelp = true;
			// 	addArg(opt_short, opt_long, help_text, var, def_val, def_provided, min_args, max_args, min_val, min_provided, max_val, max_provided, val_list, list_provided, addToHelp);
			// }
			//  Add an argument with a default value, but without a minimum value, maximum value or list of valid values 
			// template <typename T>
			// void addArg(char opt_short, std::string opt_long, std::string help_text, T &var, T def_val, unsigned int min_args, unsigned int max_args){
			// 	T min_val, max_val;
			// 	std::vector<T> val_list;
			// 	bool def_provided = true;
			// 	bool min_provided = false;
			// 	bool max_provided = false;
			// 	bool list_provided = false;
			// 	bool addToHelp = true;
			// 	addArg(opt_short, opt_long, help_text, var, def_val, def_provided, min_args, max_args, min_val, min_provided, max_val, max_provided, val_list, list_provided, addToHelp);
			// }
			// /* Add an argument with a default value, minimum value and maximum value  */
			// template <typename T>
			// void addArg(char opt_short, std::string opt_long, std::string help_text, T &var, T def_val, unsigned int min_args, unsigned int max_args, T min_val, T max_val){
			// 	std::vector<T> val_list;
			// 	bool def_provided = true;
			// 	bool min_provided = true;
			// 	bool max_provided = true;
			// 	bool list_provided = false;
			// 	bool addToHelp = true;
			// 	addArg(opt_short, opt_long, help_text, var, def_val, def_provided, min_args, max_args, min_val, min_provided, max_val, max_provided, val_list, list_provided, addToHelp);
			// }
			// /* Add an argument with a default value and a list of default values  */
			// template <typename T, typename A>
			// void addArg(char opt_short, std::string opt_long, std::string help_text, T &var, T def_val, unsigned int min_args, unsigned int max_args, std::vector<T, A> val_list){
			// 	T min_val, max_val;
			// 	bool def_provided = true;
			// 	bool min_provided = false;
			// 	bool max_provided = false;
			// 	bool list_provided = true;
			// 	bool addToHelp = true;
			// 	addArg(opt_short, opt_long, help_text, var, def_val, def_provided, min_args, max_args, min_val, min_provided, max_val, max_provided, val_list, list_provided, addToHelp);
			// }		
			/* Add an argument */
			template <typename T>
			void addArg(char opt_short, std::string opt_long, std::string help_text, value<T> &val, int minArgs, int maxArgs, bool addToHelp){
			// template <typename T>		
			// void addArg(char opt_short, std::string opt_long, std::string help_text, T &var, T def_val, bool def_provided, unsigned int min_args, unsigned int max_args, T min_val, bool min_provided, T max_val, bool max_provided, std::vector<T> val_list, bool list_provided, bool addToHelp){

				// bool range_provided = min_provided && max_provided;

				/* First, check that T is a type that we can deal with */
				if ((typeid(T) != typeid(unsigned int)) &&(typeid(T) != typeid(int)) && (typeid(T) != typeid(float)) && (typeid(T) != typeid(double)) && (typeid(T) != typeid(bool)) && (typeid(T) != typeid(char)) && (typeid(T) != typeid(std::string))){
					throw inpargs::BadType{ };
				}

				std::vector<std::string> vals;

				/* Add to the list of valid arguments */
				std::tuple<char, std::string, std::string, unsigned int, unsigned int> tup (opt_short, opt_long, help_text, val.minArgs, val.maxArgs);
				validArgList.push_back(tup);

				/* Check if this argument was used, either at the command line or in an input file */
				checkArg(opt_short, opt_long, vals);
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
