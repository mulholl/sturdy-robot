#include "InpArgs.hpp"

using namespace std;

bool argVector(int argc, char **argv, vector<string> &vec){
	vec.clear();
	vec.reserve(argc-1);

	if (argc == 1){
		return false;
	}
	else {
		for (unsigned int i = 0; i < argc - 1; ++i){
			vec.push_back(argv[i + 1]);
		}
		return true;
	}
	return true;
}