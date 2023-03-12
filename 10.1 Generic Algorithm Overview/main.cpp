#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <list>

//"generic" because they operate on elements of differing type and across multiple container types -- not only library types such as vector or list, but also the built-in array type
//--and, as we shall see, over other kinds of sequences as well.
//"algorithm" because they implement common classical algorithms such as sorting and searching.

auto practice1(std::vector<int>& v, int value)
{
	return std::count(v.cbegin(), v.cend(), value);
}

auto practice2(std::list<std::string>& l,std::string& value)
{
	return std::count(l.cbegin(), l.cend(), value);
}

int main()
{
	//In general, the algorithms do not work directly on a container. Instead, they operate by traversing a range of elements bounded by two iterators.
	//Typically, as the algorithm traverses the range, it does something with each element.

	//find
	std::vector<int> v{ 1,2,3,4,5,6,7,8,9 };
	auto result = std::find(v.cbegin(), v.cend(), 5);
	//it works in built-in array as well

	//How the Algorithms Work
	//still find:
	//1. It accesses the first element in the sequence
	//2. It compares that element to the value we want
	//3. If this element matches the one we want, find returns a value that identifies this element
	//4.Otherwise, find advances to the next element and repeats steps 2 and 3
	//5. find must stop when it has reached the end of the sequence
	//6.If find gets to the end of the sequence, it needs to return a value indicating that the element was not found.
	//This value and the one returned from step3 must have compatible//ºÊ»› types

	//these steps don't depend on the type of the container, we just need its iterators
	//If find failed to find a value, it returns a off-the-end iterator to indicate no such value in the container
	//But it does depends on element-type operations
	//most of the algorithms use one or more operations on the element type.

	//Algorithms Never Execute Container Operations
	//They never change the size of the underlying container. They may change the values of the elements stored in the container, and they may move elements around within the container.
	//They do not, however, ever add or remove elements directly
}