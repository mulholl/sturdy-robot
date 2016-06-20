#ifndef FILE_MATRIX_FUNCTIONS_HPP
#define FILE_MATRIX_FUNCTIONS_HPP

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <exception>
#include "FileExceptions.hpp"

template <typename T, typename A>
int readMatrixFromFile(std::string s, std::vector< std::vector<T, A> > &M){
	std::ifstream inp(s, std::ios::in);

	if (inp.is_open()){
		std::cout << "OPENED" << std::endl;
		return 0;
	}
	else {		
		std::cout << "FAILED to open" << std::endl;

		// throw my_exc{};
		throw fexc::OpenFailed{};
	}

	return -1;
}

#endif