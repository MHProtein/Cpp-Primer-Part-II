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
#include <fstream>

void practice1()
{
	/*In addition to unique (?10.2.3, p. 384), the library defines function named unique_copy that takes a third iterator
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

void practice3()
{
	std::ifstream ifs ("hi");
	std::istream_iterator<std::string> file_ite(ifs);
	std::istream_iterator<std::string> file_eof;
	std::vector words(file_ite, file_eof);
}

void practice4()
{
	std::istream_iterator<int> int_it(std::cin);
	std::istream_iterator<int> int_eof;
	std::ostream_iterator<int> int_out(std::cout, " ");
	std::vector v(int_it, int_eof);
	std::copy(v.cbegin(), v.cend(), int_out);
	std::cout << std::endl;
}

void practice5()
{
	std::istream_iterator<std::string> s(std::cin), eof;
	std::ostream_iterator<std::string> out(std::cout, " ");
	std::vector words(s, eof);
	std::sort(words.begin(), words.end());
	std::stable_sort(words.begin(), words.end(), [](const std::string& s1, const std::string& s2)->auto {return s1.size() < s2.size(); });
	std::unique_copy(words.cbegin(), words.cend(), out);
	std::cout << std::endl;
}

void practice6()
{
	std::istream_iterator<Sales_data> data_in(std::cin), data_eof;
	std::vector data(data_in, data_eof);
	std::sort(data.begin(), data.end(), [](const Sales_data& data1, const Sales_data& data2)->auto {return data1.isbn() < data2.isbn(); });
	for (auto begin = data.cbegin(), end = begin; end !=data.cend(); begin = end)
	{
		end = std::find_if(begin, data.cbegin(), [](const Sales_data& data1, const Sales_data& data2)->auto {return data1.isbn() != data2.isbn(); });
		//print(std::accumulate(begin, end, Sales_data(begin->isbn)));
	}
}

void practice7()
{
	std::ifstream ifs("file1");
	std::ofstream oddfs("file2"), evenfs("file3");
	std::istream_iterator<int> ifs_ite(ifs), ifs_eof;
	std::ostream_iterator<int> odd_ite(oddfs, " "), even_ite(evenfs, " ");
	std::vector nums(ifs_ite, ifs_eof);
	std::for_each(nums.cbegin(), nums.cend(), [&odd_ite, &even_ite](int n) {if (n % 2) *odd_ite++ = n; else *even_ite++ = n; });
}

void practice8()
{
	
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
	auto ins = std::inserter(l, l.begin()); //inserter creates an iterator that uses insert. This function takes a second argument, which must be an iterator into the given container.
	//Elements are inserted ahead of the element denoted by the given iterator.
	//When we call inserter, we get an iterator(c, iter) that, when used successively, inserts elements ahead of the elements originally denoted by iter.
	ins = 23;
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

	//Operations on istream_iterators
	//An istream_iterator uses >> to read a stream.
	//Therefore, the type that an istream_iterator reads must have an input operator defined. When we create an istream_iterator, we can bind it to a stream.
	//Alternatively, we can default initialize the iterator, which creates an iterator that we can use as the off-the-end value.

	//istream_iterator Opearations
	//istream_iterator<T> in(is); in reads values of type T from input stream is.
	//istream_iterator<T> end; Off-the-end iterator for an istream_iterator that reads values of type T
	//in1 == in2; //    in1 and in2 must read the same type. They are equeal if they are both the end value
	//in1 != in2; //or are bound to the same input stream
	// *in  //returns the value read from the stream
	//in-> men; //Synonym for (*in).mem
	//++in, in++ //Reads the next value from the inout stream using the>> operator for the element type. As usual, the prefix version returns a reference to the inceremented iterator.
	                  // The postfix version returns the old value.

	std::istream_iterator<int> int_it(std::cin);
	std::istream_iterator<int> int_eof;
	std::ifstream in("afile");
	std::istream_iterator<std::string> str_it(in);
	//we can use an istrem_iterator to read the standard input into a vector
	std::vector<int> v1;
	while (int_it != int_eof) //while there's valid input to read
		v1.push_back(*int_it++); //postfix increment reads the stream and returns the old value of the iterator
	//we dereference that iterator to get the previous value read from the stream
	//You can rewrite the program like this
	std::vector v2(int_it, int_eof);

	//Using Stream Iterators with the Algorithms
	//We can use stream iterators with at least some of the algorithms
	std::istream_iterator<int> sum_it(std::cin), sum_eof;
	std::cout << std::accumulate(sum_it,sum_eof,0.0) << std::endl;

	//istream_iterators Are Permitted to Use Lazy Evaluation
	//When we bind an istream_iterator to a stream, we are not guaranteed that it will read the stream immediately. The implementation is permitted to delay reading the stream
	//until we use the iterator.
	//If we create an istream_iterator that we destory without using or if we are synchronizing reads to the same stream from two different objects, then we might care a great deal when the read happens

	//Operations on ostream_iterators
	//When creating an ostream_iterator, we may (optionally) provide a second argument that specifies a character string to print following each element. The string must be a c-style string
	//We must bind an ostream_iterator to a specific stream. There's no empty or off-the-end ostream_iteratore.

	//ostream_iterator<T> out(os); //out writes values of type T to output stream os.
	//ostream_iterator<T> out(os, d); out writes values of type T followed by d to output stream os. d points to a null-terminated character array.
	//out = val //Writes val to the ostream ot which out is bound using the << operator. val must have a type that is compatible with the type that out can write

	std::ostream_iterator<int> out_itee(std::cout, " ");
	for (const int elem : v1)
	{
		*out_itee++ = elem;
	}
	std::cout << std::endl;
	//The * and ++ operators do nothing on an ostream_iterator, so omitting them has no effect on our program. However, we prefer to write the loop as first presented.
	//The loop uses the iterator consistently with how we use other iterator types. You can easily change this loop to execute on another iterator type.
	//Moreover, the behavior of this loop will be clearer to readers of our code.
	//same as above
	for (const int elem : v1)
	{
		out_itee = elem;
	}
	std::cout << std::endl;

	//Aside from writing the loop ourselves, we can more easily print the elements in vec by calling copy
	std::copy(v1.cbegin(), v1.cend(), out_itee);
	std::cout << std::endl;

	//Using Stream Iterators with Class Types
	std::istream_iterator<Sales_data> data_ite;
	std::istream_iterator<Sales_data> data_eof;
	std::ostream_iterator<Sales_data> data_out(std::cout, " ");
	Sales_data sum = *data_ite++;
	Sales_data temp;
	while (data_ite != data_eof)
	{
		if (data_ite->isbn() == sum.isbn())
			sum.combine(const_cast<Sales_data&>(*data_ite++));
		else
		{
			*data_out++ = sum;
			sum = *data_ite++;
		}
	}
	data_out = sum;

	//10.4.3 Reverse Iterators
	//A reverse iterator is an iterator that traverses a container backward, from the last element toward the first.
	//A reverse iterator inverts the meaning of increment and decrement. incrementing(++it) a reverse iterator moves the iterator to the previous element;
	//decrementing(--it) moves the iterator to the next element
	//the following loop prints the vector in reverse order:
	std::vector<int> vec{ 1,2,3,4,5,6,7,8,9,10 };
	for (auto rit = vec.crbegin(); rit != vec.crend(); ++rit)
		std::cout << *rit << std::endl;
	std::sort(vec.rbegin(), vec.rend()); //pushes the smallest element at the end of vec

	//Reverse Iterators Require Decrement Operators
	//You can't create a reverse iterator form a forward_list or a stream iterator since they don't support the -- operation

	//Relationship between Reverse Iterator and Other Iterators
	std::string line("FIRST,MIDDLE,LAST");
	auto rcomma = std::find(line.crbegin(), line.crend(), ',');
	std::cout << std::string(rcomma.base(), line.cend()) << std::endl; //its base member gives us its corresponding ordinary iterator
	//rcomma.base() and rcomma actually refer to different elements, the one with base denotes at the element one behind the latter.
	//Technically speaking, the relationship between normal and reverse iterators accommodates the properties of a left-inclusive range.
	//The point is that [line.crbegin(), rcomma ) and [rcomma.base(), line.crend() ) refer to the same elements in line. In order for that to happen,
	//rcomma and rcomma.base() must yield adjacent positions, rather than the same position, as must crbegin() and cend()
}