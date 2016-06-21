#ifndef INP_ARGS_HPP
#define INP_ARGS_HPP

#include <string>
#include <vector>
#include <tuple>
#include "ValidArgs.hpp"
#include "InpArgsClass.hpp"

// template <typename T>
// bool checkInpArg(std::string &s1, T val, int argc, char *argv[]){

// }

bool argVector(int , char **, std::vector<std::string> &);

#endif