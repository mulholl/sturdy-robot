#include <iostream>
#include "FileMatrixFunctions.hpp"
#include "FileExceptions.hpp"
#include "InpArgs.hpp"

using namespace std;

int main(int argc, char *argv[]){

	vector< vector<int> > M;
	vector<string> args;

	argVector(argc, argv, args);

	for (vector<string>::iterator it = args.begin(); it < args.end(); ++it){
		cout << distance(args.begin(), it) << ": " << *it << endl;
	}

	cout << "Calling readMatrixFromFile(\"test.txt\", M)" << endl;

	try {
		readMatrixFromFile("test.txt", M);
	}
	catch (struct fexc::OpenFailed) {
		cout << "Caught an OpenFailed exception" << endl;
	}

	cout << "Quitting" << endl;

	return 0;
}