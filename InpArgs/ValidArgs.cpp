#include "ValidArgs.hpp"

using namespace std;

void ValidArgs::addArg(char c, string s, string h){
	tuple<char, string, string> tup (c, s, h);
	argList.push_back(tup);
}

void ValidArgs::addArg(char c, string h){
	tuple<char, string, string> tup (c, "", h);
	argList.push_back(tup);
}

void ValidArgs::addArg(string s, string h){
	tuple<char, string, string> tup ('\0', s, h);
	argList.push_back(tup);
}

bool ValidArgs::isValidArg(char c){
	if (c == '\0' || argList.size() == 0){
		return false;
	}
	else {
		for (vector< tuple<char, string, string> >::iterator it = argList.begin(); it != argList.end(); ++it){
			if (c == get<0>(*it)){
				return true;
			}
		}
	}

	return false;
}

bool ValidArgs::isValidArg(string s){
	if (s.length() == 0 || argList.size() == 0){
		return false;
	}
	else {
		for (vector< tuple<char, string, string> >::iterator it = argList.begin(); it != argList.end(); ++it){
			if (s.compare(get<1>(*it))){
				return true;
			}
		}
	}

	return false;
}

string ValidArgs::listArgs(){
	string s = "";

	for (vector< tuple<char, string, string> >::iterator it = argList.begin(); it != argList.end(); ++it){
		s = s + "  -" + get<0>(*it) + "    --" + get<1>(*it) + "        " + get<2>(*it) + "\n"; 
	}

	return s;
}

ValidArgs::ValidArgs(){
	argList.clear();
	argList.resize(0);
}