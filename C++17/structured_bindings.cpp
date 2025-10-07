/*
 * 3. STRUCTURED BINDINGS:
 *
 * Structured bindings allow us to unpack tuples, pairs, arrays and other packed structures
 *      directly into variables to improve code readability.
 * They essentially perform tuple decomposition and let us bind the contained values into 
 *      local variables. 
 */
#include <iostream>
#include <tuple>
#include <cassert>

struct Point
{
	int x;
	int y;
	int z;
};

std::tuple<int, double, std::string> getValues()
{
	return {1, 3.14, "something"};
}

int main()
{
	std::cout << "===== Test: Structured Bindings with tuple =====\n";
	// This is the strucuted binding part where the lhs is a list of variable names
	// and the rhs is the container (in this case a tuple)
	auto [num, pi, str] = getValues(); 

	assert(num == 1);
	assert(pi == 3.14);
	assert(str == "something");


	Point p{1, 2, 3};
	// here we decompose a Point object into separate variables
	auto [a, b, c] = p;	
	assert(a == 1);
	assert(b == 2);
	assert(c == 3);

	return 0;
}
