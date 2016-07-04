#include "InpArgsClass.hpp"

using namespace std;

namespace inpargs{
	bool InpArgsClass::isCmdOption(string str, bool &ls){
		unsigned int str_len = str.length();
		ls = false;
		
		if (str_len == 2){
			if (str[0] == '-' && str[1] != '-'){
				return true;
			}
			else {
				return false;
			}
		}
		else if (str_len > 2) {
			if (str[0] == '-' && str[1] == '-'){
				ls = true;
				return true;
			}
			else {
				return false;
			}
		}

		return false;
	}

	bool InpArgsClass::isCmdOption(string str){
		bool temp_bool;

		return isCmdOption(str, temp_bool);
	}

	bool InpArgsClass::checkArg(char opt_short, string opt_long, vector<string> &val){
		vector<string> cmdVal;
		vector<string> fileVal;

		bool ret;

		// cout << "mode = " << mode <<endl;

		if (mode == INP_ARG_CMD_ONLY){
			ret = checkCmdArg(opt_short, opt_long, val);
		}
		else if (mode == INP_ARG_CMD_PRIORITY){
			if(!(ret = checkCmdArg(opt_short, opt_long, val))){
			// if (cmdVal.size()){
			// 	val = cmdVal;
			// }
			// else {
				ret = checkFileArg(opt_short, opt_long, val);
				// val = fileVal;
			}
		}
		else if (mode == INP_ARG_FILE_ONLY){
			ret = checkFileArg(opt_short, opt_long, val);
			// val = fileVal;
		}
		else if (mode == INP_ARG_FILE_PRIORITY){
			if (!(ret = checkFileArg(opt_short, opt_long, val))){
			// if (fileVal.size()){
				// val = fileVal;
			// }
			// else {
				ret = checkCmdArg(opt_short, opt_long, val);
				// val = cmdVal;
			}
		}
		else if (mode == INP_ARG_EQUAL_PRIORITY){

		}

		return ret;
	}

	bool InpArgsClass::checkCmdArg(char opt_short, string opt_long, vector<string> &val){
		unsigned int count;

		string opt_short_str(1, opt_short);

		for (vector<string>::iterator it = cmdOpts.begin(); it < cmdOpts.end(); ++it){
			// cout << "opt_short = " << opt_short << " | opt_long = " << opt_long << " | *it = " << *it << endl;
			if (opt_short_str.compare(*it) == 0 || opt_long.compare(*it) == 0){
				val = *(cmdArgs.begin() + distance(cmdOpts.begin(), it));
				return true;
			}
		}

		return false;
	}

	bool InpArgsClass::checkFileArg(char opt_short, string opt_long, vector<string> &val){
		unsigned int count;

		string opt_short_str(1, opt_short);

		for (vector<string>::iterator it = fileOpts.begin(); it < fileOpts.end(); ++it){
			if (opt_short_str.compare(*it) == 0 || opt_long.compare(*it) == 0){
				val = *(fileArgs.begin() + distance(fileOpts.begin(), it));
				return true;
			}
		}

		return false;
	}

	bool InpArgsClass::isValidArg(char opt_short){
		if (opt_short == '\0' || validArgList.size() == 0){
			return false;
		}
		else {
			for (vector< tuple<char, string, string, int, bool, int, bool> >::iterator it = validArgList.begin(); it != validArgList.end(); ++it){
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
			for (vector< tuple<char, string, string, int, bool, int, bool> >::iterator it = validArgList.begin(); it != validArgList.end(); ++it){
				if (opt_long.compare(get<1>(*it))){
					return true;
				}
			}
		}

		return false;
	}

	string InpArgsClass::listArgs(){
		string str = "";
		string opt_long = "";

		string argInfo;
		string valInfo;

		const unsigned int alignTo = 20;

		for (vector< tuple<char, string, string, int, bool, int, bool> >::iterator it = validArgList.begin(); it != validArgList.end(); ++it){
			opt_long = "";
			opt_long = opt_long + "  -" + get<0>(*it) + "    --" + get<1>(*it);
			unsigned int tempSize = opt_long.size();

			// cout << "tempSize = " << tempSize << endl;
			// cout << "alignTo = " << alignTo << endl;
			// cout << "opt_long = " << opt_long << "END" << endl;
			// cout << "alignTo - tempSize = " << alignTo - tempSize << endl;

			for (unsigned int it = 0; it < alignTo - tempSize; ++it){
				opt_long = opt_long + " ";
			} 

			opt_long = opt_long + get<2>(*it) + "\n";

			argInfo = "";

			for (unsigned int it = 0; it < alignTo; ++it){
				argInfo = argInfo + " ";
			} 

			if (get<4>(*it) && get<6>(*it)){
				if (get<3>(*it) == get<5>(*it)){
					argInfo = argInfo + "Takes exactly " + to_string(get<3>(*it)) + " arguments.\n";
				}
				else {
					argInfo = argInfo + "Takes " + to_string(get<3>(*it)) + "-" + to_string(get<5>(*it)) + " arguments.\n";
				}
			}
			else if (get<4>(*it)){
				argInfo = argInfo + "Takes at least " + to_string(get<3>(*it)) + " arguments.\n";
			}
			else if (get<6>(*it)){
				argInfo = argInfo + "Takes up to " + to_string(get<5>(*it)) + " arguments.\n";
			}
			else {
				argInfo = "";
			}

			str = str + opt_long + argInfo;
		}

		return str;
	}

	InpArgsClass::InpArgsClass(int arg_c, char** arg_v){
		argc = arg_c;
		argv = arg_v;
		optionsFile.clear();
		validArgList.resize(0);

		// getOptionsFile = false;

		mode = INP_ARG_CMD_ONLY;

		gatherCmdOpts();
		// printCmdOpts();

	}

	InpArgsClass::InpArgsClass(int arg_c, char** arg_v, string options_file, string priority){
		argc = arg_c;
		argv = arg_v;
		optionsFile = options_file;
		validArgList.clear();
		validArgList.resize(0);

		priority = strToUpper(priority);

		// getOptionsFile = options_file.is_empty() ? true : false;

		if (priority.compare("CF") == 0){
			mode = INP_ARG_CMD_PRIORITY;
		}
		else if (priority.compare("FC") == 0){
			mode = INP_ARG_FILE_PRIORITY;
		}
		else if (priority.compare("EQ") == 0){
			mode = INP_ARG_EQUAL_PRIORITY;
		}
		else {
			throw inpargs::BadPrioritySpec{ };
		}

		gatherCmdOpts();
		// printCmdOpts();

		gatherFileOpts();
		// printFileOpts();

	}

	InpArgsClass::InpArgsClass(string options_file){
		argc = 0;
		optionsFile = options_file;
		validArgList.clear();
		validArgList.resize(0);

		// getOptionsFile = false;

		mode = INP_ARG_FILE_ONLY;

		gatherFileOpts();
		// printFileOpts();

	}


	/*	gatherCmdOpts() gathers the options provided at the command line and populates several vectors:
			cmdOpts, which contains the options
			cmdArgs, which, for each option, contains a vector of the arguments provided to the option
			optInds, which contains the indices in argv where the options appeared
			cmdNumArgs, which contains the number of arguments provided for each of these options
			cmdIsLong, which specifies whether the option was a long or a short option
		The validity of the options/arguments is not checked here. Each vector has identical length and corresponding indices.
	*/
	void InpArgsClass::gatherCmdOpts(){
		optInds.resize(0);
		cmdNumArgs.resize(0);
		cmdOpts.resize(0);
		cmdArgs.resize(0);
		cmdIsLong.resize(0);

		vector<string> temp_vec;

		string current;
		unsigned int current_len;
		bool temp_bool;

		for (unsigned int it = 1; it < argc; ++it){
			current = argv[it]; // Pick out the current input argument
			current_len = current.length();

			/* Check if this string is an option - i.e., if it begins with '-' */
			if (isCmdOption(current, temp_bool)){
				cmdIsLong.push_back(temp_bool);
				unsigned int i = temp_bool ? 2 : 1;
				current.erase(current.begin(), current.begin()+i);
				cmdOpts.push_back(current);

				optInds.push_back(it);
			}
		}

		for (vector<unsigned int>::iterator it = optInds.begin(); it < optInds.end(); ++it){
			unsigned int current_opt_ind = *it;
			unsigned int next_opt_ind;
			temp_vec.clear();

			if (it < optInds.end() - 1){
				next_opt_ind = *(it + 1);
			}
			else {
				next_opt_ind = argc;
			}
			
			cmdNumArgs.push_back(next_opt_ind - current_opt_ind - 1);

			for (unsigned int it2 = current_opt_ind + 1; it2 < next_opt_ind; ++it2){
				temp_vec.push_back(argv[it2]);
			}

			cmdArgs.push_back(temp_vec);

		}
	}

	/* This is just for testing - it prints all of the options provided at the command line and the associated arguments, whether or not they are valid */
	void InpArgsClass::printCmdOpts(){
		cout << "Options/arguments provided at the command line:\n";
		cout << "\tOPTION\t\tARGUMENTS\n";
		for (unsigned int it = 0; it < cmdArgs.size(); ++it){
			// cout << "optInds[" << it << "] = " << optInds[it] << " | " << cmdNumArgs[it] << " arguments\n";
			cout << "\t" << cmdOpts[it] << "\n\t\t\t";
			for (vector<string>::iterator it2 = cmdArgs[it].begin(); it2 < cmdArgs[it].end(); ++it2){
				cout << *it2;
				if (it2 < cmdArgs[it].end() - 1){
					cout << ", ";
				}
			}
			cout << endl;
		}
	}

	// void InpArgsClass::convertStrToBool(vector<string> &argsAsStrings, vector<bool> &argsAsBools){
	// 	argsAsBools.resize(0);

	// 	string upper;

	// 	for (vector<string>::iterator it = argsAsStrings.begin(); it < argsAsStrings.end(); ++it){
	// 		upper = strToUpper(*it);
	// 		if (!upper.compare("Y") || !upper.compare("YES")  || !upper.compare("T") || !upper.compare("TRUE") || !upper.compare("ON")){
	// 			argsAsBools.push_back(true);
	// 		}
	// 		else if (!upper.compare("N") || !upper.compare("NO") || !upper.compare("F") || !upper.compare("FALSE") || !upper.compare("OFF")){
	// 			argsAsBools.push_back(false);
	// 		}
	// 		else {
	// 			throw inpargs::BadBoolValue{ };
	// 		}
	// 	}		
	// }

	// void InpArgsClass::convertStrToChar(vector<string> &argsAsStrings, vector<bool> &argsAsChars){
	// 	argsAsChars.resize(0);

	// 	for (vector<string>::iterator it = argsAsStrings.begin(); it < argsAsStrings.end(); ++it){
	// 		if ((*it).size() != 1){
	// 			throw ExpectedChar{ };
	// 		}
	// 		else {
	// 			argsAsChars.push_back((*it)[0]);
	// 		}
	// 	}
	// }

	// void convertStrToInt(vector<string> &argsAsStrings, vector<bool> &argsAsInts);
	// void convertStrToUInt(vector<string> &argsAsStrings, vector<bool> &argsAsUInts);
	// void convertStrToFloat(vector<string> &argsAsStrings, vector<bool> &argsAsFloats);
	// void convertStrToDouble(vector<string> &argsAsStrings, vector<bool> &argsAsDoubles);	


	void InpArgsClass::convert(std::vector<std::string> &argsAsStrings, std::vector<std::string> &argsAsCorrectType){
		argsAsCorrectType = argsAsStrings;
	}

	void InpArgsClass::convert(std::vector<std::string> &argsAsStrings, std::vector<char> &argsAsCorrectType){
		argsAsCorrectType.resize(0);

		for (std::vector<std::string>::iterator it = argsAsStrings.begin(); it < argsAsStrings.end(); ++it){
			if ((*it).size() != 1){
				throw ExpectedChar{ };
			}
			else {
				argsAsCorrectType.push_back((*it)[0]);
			}
		}
	}			

	void InpArgsClass::convert(std::vector<std::string> &argsAsStrings, std::vector<int> &argsAsCorrectType){
		argsAsCorrectType.resize(0);

		int val;

		std::string::size_type sz;   // alias of size_t

		for (std::vector<std::string>::iterator it = argsAsStrings.begin(); it < argsAsStrings.end(); ++it){
			try {
				val = std::stoi((*it), &sz);
			}
			catch (std::exception e){
				std::cout << e.what() << std::endl;
			}
			argsAsCorrectType.push_back(val);
		}
	}

	void InpArgsClass::convert(std::vector<std::string> &argsAsStrings, std::vector<long> &argsAsCorrectType){
		argsAsCorrectType.resize(0);

		long val;

		std::string::size_type sz;   // alias of size_t

		for (std::vector<std::string>::iterator it = argsAsStrings.begin(); it < argsAsStrings.end(); ++it){
			try {
				val = std::stol((*it), &sz);
			}
			catch (std::exception e){
				std::cout << e.what() << std::endl;
			}
			argsAsCorrectType.push_back(val);
		}
	}

	void InpArgsClass::convert(std::vector<std::string> &argsAsStrings, std::vector<long long> &argsAsCorrectType){
		argsAsCorrectType.resize(0);

		long long val;

		std::string::size_type sz;   // alias of size_t

		for (std::vector<std::string>::iterator it = argsAsStrings.begin(); it < argsAsStrings.end(); ++it){
			try {
				val = std::stoll((*it), &sz);
			}
			catch (std::exception e){
				std::cout << e.what() << std::endl;
			}
			argsAsCorrectType.push_back(val);
		}
	}

	void InpArgsClass::convert(std::vector<std::string> &argsAsStrings, std::vector<float> &argsAsCorrectType){
		argsAsCorrectType.resize(0);

		float val;

		std::string::size_type sz;   // alias of size_t

		for (std::vector<std::string>::iterator it = argsAsStrings.begin(); it < argsAsStrings.end(); ++it){
			try {
				val = std::stof((*it), &sz);
			}
			catch (std::exception e){
				std::cout << e.what() << std::endl;
			}
			argsAsCorrectType.push_back(val);
		}
	}

	void InpArgsClass::convert(std::vector<std::string> &argsAsStrings, std::vector<double> &argsAsCorrectType){
		argsAsCorrectType.resize(0);

		double val;

		std::string::size_type sz;   // alias of size_t

		for (std::vector<std::string>::iterator it = argsAsStrings.begin(); it < argsAsStrings.end(); ++it){
			try {
				val = std::stod((*it), &sz);
			}
			catch (std::exception e){
				std::cout << e.what() << std::endl;
			}
			argsAsCorrectType.push_back(val);
		}
	}		

	void InpArgsClass::convert(std::vector<std::string> &argsAsStrings, std::vector<long double> &argsAsCorrectType){
		argsAsCorrectType.resize(0);

		long double val;

		std::string::size_type sz;   // alias of size_t

		for (std::vector<std::string>::iterator it = argsAsStrings.begin(); it < argsAsStrings.end(); ++it){
			try {
				val = std::stold((*it), &sz);
			}
			catch (std::exception e){
				std::cout << e.what() << std::endl;
			}
			argsAsCorrectType.push_back(val);
		}
	}

	void InpArgsClass::convert(std::vector<std::string> &argsAsStrings, std::vector<unsigned int> &argsAsCorrectType){
		argsAsCorrectType.resize(0);

		unsigned int val;

		std::string::size_type sz;   // alias of size_t

		for (std::vector<std::string>::iterator it = argsAsStrings.begin(); it < argsAsStrings.end(); ++it){
			try {
				val = std::stoul((*it), &sz);
			}
			catch (std::exception e){
				std::cout << e.what() << std::endl;
			}
			argsAsCorrectType.push_back(val);
		}
	}			

	void InpArgsClass::convert(std::vector<std::string> &argsAsStrings, std::vector<unsigned long> &argsAsCorrectType){
		argsAsCorrectType.resize(0);

		unsigned long val;

		std::string::size_type sz;   // alias of size_t

		for (std::vector<std::string>::iterator it = argsAsStrings.begin(); it < argsAsStrings.end(); ++it){
			try {
				val = std::stoul((*it), &sz);
			}
			catch (std::exception e){
				std::cout << e.what() << std::endl;
			}
			argsAsCorrectType.push_back(val);
		}
	}

	void InpArgsClass::convert(std::vector<std::string> &argsAsStrings, std::vector<unsigned long long> &argsAsCorrectType){
		argsAsCorrectType.resize(0);

		unsigned long long val;

		std::string::size_type sz;   // alias of size_t

		for (std::vector<std::string>::iterator it = argsAsStrings.begin(); it < argsAsStrings.end(); ++it){
			try {
				val = std::stoull((*it), &sz);
			}
			catch (std::exception e){
				std::cout << e.what() << std::endl;
			}
			argsAsCorrectType.push_back(val);
		}
	}	

	void InpArgsClass::convert(std::vector<std::string> &argsAsStrings, std::vector<bool> &argsAsCorrectType){
		argsAsCorrectType.resize(0);

		std::string upper;

		for (std::vector<std::string>::iterator it = argsAsStrings.begin(); it < argsAsStrings.end(); ++it){
			upper = strToUpper(*it);
			if (!upper.compare("Y") || !upper.compare("YES")  || !upper.compare("T") || !upper.compare("TRUE") || !upper.compare("ON")){
				argsAsCorrectType.push_back(true);
			}
			else if (!upper.compare("N") || !upper.compare("NO") || !upper.compare("F") || !upper.compare("FALSE") || !upper.compare("OFF")){
				argsAsCorrectType.push_back(false);
			}
			else {
				throw inpargs::BadBoolValue{ };
			}
		}		
	}


	string InpArgsClass::strToUpper(string str){
		string str2 = str;
		unsigned int len = str.length();

		for (unsigned int it = 0; it < len; ++it){
			str2[it] = toupper(str2[it]);
		}

		return str2;
	}

	/* trimLWSpace(string &str) trims any whitespace at the beginning of str */
	void InpArgsClass::trimLWSpace(string &str){
		locale loc;
		unsigned int str_len = str.length();
		unsigned int it;

		for (it = 0; it < str_len; ++it){
			if (!isspace(str[it], loc))
				break;
		}

		str = str.substr(it, str_len - it);
	}

	/* trimLWSpace(string &str) trims any whitespace at the end of str */
	void InpArgsClass::trimRWSpace(string &str){
		locale loc;
		unsigned int str_len = str.length();
		unsigned int it;

		// cout << "str = " << str << endl;

		for (it = str_len - 1; it >= 0; --it){
			// cout << "\tstr[" << it << "] = " << str[it] << endl;
			if (!isspace(str[it], loc))
				break;
		}

		str = str.substr(0, it + 1);

		// cout << "str went from " << str_len << " to " << str.length() << " characters" << endl;
		// cout << "str is now = " << str << endl;
	}

	/* splitAtFirstWs(string &str1) splits str1 in two at the first whitespace character. The return value is everything up to this character, str1 is modified to be everything after this character. Leading whitespace is trimmed from str1 before and after the split */
	string InpArgsClass::splitAtFirstWS(string &str1){
		locale loc;
		string str2 = "";

		trimLWSpace(str1);

		unsigned int str1_len = str1.length();

		for (unsigned int it = 0; it < str1_len + 1; ++it){
			if (it == str1_len){
				str2 = str1;
				str1 = "";
				break;
			}
			else if (isspace(str1[it], loc)){
				str2 = str1.substr(0, it);
				// cout << "it+1 = " << it+1 << endl;
				// cout << "str1_len = " << str1_len << endl;
				// cout << "str1_len - it - 1 = " << str1_len - it - 1 << endl;
				str1 = str1.substr(it+1, str1_len - it - 1);
				break;
			}
		}

		trimLWSpace(str1);

		return str2;
	}

	void InpArgsClass::gatherFileOpts(){
		// optInds.resize(0);
		fileNumArgs.resize(0);
		fileOpts.resize(0);
		fileArgs.resize(0);
		fileIsLong.resize(0);

		vector<string> temp_vec;

		ifstream ifs(optionsFile);
		string current_line;
		string category = "";
		string option;
		string arguments, argument;
		unsigned int ind;

		if(!ifs.is_open()){
			throw inpargs::FileOpenFailed{ };
		}

		while(getline(ifs, current_line)){
			// cout << "current_line = \n" << current_line << endl;
			trimLWSpace(current_line);
			// cout << "current_line = \n" << current_line << endl;

			/* If this line is empty, move on to the next one */
			if (current_line.length() == 0){
				//cout << "Skipping this line as it's blank." << endl;
				continue;
			}
			/* If the line begins with '#', we assume it's a comment and move on to the next one */
			else if (current_line[0] == '#'){
				//cout << "Skipping this line as it's a comment." << endl;
				continue;
			}
			/* Check if this line begins a new category */
			else if (current_line[0] == '['){
				ind = current_line.find(']');
				category = current_line.substr(1, ind - 1);
				// cout << "category is [" << category << "]" << endl;
			}
			/* Otherwise, we consider this line to specify an option. We check for an equals sign and let everything before it (excluding any trailing whitespace) be the option */
			else {
				/* First, we serach for the equals sign */
				ind = current_line.find('=');

				/* We assume that everything that comes before this equals sign is the option, possibly with some whitespace at the end that we'll trim... */
				option = current_line.substr(0, ind - 1);

				// cout << "option = " << option << endl;
				trimRWSpace(option);

				// cout << "option = " << option << endl;

				/* Now we store the category and option */
				fileOpts.push_back(category + '.' + option);

				/* If the option contains more than one character, consider it a long option */
				fileIsLong.push_back(option.length() > 1);

				/* We assume that everything that comes after the equals sign are the arugments for the option, separated by whitespace characters */
				arguments = current_line.substr(ind+1, current_line.length() - ind);
				trimLWSpace(arguments);

				temp_vec.resize(0);

				while (arguments.length()){
					argument = splitAtFirstWS(arguments);
					temp_vec.push_back(argument);
				}

				fileArgs.push_back(temp_vec);

				fileNumArgs.push_back(temp_vec.size());
			}
		}
	}

	void InpArgsClass::printFileOpts(){
		cout << "Options/arguments provided from the input file:\n";
		cout << "\tOPTION\t\tARGUMENTS\n";
		for (unsigned int it = 0; it < fileArgs.size(); ++it){
			// cout << "optInds[" << it << "] = " << optInds[it] << " | " << fileNumArgs[it] << " arguments\n";
			cout << "\t" << fileOpts[it] << "\n\t\t\t";
			for (vector<string>::iterator it2 = fileArgs[it].begin(); it2 < fileArgs[it].end(); ++it2){
				cout << *it2;
				if (it2 < fileArgs[it].end() - 1){
					cout << ", ";
				}
			}
			cout << endl;
		}
	}

}