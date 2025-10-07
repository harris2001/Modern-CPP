#include <iostream>
#include <vector>
#include <set>
#include <string>
//#include <print> // Needs to be included if we are using C++23 print function

//size_t... I is a std::integer_sequence whose values are specified by a non-type template
template<typename TupleT, size_t... IdxT>
void print(const TupleT& tupl, std::index_sequence<IdxT...>){
	//This experssion (..., operator) folds the tuple by applying operator to
	// each of its elements going from left to right
	std::cout << "(";
	(..., (std::cout << (IdxT == 0 ? "" : ", ") << std::get<IdxT>(tupl)));
	std::cout << ")\n";
}

// This is a non-type template that takes a tuple with multiple arguments of some type T
template<typename... T>
void printTuple(const std::tuple<T...>& tupl){
	//std::make_integer_sequence creates a sequence of integers of size equal to the number of arguments of T 
	print(tupl, std::make_index_sequence<sizeof...(T)>());
}	

int main(){
	std::vector<std::tuple<std::string>> my_list = {("5","3","1"),("1","3","2"),("3","5","A"),("6","4","5")};

	auto a = std::make_index_sequence<4>();
	for(auto tupl_ : my_list){
		//std::cout << std::fmt("{}", my_list[i]) << std::endl; //For C++20 use format
		//print("{}", my_list[i]); // For C++23 use print
		printTuple(tupl_);
	}
	return 0;
}
