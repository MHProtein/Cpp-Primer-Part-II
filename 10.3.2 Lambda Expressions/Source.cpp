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
#include "D:\\C++Primer Part I\\7.1 Defining Abstract Data Types\\Sales_data.h"

inline auto isShorter(const std::string& s1, const std::string& s2)
{
	return s1.size() < s2.size() ? true : false;
}

inline auto givenSize(const std::string& s)
{
	return s.size() >= 5 ? true : false;
}

template<class T>
auto practice1(T a,T b)
{
	auto x = [](T m, T n)->T
	{
		return m + n;
	};
	return x(a, b);
}

void biggies(std::string& target_string,size_t min_size)
{
	std::istringstream strm(target_string);
	std::vector<std::string> words;
	std::string temp;
	while (strm >> temp)
		words.emplace_back(temp);

	std::stable_sort(words.begin(), words.end(), [](const std::string& s1, const std::string& s2) {return s1.size() < s2.size(); });
	auto first_target = std::find_if(words.begin(), words.end(), [min_size](const std::string& s) {s.size() >= min_size; });
	std::for_each(first_target, words.end(), [](const std::string& s) {std::cout << s << " "; });
	std::cout << std::endl;

}

int main()
{
	std::string s("the quick red fox jumps over the slow red turtle");
	std::vector<std::string> words;
	std::istringstream strm(s);
	std::string temp;
	while (strm >> temp)
		words.emplace_back(temp);
	std::sort(words.begin(), words.end());
	auto after_unique = std::unique(words.begin(), words.end());
	words.erase(after_unique, words.end());
	std::stable_sort(words.begin(), words.end(), isShorter);
	auto after_givensize = std::find_if(words.begin(), words.end(), givenSize); //find the first element that conforms to the condition of the predicate and returns a iterator denotes it.
	for (; after_givensize != words.end(); ++after_givensize)
	{
		std::cout << *after_givensize << std::endl;
	}

	//Introducing Lambda
	//A lambda expression represents a callable unit of code. It can be thought of as an unnamed, inline function. Like any function, a lambda has a return type, a parameter list, and a function body.
	//Unlike a function, lambdas may be defined inside a function.
	//A lambda function has the form:
	//[capture list](parameter list) -> return type{ function body }
	//capture list is an (often empty) list of local variables defined in the enclosing function. and a lambda must use a trailing return
	auto f = []()->int {return 42; };
	//We can omit either or both of the parameter list and  return type but must always include the capture list and function body
	//Here, we've defined f as a callable object that takes no arguments and returns 42
	//You can call f just by using the call operator
	std::cout << f() << std::endl;

	//Passing Arguments to a Lambda
	auto g = [](int n)->auto
	{
		int sum = 0;
		for (int i = 0; i <= n; ++i)
		{
			sum += n;
		}
		return sum;
	};
	std::cout << g(20) << std::endl;
	//You can rewrite stable_sort like this
	std::stable_sort(words.begin(), words.end(), [](const std::string& s1, const std::string& s2)->auto {return s1.size() < s2.size(); });
	//Using the Capture List
	size_t sz = 4;
	auto sizeCompare = [sz](const std::string& s)->auto {return s.size() >= sz; };
	auto ite = std::find_if(words.begin(), words.end(), sizeCompare);
	//Now we can change the size when calling find_if
	//A lambda may use a variable local to its surrounding function only if the lambda captures that variable in its capture list

	//for_each Algorithm
	std::for_each(ite, words.end(), [](const std::string& s) {std::cout << s<<" "; });
	std::cout << std::endl;
}