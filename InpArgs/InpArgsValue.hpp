#ifndef INP_ARGS_VALUE_HPP
#define INP_ARGS_VALUE_HPP

#include "InpArgsExceptions.hpp"
#include <iostream>
#include <vector>
#include <string>
// #include <cstdarg>

namespace inpargs{
	template <class T>
	class value{
		public:
			/* 1. Variables storing info. about possible values */
			T minVal; // Minimum allowed value
			T maxVal; // Maximum allowed value
			std::vector<T> valList; // Vector of allowed values
			T defVal; // Default value

			/* Boolean variables specifying whether the variables in (1) above have been specified or not */
			bool rangeSpec; // TRUE if a range of values has been specified - maxSpec and minSpec should always be TRUE if rangeSpec is TRUE
			bool maxSpec; // TRUE if a maximum value has been specified
			bool minSpec; // TRUE if a minimum value has been specified
			bool valListSpec; // TRUE if a vector of allowed values has been specified
			bool defSpec; // TRUE if a default value has been specified

			bool valVecSpec; // TRUE if we are dealing with a vector of arguments

			/* setRange(a, b) is used to set a range of possible values. It returns a reference to the current object.
			 *		If a list of values has been previously specified, it is overridden.
			 *
			 * 		rangeSpec is set to TRUE
			 * 		maxSpec is set to TRUE
			 * 		minSpec is set to TRUE
			 *		valListSpec is set to FALSE
			 */
			value& setRange(T a, T b){
				if (a < b){
					minVal = a;
					maxVal = b;
				}
				else if (b < a){
					minVal = b;
					maxVal = a; 
				}
				else {
					minVal = maxVal = a;
				}

				rangeSpec = true;
				maxSpec = true;
				minSpec = true;
				valListSpec = false;
				valList.resize(0);

				return *this;
			}

			const value& setRange(T a, T b) const {
				if (a < b){
					minVal = a;
					maxVal = b;
				}
				else if (b < a){
					minVal = b;
					maxVal = a; 
				}
				else {
					minVal = maxVal = a;
				}

				rangeSpec = true;
				maxSpec = true;
				minSpec = true;
				valListSpec = false;
				valList.resize(0);

				return *this;
			}

			/* setMax(a) is used to set a maximum value. It returns a reference to the current object.
			 *		If a range, minimum value or list of allowed values have been previously set, they are overridden
			 *
			 *		maxSpec is set to TRUE
			 *		rangeSpec is set to FALSE
			 *		minSpec is set to FALSE
			 *		valListSpec is set to FALSE
			 */
			value& setMax(T inpMaxVal){
				maxVal = inpMaxVal;
				
				rangeSpec = false;
				maxSpec = true;
				minSpec = false;
				valListSpec = false;
				valList.resize(0);

				return *this;
			}

			const value& setMax(T inpMaxVal) const {
				maxVal = inpMaxVal;
				
				rangeSpec = false;
				maxSpec = true;
				minSpec = false;
				valListSpec = false;
				valList.resize(0);

				return *this;
			}			

			/* setMin(a) is used to set a maximum value. It returns a reference to the current object.
			 *		If a range, maximum value or list of allowed values have been previously set, they are overridden
			 *
			 *		minSpec is set to TRUE
			 *		rangeSpec is set to FALSE
			 *		maxSpec is set to FALSE
			 *		valListSpec is set to FALSE
			 */			
			value& setMin(T inpMinVal){
				minVal = inpMinVal;
				
				rangeSpec = false;
				maxSpec = false;
				minSpec = true;
				valListSpec = false;
				valList.resize(0);

				return *this;
			}

			const value& setMin(T inpMinVal) const {
				minVal = inpMinVal;
				
				rangeSpec = false;
				maxSpec = false;
				minSpec = true;
				valListSpec = false;
				valList.resize(0);

				return *this;
			}			

			/* setMax(a) is used to set a maximum value. It returns a reference to the current object.
			 *		If a range, maximum or minimum value have been previously set, they are overridden
			 *
			 *		valListSpec is set to TRUE
			 *		rangeSpec is set to FALSE
			 *		maxSpec is set to FALSE
			 *		minSpec is set to FALSE
			 */			
			value& setValList(std::vector<T> inpValList){
				valList = inpValList;

				rangeSpec = false;
				maxSpec = false;
				minSpec = false;
				valListSpec = true;

				return *this;
			}

			const value& setValList(std::vector<T> inpValList) const {
				valList = inpValList;

				rangeSpec = false;
				maxSpec = false;
				minSpec = false;
				valListSpec = true;

				return *this;
			}			

			/* defaultValue(a) is used to set a default value. It returns a reference to the current object.
			 */
			value& defaultValue(T inpDefVal){
				defVal = inpDefVal;

				defSpec = true;
			}

			const value& defaultValue(T inpDefVal) const {
				defVal = inpDefVal;

				defSpec = true;
			}			

			// void printVectorContents(){
			// 	std::vector<T>::iterator it2;

			// 	it2 = 
			// }

			/* Constructor for the value class */
			value(T &inpVarRef) : varRef(inpVarRef), vecVarRef(emptyVector) {

				// vecVarRef = &(std::vector<T>());
				
				valVecSpec = false;

				rangeSpec = false;
				maxSpec = false;
				minSpec = false;
				valListSpec = false;
				valList.resize(0);

				defSpec = false;
			}
			/* Constructor for the value class where a vector of inputs is expected */
			value(typename std::vector<T> &inpVecVarRef) : vecVarRef(inpVecVarRef), varRef(emptyT) {
				// it = inpVecVarRef.begin();

				// vecVarRef = inpVecVarRef;


				vecVarRef.push_back("there!\n");

				valVecSpec = true;

				rangeSpec = false;
				maxSpec = false;
				minSpec = false;
				valListSpec = false;
				valList.resize(0);

				defSpec = false;
			}
		private:
			T& varRef;
			std::vector<T>& vecVarRef;
			std::vector<T> emptyVector;
			T emptyT;
			// const typename std::vector<T>::iterator it;
	};
}

#endif