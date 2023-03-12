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
#include <D:\C++Primer Part I\7.1 Defining Abstract Data Types\Sales_data.h>

//10.3.1 Passing a Function to an Algorithm
//Predicates(Î½´Ê)
//A predicate is an expression that can be called and that returns a value that can be used as a condition.
//predicates used by library algorithms are either unary predicates (meaning they have a single parameter)  or binary predicates (meaning they have two parameters)
//The algorithms that take predicates call the given predicate on the elements in the input range.
//As a result, it must be possible to convert the element type to the parameter type of the predicate

inline auto compareIsbn(const Sales_data& data1,const Sales_data& data2)
{
	return data1.isbn() < data2.isbn();
}

auto practice(const std::vector<Sales_data>& data_set)
{
	std::sort(data_set.begin(), data_set.end(), compareIsbn);
}

inline bool is_5Words(std::string& word)
{
	return word.size() >= 5 ? true : false;
}

auto practice2(const std::vector<std::string>& words)
{
	auto it = std::partition(words.begin(), words.end(), is_5Words);
	//
}

inline bool isShorter(const std::string& s1, const std::string& s2)
{
	return s1.size() < s2.size();
}

int main()
{
	std::istringstream strm("the quick red fox jumps over the slow red turtle");
	std::vector<std::string> sentence;
	std::string temp;
	while (strm >> temp)
		sentence.emplace_back(temp);
	std::sort(sentence.begin(), sentence.end());
	auto end_unique = std::unique(sentence.begin(), sentence.end());
	sentence.erase(end_unique, sentence.end());
	std::sort(sentence.begin(), sentence.end(), isShorter); //sort on word length, shortest to longest, no guarantee to keep the alphabetical order
	for (const auto & word : sentence)
	{
		std::cout << word << std::endl;
	}

	//Sorting Algorithms
	std::stable_sort(sentence.begin(), sentence.end(), isShorter);
	//resort by length, maintaining alphabetical order among words of the same length

}