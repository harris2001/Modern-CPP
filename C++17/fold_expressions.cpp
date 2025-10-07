/* 
 * 4. FOLD EXPRESSIONS
 *    
 * Fold expressions provide the tools to apply BINARY OPERATORS to all elements in a
 *      parameter pack without having of recursive template unpacking or intitializer tricks
 *
 * There are 4 forms of a fold expression:
 *      (... OP pack)             // Unary right fold  =>  ((arg1 [+] arg2) [+] ...)
 *      (pack OP ...)             // Unary left fold   =>  (... [+] (arg2 [+] arg3))
 *      (init OP ... OP pack)     // Binary left fold  => ((init [+] arg1) [+] arg2) [+] ...) 
 *      (pack OP ... OP init)     // Binary right fold =>  (... [+] (arg2 [+] (arg3 [+] init)))  
 */
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <cassert>
#include <sstream>

//(size_t... I) is a std::integer_sequence whose values are specified by a non-type template
template<typename TupleT, size_t... IdxT>
std::string print(const TupleT& tupl, std::index_sequence<IdxT...>){
	//This experssion (..., operator) folds the tuple by applying operator to
	// each of its elements going from left to right
	std::ostringstream oss;
	oss << "(";
	(..., (oss << (IdxT == 0 ? "" : ", ") << std::get<IdxT>(tupl)));
	oss << ")\n";
	return oss.str();
}

// This is a non-type template that takes a tuple with multiple arguments of some type T
template<typename... T>
std::string printTuple(const std::tuple<T...>& tupl){
	// std::make_integer_sequence creates a sequence of integers of size equal to the number of arguments of T 
	return print(tupl, std::make_index_sequence<sizeof...(T)>());
}	

int main(){
	std::cout << "===== Test : Fold expressions applied to tuple printing =====\n";

	std::vector<std::tuple<std::string, std::string, std::string>> my_list = {
		{"5","3","1"},
		{"1","3","2"},
		{"3","5","A"},
		{"6","4","5"}
	};

	std::vector<std::string> expected_output = {"(5, 3, 1)\n",
						    "(1, 3, 2)\n",
						    "(3, 5, A)\n",
						    "(6, 4, 5)\n"};
	for(size_t i = 0; i < my_list.size(); i++)
	{
		const auto& tupl_ = my_list[i];
		std::string result = printTuple(tupl_);  
		if (result != expected_output[i]) 
		{
			std::cerr << "Failed on tuple " << i << ": got " << result 
				  << " expected " << expected_output[i] << "\n";
			assert(false);
		}
		// In C++20 use std::fmt as follows:
		//      std::cout << std::fmt("{}", my_list[i]) << std::endl;
		// In C++23 use std::print
		//      print("{}", my_list[i]); 
	}
	std::cout << "All tuples verified successfully\n";
	return 0;
}

