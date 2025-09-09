/*
 * 2. DELIGATED CONSTRUCTORS:
 *
 * The following code implements the idea of deligated constructors first introfuced in C++11
 * This allows an overloaded constructor to avoid code duplication and by deligating some
 * 	of the work to another constructor of the same class 
 */
#include <iostream>
#include <cassert>
#include <sstream>

class Foo
{
	public:
	Foo()
	{
		a = b = c = 1;
	}
	// By extending the default constructor, we delicate part of the work that needs to be done 
	Foo(int c) : Foo()
	{
		this->c = c;
	}

	private:
	int a;
	int b;
	int c;

	friend std::ostream& operator<<(std::ostream& o, const Foo& f)
	{
		o << "(" << f.a << "," << f.b << "," << f.c <<")\n";
		return o;
	}
};

int main()
{
	std::cout << "===== Test : Deligated constructor was called =====\n";
	Foo default_constr;
	
	std::ostringstream oss;
	oss << default_constr;
	assert(oss.str() == "(1,1,1)\n");

	//Resetting ostring stream
	oss.str(std::string());

	Foo deligated_constr(3);
	oss << deligated_constr;
	assert(oss.str() == "(1,1,3)\n");

	return 0;
}
