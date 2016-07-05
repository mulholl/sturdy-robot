#ifndef __STDC_IEC_559__
#error "This program requires IEEE 754 floating point support - this can be disabled by comment out the check for __STD_IEC_559__ in the main .cpp file" 
#endif

#include <iostream>
#include <typeinfo>
#include "InpArgs.hpp"

using namespace std;

int main(int argc, char *argv[]){

	unsigned int i = 0;

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

	IA.addOpt('h', "help", "Print this help message", test1);

	IA.addOpt('f', "file", "List of files", test2.numArgs(0,3).defaultValue("input.txt"));

	IA.addOpt('s', "switch", "Boolean switch option test", test3);

	if (IA.Used('h') || IA.Used("help")){
		cout << "Printing a list of valid options\n";
		cout << IA.listArgs() << endl;
	}

	/* Check for any user-specified options that are not recognized */
	try {
		IA.UnrecognizedOpts();
	}
	catch (inpargs::UnrecOpts UO){
		cout << UO.what();
	}
	
	cout << "Quitting" << endl;

	return 0;
}