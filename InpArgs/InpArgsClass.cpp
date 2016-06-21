#include "InpArgsClass.hpp"

using namespace std;

void InpArgsClass::addArg(char opt_short, string opt_long, string help_text, unsigned int min_args, unsigned int max_args){
	string val;
	tuple<char, string, string> tup (opt_short, opt_long, help_text, min_args, max_args);
	validArgList.push_back(tup);
	checkArg(opt_short, opt_long, val);
}

void InpArgsClass::addArg(char opt_short, string help_text, unsigned int min_args, unsigned int max_args){
	addArg(opt_short, "\0", help_text, min_args, max_args);
}

void InpArgsClass::addArg(string opt_long, string help_text, unsigned int min_args, unsigned int max_args){
	addArg('\0', opt_long, help_text, min_args, max_args);
}

bool InpArgsClass::checkArg(char opt_short, string opt_long, string &val){
	string opt_short_2 = "-" + opt_short;
	opt_long = "--" + opt_long;
	string temp;

	bool ret = false;

	cout << "argc = " << argc << endl;

	if (argc){
		for (unsigned int it = 0; it < argc - 1; ++it){
			temp = argv[it + 1];
			cout << "temp = " << temp << endl;
			if (opt_short_2.compare(temp) || (opt_long.compare(temp))){
				val = argv[it + 2];
				cout << "FOUNT IT! val = " << val << endl;
				ret = true;
			}
		}
	}

	return ret;
}

bool InpArgsClass::isValidArg(char opt_short){
	if (opt_short == '\0' || validArgList.size() == 0){
		return false;
	}
	else {
		for (vector< tuple<char, string, string> >::iterator it = validArgList.begin(); it != validArgList.end(); ++it){
			if (opt_short == get<0>(*it)){
				return true;
			}
		}
	}

	return false;
}

bool InpArgsClass::isValidArg(string opt_long){
	if (opt_long.length() == 0 || validArgList.size() == 0){
		return false;
	}
	else {
		for (vector< tuple<char, string, string> >::iterator it = validArgList.begin(); it != validArgList.end(); ++it){
			if (opt_long.compare(get<1>(*it))){
				return true;
			}
		}
	}

	return false;
}

string InpArgsClass::listArgs(){
	string opt_long = "";

	for (vector< tuple<char, string, string> >::iterator it = validArgList.begin(); it != validArgList.end(); ++it){
		opt_long = opt_long + "  -" + get<0>(*it) + "    --" + get<1>(*it) + "        " + get<2>(*it) + "\n"; 
	}

	return opt_long;
}

InpArgsClass::InpArgsClass(int arg_c, char** arg_v){
	argc = arg_c;
	argv = arg_v;
	optionsFile.clear();
	validArgList.clear();
	validArgList.resize(0);
}

InpArgsClass::InpArgsClass(int arg_c, char** arg_v, string options_file){
	argc = arg_c;
	argv = arg_v;
	optionsFile = options_file;
	validArgList.clear();
	validArgList.resize(0);
}

InpArgsClass::InpArgsClass(string options_file){
	argc = 0;
	optionsFile = options_file;
	validArgList.clear();
	validArgList.resize(0);
}