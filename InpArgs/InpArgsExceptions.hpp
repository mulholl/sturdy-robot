#ifndef INP_ARGS_EXCEPTIONS_HPP
#define INP_ARGS_EXCEPTIONS_HPP

#include <exception>
#include <string>

namespace inpargs {
	struct  BadType{ };
	struct 	BadPrioritySpec{ };
	struct 	FileOpenFailed{ };
	class 	OptRedefined{
		public:
			OptRedefined(char c){
				optName = c + '\0';
			}
			OptRedefined(std::string str){
				optName = str;
			}
			virtual const char* what() const throw(){
				std::string msg = "The option " + optName + " was specified multiple times\n";
				return msg.c_str();
			}
		private:
			std::string optName;
	};
	class 	UnrecOpt{
		public:
			UnrecOpt(char c){
				optName = c + '\0';
			}
			UnrecOpt(std::string str){
				optName = str;
			}
			virtual const char* what() const throw(){
				std::string msg = "The option " + optName + " is not valid\n";
				return msg.c_str();
			}
		private:
			std::string optName;
	};
	class IncNumArgs{
		public:
			IncNumArgs(char c, int inp_min, int inp_max, int inp_actual){
				optName = c + '\0';
				min = inp_min;
				max = inp_max;
				actual = inp_actual;
			}
			IncNumArgs(std::string str, int inp_min, int inp_max, int inp_actual){
				optName = str;
				min = inp_min;
				max = inp_max;
				actual = inp_actual;
			}
			virtual const char* what() const throw(){
				std::string msg;
				std::string amt_provided;

				if (actual == 1){
					amt_provided = std::to_string(actual) + "argument was";
				}
				else {
					amt_provided = std::to_string(actual) + "arguments were";
				}
				if (actual < min){
					amt_provided = "only " + amt_provided;
				}

				if (min == max){
					if (max == 0){
						/* No arguments may be given */
						msg = "The option " + optName + " does not take any arguments, but " + amt_provided + " provided.\n";
					}
					else if (max > 0){
						/* An exact number of arguments is required */
						std::string amt_required;
						if (max == 1){
							amt_required = std::to_string(max) + "argument";
						}
						else {
							amt_required = std::to_string(max) + "arguments";
						}
						msg = "The option " + optName + " requires exactly " + amt_required + ", but " + amt_provided + " provided.\n";
					}
				}
				else if (min >= 0 && max < 0){
					/* A minimum number of arguments is required but there is no maximum */
					std::string amt_required;
					if (min == 1){
						amt_required = std::to_string(min) + "argument";
					}
					else {
						amt_required = std::to_string(min) + "arguments";
					}
					msg = "The option " + optName + " requires at least " + amt_required + ", but " + amt_provided + " provided.\n";
				}
				else if (max > 0 && min < 0){
					/* A maximum number of arguments is allowed but there is no minimum */
					std::string amt_required;
					if (max == 1){
						amt_required = std::to_string(max) + "argument";
					}
					else {
						amt_required = std::to_string(max) + "arguments";
					}
					msg = "The option " + optName + " can take up to " + amt_required + ", but " + amt_provided + " provided.\n";
				}
				else if (min >= 0 && max > 0){
					/* A minimum and maximum number of arguments are specified */
					std::string amt_required = std::to_string(min) + " and " + std::to_string(max) + " arguments";
					msg = "The option " + optName + " can take between " + amt_provided + ", but " + amt_provided + " provided.\n";
				}
				return msg.c_str();
			}
			unsigned int min, max, actual;
		private:
			std::string optName;
	};
	class OutsideRange{

	};
	class NotInList{

	};
}

#endif