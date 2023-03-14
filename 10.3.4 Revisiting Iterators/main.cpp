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
#include "Sales_data.h"


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


}