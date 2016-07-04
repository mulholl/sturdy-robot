#ifndef __STDC_IEC_559__
#error "This program requires IEEE 754 floating point support - this can be disabled by comment out the check for __STD_IEC_559__ in the main .cpp file" 
#endif

#include <iostream>
#include <typeinfo>
#include "InpArgs.hpp"

using namespace std;

int main(int argc, char *argv[]){

	vector< vector<int> > M;
	vector<string> args;

	inpargs::InpArgsClass IA(argc, argv);

	vector<string> vals;
	int testint = 10;
	bool testbool = true;

	// cout << "typeid(vals).name() = " << typeid(vals).name() << endl;
	// cout << "typeid(&vals).name() = " << typeid(&vals).name() << endl;

	vals.push_back("Hi\n");

	inpargs::value<int> test1 = inpargs::value<int>(testint);
	inpargs::value<string> test2 = inpargs::value<string>(vals);
	inpargs::value<bool> test3 = inpargs::value<bool>(testbool);

	// test2.numArgs(0, 3);

	IA.addOpt('h', "help", "Print this help message", test1);
	IA.addOpt('f', "file", "List of files", test2.numArgs(0,3).defaultValue("input.txt"));

	cout << IA.listArgs() << endl;

	// for (std::vector<std::string>::iterator it = vals.begin(); it < vals.end(); ++it){
	// 	std::cout << "Element " << std::distance(vals.begin(), it) << ": " << *it << endl;
	// }


	// int a;

	// IA.addOpt('h', "help", "Print this help message", 0, 0, a, 1);

	// cout << IA.listArgs() << endl;

	// argVector(argc, argv, args);

	// for (vector<string>::iterator it = args.begin(); it < args.end(); ++it){
	// 	cout << distance(args.begin(), it) << ": " << *it << endl;
	// }
	
	cout << "Quitting" << endl;

	return 0;
}