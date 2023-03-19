#include <iostream>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <vector>
#include <string>

int main()
{
	std::map<std::string, size_t>::key_type;
	std::map<std::string, size_t>::mapped_type; //for map only
	std::map<std::string, size_t>::value_type; //returns a pair type

	//11.3.1 Associative Container Iterators
	//When we dereference an iterator, we get a reference to a value of the container's value_type. In the case of map, the value_type is a pair in which first holds the const key and second holds the value:
	std::map<std::string, size_t> word_count{ {"word",1} };
	auto map_it = word_count.begin();
	std::cout << map_it->first;
	std::cout << " " << map_it->second;
	std::cout << std::endl;
	//map_it->first="new key" //error
	++map_it->second;
	//We can change the value but not the key

	//Iterators for sets Are const
	std::set<int> iset = { 0,1,2,3,4,5,6,7,8,9 };
	std::set<int>::iterator set_it = iset.begin();
	if (set_it != iset.end())
	{
		// *set_it = 42; //read-only
		std::cout << *set_it << std::endl;
	}

	//Iterating across an Associative Container
	auto map_cit = word_count.cbegin();
	while (map_cit != word_count.cend())
	{
		std::cout << map_cit->first << " occurs " << map_cit->second << " times." << std::endl;
		++map_cit;
	}

	//11.3.2 Adding Elements
	std::vector<int> ivec({ 2,4,6,8,2,4,6,8 });
	std::set<int> set2;
	set2.insert(ivec.cbegin(), ivec.cend()); //set2 has 4 elements
	set2.insert({ 1,3,5,7,1,3,5,7 });  //set2 has 8 elements

	//c.insert(v)  //v value_type object; args use used
	//c.emplace(args) //For map and set, the element in inserted (or constructed) only if an element with the given key is not already in c.
									//Returns a pair containing an iterator referring to the element with the given key and a bool indicating whether the element was inserted
									//For multimap and multiset, inserts (or constructs) the given element and returns an iterator to the new element
	//c.insert(b, e)  //b and e are iterators that denote a range of c::value_type values;
	//c.insert(il)  //il is a braced list of such values. Returns void.
						//For map and set, inserts the elements with keys that are not already in c. For multiset and multimap inserts, each element in the range.
	//c.insert(p, v)  //Like insert(v) or (emplace(args)), but uses iterator  p as a hint for where to begin the search for where the new element should be stored. Returns an iterator to the element with the given key
	//c. emplace(p, args)

	//Adding Elements to a map

	word_count.insert({ "word", 1 });
	word_count.insert(std::make_pair("word", 1));
	word_count.insert(std::pair<std::string, size_t>("word", 1));
	word_count.insert(std::map<std::string, size_t>::value_type("word", 1));

	//Testing the Return from insert
	std::string word;
	while (std::cin >> word)
	{
		auto ret = word_count.insert({ word,1 });
		if (!ret.second)
			++ret.first->second;
		++word_count.insert({ word, 1 }).first->second;
	}

	//Unwinding the Syntax
	//++ret((ret.first)->second)

	//Adding Elements to multiset or multimap
	std::multimap<std::string, std::string> authors;
	//adds the first element with the key Barth, John
	authors.insert({ "Barth, John","Sot-Weed, Factor" });
	//ok: adds the second element with the key Barth, John
	authors.insert({ "Barth, John","Lost in the Funhouse" });
	//For the containers that allow multiple keys, the insert operation that takes a single element in these types

	//11.3.3 Erasing Elements
	//c.erase(k)   //Removes every element with key k from c/ Returns size_type indicating the number of elements removed.
	//c.erase(p)  //Removes the element denoted by the iterator p from c. p must refer to an actual element in c; it must not be equal to c.end(). Returns an iterator to the element after p or c.end() if p denotes the last element in c.
	//c.erase(b,e)  //Removes the elements int the range denoted by the iterator pair b, e. Returns e
	std::string removal_word = "fdsf";
	if (word_count.erase(removal_word))
	{
		std::cout << "ok: " << removal_word << " removed\n";
	}
	else
		std::cout << "oops: " << removal_word << "not found!\n";

	auto cnt = authors.erase("Barth, John");
	//If authors is the multimap we created, then cnt will be 2.

	//11.3.4 Subscripting a map
	//The map and unordered_map containers provide the subscript operator and a corresponding at function. The set types do not support subscripting because there's no "value" associated with a key in set.
	//The elements are themselves keys, so the operation of "fetching the value associated with a key" is meaningless.
	//We cannot subscript a multimap or an unordered_multimap because there may be more than one value associated with a given key.
	//c[k] Returns the element with key k; if k is not in c, adds a new, value-initialized element with key k.
	//c.at(k) Checked access to the element with key k; throws an out_of_range exception if k is not in c.

	word_count["Arcueid Brunestud"] = 1;
	//The following steps take place:
	//word_count is searched for the element whose key is Arcueid Brunestud. The element is not found.
	//A new key-value pair is inserted into word_count. The key is a const string holding Arcueid Brunestud. The value is value initialized, meaning in this case that the value is 0
	//The newly inserted element is fetched and is given the value 1.
}  