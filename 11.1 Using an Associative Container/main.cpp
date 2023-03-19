#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <format>
#include <algorithm>
#include <iterator>

//Associative containers support efficient lookup and retrieval by a key. The two primary associative-container types are map and set
//The elements in a map are key-value pairs: The key serves as an index into the map, and the value represents the data associated with that index.
//A set element contains only a key; a set supports efficient queries as to whether a given key is present.
//We might use a set to hold words that we want to ignore during some kind of text processing.
//A dictionary would be a good use for a map: The word would be the key, and its definition would be the value

void practice()
{
	std::map<std::string, size_t> word_count;
	std::string word;
	while(std::cin>>word)
	{
		std::transform(word.begin(), word.end(), std::back_inserter(word), toupper);
		if (word.back() == '.' || word.back() == ',')
		{
			word.pop_back();
		}
		++word_count[word];
	}
}

int main()
{
	//Associative Container Types
	std::map<int, int> Map; //Associative array; holds key-value pairs
	std::set<int> Set; //Container in which the key is the value
	std::multimap<int, int> MultiMap; //map in which a key can appear multiple times
	std::multiset<int> MultiSet; //set in which a key can appear multiple times
	std::unordered_map<int, int> UnorderedMap; //map organized by a hash function
	std::unordered_set<int> UnorderedSet; //set organized by a hash function
	std::unordered_multimap<int, int> UnorderedMultiMap; //Hashed map; keys can appear multiple times
	std::unordered_multiset<int> UnorderedMultiSet; //Hashed set; keys can appear multiple times

	//map
	//An associative array is like a "normal" array except that its subscripts don't have to be integers. Values in a map are found by a key rather than by their position.

	std::map<std::string, size_t> word_count;
	std::string word;
	while (std::cin >> word)
		++word_count[word];
	//If word is not already in the map, the subscript operator creates a new element whose key is word and whose value is 0
	for(const auto& w:word_count)
	{
		std::cout << std::format("{} occured {} {}", w.first, w.second, (w.second > 1 ? "time" : "times"));
		//Briefly, a pair is a template type that holds two (public) data elements named first and second.
		//The pairs used by map have a first member that is the key and a second member that is the corresponding value.
		//Thus, the effect of the output statement is to print each word and its associated counter.
	}

	//set
	//In contrast, a set is simply a collection of keys. A set is most useful when we simply want to know whether a value is present
	std::set<std::string> exclude{ "The","But","And","Or","An","A","the","but","and","or","an","a" };
	std::string word2;
	while (std::cin >> word)
	{
		//count only words that are not in exclude
		if (exclude.find(word) == exclude.end())
			++word_count[word];
	}

}