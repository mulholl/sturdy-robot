// #ifndef __STDC_IEC_559__
// #error "This program requires IEEE 754 floating point support - this can be disabled by commenting out the check for __STD_IEC_559__ in the main .cpp file" 
// #endif

#include <iostream>
#include <typeinfo>
#include "InpOpts.hpp"

using namespace std;

int main(int argc, char *argv[]){

	unsigned int i = 0;

	vector< vector<int> > M;
	vector<string> args;

	inpopts::InpOptsClass IA(argc, argv);

	vector<string> vals;
	int testint = 10;
	bool testbool = true;

	cout << "The InpOpts version is " << inpopts::Version() << endl;

	// cout << "typeid(vals).name() = " << typeid(vals).name() << endl;
	// cout << "typeid(&vals).name() = " << typeid(&vals).name() << endl;

	vals.push_back("Hi\n");

	inpopts::value<int> test1 = inpopts::value<int>(testint);
	inpopts::value<string> test2 = inpopts::value<string>(vals);
	inpopts::value<bool> test3 = inpopts::value<bool>(testbool);

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
	catch (inpopts::UnrecOpts UO){
		cout << UO.what();
	}
	
	cout << "Quitting" << endl;

	return 0;
}