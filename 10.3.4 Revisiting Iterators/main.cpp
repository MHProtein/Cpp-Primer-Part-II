#include <iostream>
#include <vector>
#include <list>
#include <forward_list>
#include <deque>
#include <stack>
#include <queue>
#include <iterator>
#include <numeric>
#include <functional>
#include <sstream>
#include <istream>
#include <ostream>
#include "Sales_data.h"

void practice1()
{
	/*In addition to unique (§ 10.2.3, p. 384), the library defines function named unique_copy that takes a third iterator
	 *denoting a destination into which to copy the unique elements. Write a program that uses unique_copy to copy the unique
	 *elements from a vector into an initially empty list
	*/

	std::istringstream strm("the quick red fox jumps over the slow red turtle");
	std::vector<std::string> words;
	std::vector<std::string> result;
	std::string temp;
	while (strm >> temp)
		words.emplace_back(temp);
	std::sort(words.begin(), words.end());
	std::stable_sort(words.begin(), words.end(), [](const std::string& s1, const std::string& s2)->auto {return s1.size() < s2.size(); });
	for (const auto& word : words)
	{
		std::cout << word << " ";
	}
	std::cout << std::endl;
	std::unique_copy(words.cbegin(), words.cend(), std::back_inserter(result));
	for (const auto & word : result)
	{
		std::cout << word << " ";
	}
	std::cout << std::endl;

}

void practice2()
{
	/*
	 *  Copy a vector that holds the values from 1 to 9 inclusive, into three other containers. Use an inserter,
	 *  a back_inserter, and a front_inserter, respectivly to add elements to these containers. Predict how the output
	 *  sequence varies by the kind of inserter and verify your predictions by running your programs.
	 */
	std::vector<int> v{ 1,2,3,4,5,6,7,8,9 };
	std::list<int> lst;
	std::deque<int> deq;
	std::forward_list<int> flst;
	std::copy(v.cbegin(), v.cend(), std::back_inserter(lst));
	std::copy(v.cbegin(), v.cend(), std::front_inserter(flst));
	std::copy(v.cbegin(), v.cend(), std::inserter(deq, deq.begin()));

	for (const auto value : lst)
	{
		std::cout << value << " ";
	}
	std::cout << std::endl;

	for (const auto value : flst)
	{
		std::cout << value << " ";
	}
	std::cout << std::endl;

	for (const auto value : deq)
	{
		std::cout << value << " ";
	}
	std::cout << std::endl;

}

int main()
{

	std::vector<int> v{ 1,2,3,4,5 };

	//10.4.1 Insert Iterator
	//These iterators are bound to a container and can be used to insert elements into the container
	//An inserter is an iterator adaptor that takes a container and yields an iterator that adds elements to the specified container. When we assign a value through an insert iterator
	//the iterator calls a container operation to add an element at a specified position in the given container.

	//Insert Operations
	std::back_insert_iterator<std::vector<int>> it = std::back_inserter(v);
	it = 20;//Inserts the value 20 at the current position denoted by it. Depending on the kind of insert iterator, and assuming the container is the container to which it is bound, calls
	//v.push_back(20), v.push_front(20), or v.insert(20, p), where p is the iterator position given to the inserter.
	*it; ++it; it++; //These operations exist but do nothing to is. Each operator returns it.

	std::list<int> l{ 1,2,3,4,5 };
	auto bi = std::back_inserter(l); //back_inserter creates an iterator that uses push_back
	auto fi = std::front_inserter(l); //front_inserter creates an iterator that uses push_front
	auto in = std::inserter(l, l.begin()); //inserter creates an iterator that uses insert. This function takes a second argument, which must be an iterator into the given container.
	//Elements are inserted ahead of the element denoted by the given iterator.
	//When we call inserter, we get an iterator(c, iter) that, when used successively, inserts elements ahead of the elements originally denoted by iter.
	in = 23;
	//behaves just like.
	/*auto it = l.insert(iterator, 23);  // it points to the newly added elements
	++it;  //increment it so that it denotes that same elements as before
	*/

	//When we use front_iterator, elements are always inserted  ahead of the then first element in the container
	std::list<int> lst1{ 1,2,3,4 };
	std::list<int> lst2, lst3;
	std::copy(lst1.cbegin(), lst1.cend(), std::front_inserter(lst2));
	std::copy(lst1.cbegin(), lst1.cend(), std::inserter(lst3, lst3.begin()));


	practice2();

	//10.4.2 iostream Iterator
	//Even though the iostream types are not containers, there are iterators that can be used with objects of the IO types. An istream_iterator reads an input stream,
	//and an ostream_iterator writes an output stream. These iterators treat their corresponding stream as a sequence of elements of a specified type.
	//Using a stream iterator, we can use the generic algorithms to read data fro or write data to stream objects.

	//istream_iterator Opearations
	//istream_iterator<T> in(is); in reads values of type T from input stream is.
	//istream_iterator<T> end; Off-the-end iterator for an istream_iterator that reads values of type T
}