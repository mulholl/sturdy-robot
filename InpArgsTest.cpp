#include <iostream>
#include <typeinfo>
#include "InpArgs.hpp"

using namespace std;

int main(int argc, char *argv[]){

	vector< vector<int> > M;
	vector<string> args;

	inpargs::InpArgsClass IA("input.txt");

	vector<string> vals;
	int testint = 10;

	// cout << "typeid(vals).name() = " << typeid(vals).name() << endl;
	// cout << "typeid(&vals).name() = " << typeid(&vals).name() << endl;

	vals.push_back("Hi\n");

	inpargs::value<int> test1 = inpargs::value<int>(testint);
	inpargs::value<string> test2 = inpargs::value<string>(vals);

	for (std::vector<std::string>::iterator it = vals.begin(); it < vals.end(); ++it){
		std::cout << "Element " << std::distance(vals.begin(), it) << ": " << *it << endl;
	}


	// int a;

	// IA.addArg('h', "help", "Print this help message", 0, 0, a, 1);

	// cout << IA.listArgs() << endl;

	// argVector(argc, argv, args);

	// for (vector<string>::iterator it = args.begin(); it < args.end(); ++it){
	// 	cout << distance(args.begin(), it) << ": " << *it << endl;
	// }
	
	cout << "Quitting" << endl;

	return 0;
}