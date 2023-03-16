#include <numeric>
#include <algorithm>
#include <iostream>
#include <vector>
#include <list>
#include <forward_list>
#include <deque>
#include <stack>
#include <queue>

int main()
{
	//list and forward_list define several algorithms as their members.
	//In particular, the list types define their own versions of sort, merge, remove, reverse and unique.
	//The generic version of sort requires random-access iterators. As a result, sort cannot be used with list and forward_list because these types offer bidirectional and forward iterators, respectively
	//The generic versions of the other algorithms that the list types define can be used with lists, but at a cost in performance. A list can "swap" its elements by changing the links among its elements rather tha swapping the values of those elements.
	//So we have the list-specified operations
	std::list<int> lst1{ 1,2,3,4 };
	std::list<int> lst2{ 5,6,7,8 };
	lst1.merge(lst2);//Merges elements from lst2 onto lst1. Both lst1 and lst2 must be sorted. Elements are removed from lst2, after the merge, lst2 is empty.
	lst1.merge(lst2, [](const int n1, const int n2) {return n1 < n2; }); //The first version uses the < operator; the second version uses the given comparision operator.
	lst1.remove(4); //Calls erase to remove each element that is == to the given value or for which the given unary predicate succeeds.
	lst1.remove_if([](const int n) {return n == 5; });
	lst1.reverse(); //Reverses te order of the elements in lst1
	lst1.sort();
	lst1.sort([](const int n1, const int n2) {return n1 < n2; });
	lst1.unique(); //Calls erase to remove consecutive copies of the same value
	lst1.unique(/*pred*/); //the second uses the given binary predicate

	//splice members
	std::list<int> lst3{ 1,2,3,4,5,6,7,8,9 };
	std::forward_list<int> flst{ 1,2,3,4,5,6 };
	std::forward_list<int> flst2{ 1,2,3,4,5,6 };

	lst3.splice(lst3.end(), lst1); flst.splice_after(flst.begin(), flst2); //p is an iterator to an element in lst3 or an iterator just before an element in flst.
	//This operation will remove all the elements in lst1 and flst2

	//lst3.splice(lst3.cend(), lst1, lst1.cbegin()); flst.splice_after(flst.before_begin(), flst2, flst2.cbegin());
	//This will move the elements that lst1.cbegin() denotes and after onto lst3.

	//and you can enter a range of lst1.
	//merge and splice are destructive on their arguments.

}