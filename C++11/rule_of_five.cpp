/*
 * 1. THE RULE OF FIVE:
 *
 * The following code implements the Rule of Five introduced in C++11
 * The class Arr manaages a dynamic array of integers and demonstrates how to properly
 * 	handle resourse ownership
 * It defines the following:
 * 	- Destructor: for releasing the allocated memory
 *	- Copy constructor: performs deep copy of the array
 *	- Copy assignment operator: cleans up old memory and deep copies
 *	- Move constructor: transfers ownership from a temporary rvalue to a new object
 *	- Move assignment operator: transfers ownwership and prevents a double delete  
 *
 * In modern C++ the rule of five states that if a class defines any one of these member
 * functions (destructor, copy/move constructor, copy/move assignment), it needs to define
 * ALL of them to manage resources safely and consistently.
 */
#include <iostream>
#include <cassert>

class Arr
{
	public:
	Arr(int s)
	{
		std::cout << "Normal constructor executing" <<std::endl;
		size_ = s;
		arr_ = new int[s] {0};
	}

	// Copy constructor
	// Arr f(g);
	// Arr f = g; 
	Arr(const Arr& rhs)
	{
		std::cout << "Copy constructor executes" << std::endl;
		size_ = rhs.size_;
		arr_ = new int[size_];
	   
		for(int i = 0; i < size_; i++)
			arr_[i] = rhs.arr_[i];	
	}

	// Move constructor
	// For dealing with r-values
	Arr(Arr&& rhs) noexcept //<- NECESSARY because a move constructor is not allowed to throw exceptions
	{
		std::cout << "R-value detected => move constructor executes" << std::endl;
		size_ = rhs.size_;
		arr_ = rhs.arr_;
		// The r-value gets out of scope as soon as it assigns its contents to the lvalue
		// We need to prevent its destructor from destroying arr_ since it's now binded to rhs.arr_
		rhs.arr_ = nullptr;
	}	

	// Destructor takes care of clearing the memory
	~Arr()
	{
		if(arr_)
			delete[] arr_;	
	}

	int& operator[](int i){ return arr_[i]; }
	int len(){ return size_; }
	
	// Needs to be defined as friend to access rhs's size_ and arr_ members	
	friend std::ostream& operator<<(std::ostream& o, const Arr& rhs)
	{
		for(int i = 0; i < rhs.size_; i++)
			o << rhs.arr_[i] <<" ";

		return o;
	}
	
	// arr_1 + arr_2 cause an r-value to be created
	Arr operator+(const Arr& rhs)
	{
		Arr temp(size_ + rhs.size_);
		
		int i = 0;
		for (; i < size_; i++)
			temp[i] = arr_[i];
			
		for (int j=0; j<rhs.size_; i++, j++)
			temp[i] = rhs.arr_[j];	

		return temp;
	}

	// Assign operator 
	// arr_1 = arr_2
	Arr& operator=(const Arr& rhs)
	{
		// Check if we are assigning the same object to itself by checking their memory address 
		if(this == &rhs)
			return *this;

		// Delete current arr_ay if it exists
		if(arr_)	
			delete[] arr_;
	
		// Need to copy all elements because assigning rhs.arr_ to arr_ will cause a double delete
		size_ = rhs.size_;
		arr_ = new int[size_];
		for(int i = 0; i < rhs.size_; i++)
			arr_[i] = rhs.arr_[i];

		return *this;
	}
	
	// Move assignment operator
	Arr& operator=(Arr&& rhs)
	{
		std::cout << "R-value detected => move assignment executes" << std::endl;
		size_ = rhs.size_;
		arr_ = rhs.arr_;
		rhs.arr_ = nullptr;

		return *this;
	}

	private:
	int* arr_;
	int size_;	
};

int main()
{
	std::cout << "===== Test 1: Normal constructor =====\n";
	Arr arr1(5);
	assert(arr1.len() == 5);

	std::cout << "===== Test 2: operator[] and len() =====\n";
	for (int i = 0; i < arr1.len(); i++)
		arr1[i] = i * 2;
	for (int i = 0; i < arr1.len(); i++)
		assert(arr1[i] == i * 2);

	std::cout << "===== Test 3: Copy constructor =====\n";
	Arr arr2(arr1); // copy constructor
	assert(arr2.len() == arr1.len());
	for (int i = 0; i < arr2.len(); i++)
		assert(arr2[i] == arr1[i]);

	std::cout << "===== Test 4: Assignment operator =====\n";
	Arr arr3(3);
	arr3 = arr1; // copy assignment
	assert(arr3.len() == arr1.len());
	for (int i = 0; i < arr3.len(); i++)
		assert(arr3[i] == arr1[i]);

	std::cout << "===== Test 5: operator+ (move constructor invoked) =====\n";
	Arr arr4 = arr1 + arr2;
	assert(arr4.len() == arr1.len() + arr2.len());
	for (int i = 0; i < arr1.len(); i++)
		assert(arr4[i] == arr1[i]);
	for (int i = 0; i < arr2.len(); i++)
		assert(arr4[i + arr1.len()] == arr2[i]);

	// arr_4 + arr_3 creates a TEMPORARY r-value (i.e. an unnamed memory location)
	// Therefore the move constructor and assignment operator will be executed
	std::cout << "===== Test 6: Move assignment =====\n";
	Arr arr5(2);
	arr5 = arr4 + arr3; // move assignment
	assert(arr5.len() == arr4.len() + arr3.len());

	std::cout << "===== Test 7: Move constructor =====\n";
	Arr arr6 = Arr(arr1 + arr2); // temporary r-value triggers move constructor
	// For the above to call the move constructor we need to use -std=c++11 -fno-elide-constructors
	// OR change the above line to Arr(std::move(arr1 + arr2)
	// This is because copy elision is mandatory in C++17 and optionally before
	assert(arr4.len() == arr1.len() + arr2.len());
	for (int i = 0; i < arr1.len(); i++)
		assert(arr6[i] == arr1[i]);
	for (int i = 0; i < arr2.len(); i++)
		assert(arr6[i + arr1.len()] == arr2[i]);

	std::cout << "All tests passed successfully!\n";

	return 0;
}
