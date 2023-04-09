#include <memory>
#include <iterator>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

size_t get_size()
{
	srand(static_cast<size_t>(time(0)));
	return rand() % 10;
}

auto practice(const std::string& s1, const std::string& s2)
{
	const char* s3 = "hi";
	const char* s4 = "there";
	auto len = strlen(s3) + strlen(s4) + 1;
	char* s = new char[len]();
	strcat_s(s, len, s3);
	strcat_s(s, len, s4);
	delete[] s;
	s = nullptr;

	char* ss = new char[s1.size() + s2.size() + 1]();
	strcat_s(ss, (s1 + s2).size() + 1, (s1 + s2).c_str());
	delete[] ss;
	ss = nullptr;

	return s;
}

auto practice2()
{
	std::string temp;
	std::cin >> temp;
	char* s = new char[temp.size() + 1]();
	strcat_s(s, temp.size() + 1, temp.c_str());
}

//Still, try to use a vector

int main()
{
	//12.2.1 new and Arrays 
	size_t n = 123;
	int* pia = new int[n]; //pia points to the first of these ints, the ints are not initialized

	//Allocating an Array Yields a pointer to the Element Type
	//When we use new to allocate an array, we do not get an object with an array type.
	//the fact that we are allocating an array is even invisible; there's no [num].
	//Even so, new returns a pointer to the element type
	//Because the allocated memory does not have an array type, we cannot call begin and end on a dynamic array.
	//We also cannot use a range-for function

	//Initializing an Array of Dynamic Allocated Objects
	int* pia2 = new int[10](); //block of ten ints value initialized to o
	std::string* pas = new std::string[10];//block of ten empty strings
	std::string* pas2 = new std::string[10](); //block of ten empty strings
	int* pis3 = new int[10] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	std::string* psa3 = new std::string[10]{ "a","an","the",std::string(3,'x') };
	//If there are more elements than the initializers, the remaining elements are value initialized.
	//If there more initializers than the given size, then the new expression fails and no storage is allocated.
	//In this case, new throws an exception of type bad_array_new_length. Like bad_alloc, this type defines in new header

	//It is Legal to Dynamically Allocate an Empty Array
	int* p = new int[get_size()];
	//The code will work fine even if get_size() returns 0
	//The pointer behaves like a off-the-end pointer

	//Freeing Dynamic Arrays
	delete[] p;
	//This destroys the elements in the array to which p points and frees the corresponding memory. Elements are destroyed in reverse order.

	//Smart Pointers and Dynamic Arrays
	//The library provides a version of unique_ptr that can manage arrays allocated by new,
	std::unique_ptr<int[]> up(std::make_unique<int[]>(10));
	up.release(); //automatically uses delete[] to destroy its pointer
	//When a unique_ptr points to an array, we cannot use the dot and arrow member access operations. After all, the unique_ptr points to an array, not an object so these operators would be
	//meaningless
	//When a unique_ptr points to an array, we can use the subscript operator to access to access the elements in the array:
	for (size_t i = 0; i != 10; ++i)
		up[i] = i;
	//If we wanna use a shared_ptr to manage an array, we gotta provide a deleter
	std::shared_ptr<int> sp(new int[10], [](int* p) {delete[] p; });
	sp.reset(); //Here, we provide a lambda that uses delete[] as the deleter
	for (size_t i = 0; i != 10; ++i)
		*(sp.get() + i) = i; //use get to get a built-in pointer
	//There is no subscript operator for shared_ptrs, and the smart pointer types do not support pointer arithmetic. As a result, to access the elements in the array, we must use get to obtain a
	//built-in pointer.
	
	//12.2.2 The allocator Class
	//new combines allocating memory with constructing objects in that memory. Similarly, delete combines destruction with deallocation.
	//coupling allocation and construction can be wasteful.
	//std::string *const p = new std::string[n];
	//The new expression allocates and initializes n strings. However, we might not need n strings. We could create objects that are never used.
	//Moreover, for those objects we do use, we immediately assign new values over the previously initialized strings. The elements that are used are written twice.

	//The allocator class lets use separate allocation from construction. It provides type-aware allocation of raw, unconstructed, memory.
	std::allocator<std::string> alloc; //object that can allocate strings
	auto const pp = alloc.allocate(5); //allocate n unconstructed strings
	//a.allocate(n)  //Allocates raw, unconstructed memory to hold n objects of type T
	//a.deallocate(p, n)  //Deallocates memory that held n objects of type T starting at the address in the T* pointer p; p must be a pointer previously returned by allocate, and n must be the
									//size requested when p was created. The user must run destroy on any objects that were constructed in this memory before calling deallocate.
	//a.construct(p, args) //p must be a pointer to type T that points to raw memory; args are passed to a constructor for type T, which is used to construct an object in the memory pointed to by p.
	//a. destroy(p)  //Runs the destructor on the object pointed to by the T* pointer p.

	//allocators Allocate Unconstructed Memory
	auto q = pp; //q will point to one past the last constructed element
	alloc.construct(q++); //*q is the empty string
	alloc.construct(q++, "hey"); //*q is ~~
	alloc.construct(q++, 10, 's');//*q is ~~
	std::cout << *pp << std::endl;
	std::cout << *q << std::endl; //disaster: q points to unconstructed memory
	//When we're finished using the objects, we must destroy the elements we constructed.
	while (q != pp)
	{
		alloc.destroy(--q);
	}
	//Once the elements have been destroyed, we can either reuse the memory to hold other strings or return the memory to the system. We free the memory by calling deallocate:
	alloc.deallocate(pp, 5);

	//Algorithms to Copy and Fill Uninitialized Memory
	std::vector<int> vi{ 1,2,3,4,5,6,7,8,9,10 };
	auto pi = alloc.allocate(vi.size() * 2);
	std::uninitialized_copy(vi.cbegin(), vi.cend(), pi); //Copies elements from the input range denoted by iterators into unconstructed, raw memory denoted by pi. The memory denoted
	std::uninitialized_copy_n(vi.cbegin(), vi.size(), pi); //by pi must have enough size to hold a copy of the elements in the input range
	std::uninitialized_fill(pi, pi + vi.size(), 2); // Constructs objects in the range of raw memory denoted by iterators as a copy of 2
	std::uninitialized_fill_n(pi, vi.size(), 10); //


}