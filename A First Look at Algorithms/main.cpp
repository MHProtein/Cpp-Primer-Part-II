#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <deque>
#include <numeric>
#include <iterator>
#include <array>
#include <list>

auto practice1()
{
	std::deque<double> deq{ 1.23,243.43,43.34,23.231232,345.345 };
	std::cout << std::accumulate(deq.cbegin(), deq.cend(), 0.0) << std::endl;
}

int main()
{
	//10.2.1 Read-Only Algorithms
	//accumulate//ÇóºÍ in numeric
	std::vector<int> v{ 1,2,3,4,5,6,7,8,9 };
	auto sum = std::accumulate(v.cbegin(), v.cend(), 0);
	//the type of the third parameter of accumulate decides which plus operator to use and the return type of accumulate

	//auto sum = std::accumulate(v.cbegin(), v.cend(), std::string(" "));
	//error: if we pass a string literal, the type of the object to hold the sum will become const char* , and that type doesn't offer a operator+

	std::cout << sum << std::endl;

	//Algorithms that Operate two Sequences
	//equal
	//to use this, there's a significant assumption that the lengths of the two sequences to compare equal
	std::vector<double> v2{ 1,2,3,4,5,6,7,8,9 };
	auto is_equal = std::equal(v.cbegin(), v.cend(), v2.cbegin());
	//true if every element in 2 sequences equals respectively

	practice1();

	//10.2.2 Algorithms that Write Container Elements
	//When using an algorithm to assign, make sure that the sequence into which the algorithm
	//writes is at least as the number of elements we ask the algorithm to write.
	//algorithms can't change the size of a container since it can't perform container operations
	//fill
	std::vector<int> vec(100);
	std::fill(vec.begin(), vec.end(), 10);

	//Algorithms don't Check Write Operations
	std::fill_n(vec.begin(), vec.size(), 100);
	vec.resize(0);
	vec.shrink_to_fit();
	std::cout << vec.capacity() << std::endl;//0
	//std::fill_n(vec.begin(), 10, 1000); //error: Undefined, there's no element in vec

	//Introduce back_inserter  //defined in iterator
	//insert iterator ensure that an algorithm has enough elements to hold the output
	//When we assign through an insert iterator, a new element equal to the right-hand value is added to the container
	auto insertIte = std::back_inserter(vec);
	*insertIte = 42; //vec now has one element with value 42
	//We can also use back_inserter to create an iterator to use as the destination of an algorithm
	std::vector<int> vec2;
	std::fill_n(std::back_inserter(vec2), 10, 0);

	//Copy Algorithms
	std::array<int, 10> arr1{ 1,2,3,4,5,6,7,8,9 };
	std::array<int, arr1.size()> arr2;
	auto it = std::copy(arr1.cbegin(), arr1.cend(), arr2.begin());
	//It's essential to ensure the destination passed into the function be at least as large as the input range
	//the value returned by copy is the incremented value of its destination iterator that is it denotes just past the element copied

	//replace
	std::replace(vec2.begin(), vec2.end(), 0, 32);

	//if we don't wanna change the value and need a copy?
	std::vector<int> vec3;
	std::replace_copy(vec2.cbegin(), vec2.cend(), std::back_inserter(vec3), 32, 100);

	//10.2.3 Algorithms that Reorder Container Elements
	//Eliminate Duplicates
	std::string s("the quick red fox jumps over the slow red turtle");
	std::vector<std::string> sentence;
	std::istringstream strm(s);
	std::string temp;
	while(strm>>temp)
	{
		sentence.push_back(temp);
	}
	std::cout << sentence.size() << std::endl;
	std::sort(sentence.begin(), sentence.end());  //sort words alphabetically so we can find the duplicates
	//unique reorders the input range so that each word appears once in the front position of the range and returns an iterator one past the unique range
	auto end_unique = std::unique(sentence.begin(), sentence.end()); 
	sentence.erase(end_unique, sentence.end());
	for (const auto & word : sentence)
	{
		std::cout << word << std::endl;
	}

	//The size of sentence isn't changed, but the order of the elements is changed. The duplicates aren't removed, they are just overwritten which makes sure the unique elements to appear at the front of the sequence
	//The elements beyond the one-past-the-last-unique-element point still exist, but their values are unknown to us.


}