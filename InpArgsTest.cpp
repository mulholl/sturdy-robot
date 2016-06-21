#include <iostream>
#include "InpArgs.hpp"

using namespace std;

int main(int argc, char *argv[]){

	vector< vector<int> > M;
	vector<string> args;

	InpArgsClass IA(argc, argv);

	IA.addArg('h', "help", "Print this help message");

	cout << IA.listArgs() << endl;

	// argVector(argc, argv, args);

	// for (vector<string>::iterator it = args.begin(); it < args.end(); ++it){
	// 	cout << distance(args.begin(), it) << ": " << *it << endl;
	// }
	
	cout << "Quitting" << endl;

	return 0;
}