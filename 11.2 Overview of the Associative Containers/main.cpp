#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <istream>
#include <list>
#include <utility>
#include <vector>
#include "Sales_data.h"

//The associative containers  do not support the sequential-container position-specific operations, such as push_front or back
//Because the elements are stored based on their keys, these operations would be meaningless for the associative containers.
//Moreover, they do not support the constructors or insert operations that take an element value and a count.

bool compareIsbn(const Sales_data& data1,const Sales_data& data2)
{
	return data1.isbn() < data2.isbn();
}

std::pair<std::string,int> process(std::vector<std::string>& v)
{
	if (!v.empty())
		return { v.back(),v.back().size() };
	else
		return std::pair<std::string, int>();
}

void practice()
{
	std::map < std::string, std::vector<std::string>> Families;
	std::string name;
FLAG:
	while (std::cout << "Enter the last name: ", std::cin >> name)
	{
		std::cout << "Enter children's names (split by space): ";
		std::istream_iterator<std::string> childrenNames(std::cin), end;
		std::copy(childrenNames, end, std::back_inserter(Families[name]));
	}
	char ans;
	std::cout << "End?(Y/N): ";
	std::cin >> ans;
	if (toupper(ans) == 'Y')
		return;
	else
		goto FLAG;
}

void practice2()
{
	std::map<std::string, std::list<size_t>> lineNumber;
}

void practice3()
{
	std::istream_iterator<std::string> strBeg(std::cin), strEnd;
	std::istream_iterator<int> intBeg(std::cin), intEnd;
	std::vector<std::string> s(strBeg, strEnd);
	std::vector<int> i(intBeg, intEnd);
	std::vector<std::pair<std::string, int>> pairs;
	i.resize(s.size());
	for(auto sIter=s.cbegin(),iIter=i.cbegin();sIter!=s.cend();++sIter,++iIter)
	{
		pairs.emplace_back(*sIter,*iIter);
	}
}

int main()
{
	//11.2.1 Defining an Associative Container
	std::map<std::string, size_t> word_count; //empty
	//list initialization
	std::set<std::string> exclude{ "The","But","And","Or","An","A","the","but","and","or","an","a" };
	std::map<std::string, std::string> authors = { {"Joyce","James"},{"Austen","Jane"},{"Dickens","Charles"} };

	//Initializing a multimap or multiset
	//In a multimap or multiset, there can be several elements with the same key.
	std::vector<int> ivec;
	for (size_t i = 0; i != 10; ++i)
	{
		ivec.push_back(i);
		ivec.push_back(i);
	}
	std::set<int> iset(ivec.cbegin(), ivec.cend());
	std::multiset<int> miset(ivec.cbegin(), ivec.cend());

	std::cout << ivec.size() << std::endl;
	std::cout << iset.size() << std::endl; //iset has only ten elements: one for each distinct element in ivec
	std::cout << miset.size() << std::endl;

	//11.2.2 Requirements on Key Type
	//For the ordered containers -- map, multimap, set and the multiset -- the key type must define a way wo compare the elements.
	//By default, the library uses the < operator for the key type to compare the keys

	//Key Types for Ordered Containers
	//The specified operation must define a strict weak ordering over the key type. We can think of a strict weak ordering as "less than," although our function might use a more complicated procedure.
	//When we define it, the comparision must have the following properties
	// 1. Two keys cannot both be "less than" each other; if k1 is "less than" k2, then k2 must never be "less than" k1
	// 2. If k1 is "less than" k2 and k2 is "less than" k3, then k1 must be "less than" k3
	// 3. If there two keys, and neither key is "less than" the other, then we'll say that those keys are "equivalent." If k1 is "equivalent" to k2 and k2 is "equivalent to k3, then k1 must be "equivalent" to k3.
	//If two keys are equivalent, the container treats them as equal. When used as a key to a map, there will be only one element associated with those keys, and either key can be used to access the corresponding value.
	//Equivalent means two elements are the same in some aspects while equal means two elements are the same in every aspect.

	//Using a Comparison Function for the Key Type
	std::multiset<Sales_data, decltype(compareIsbn)*> bookstore(compareIsbn);
	std::multimap<Sales_data, auto*> bookstore2(compareIsbn);
	//Here, we use decltype to specify the type of our operation, remembering that when we use decltype to form a function pointer, we must add a * to indicate that we're using a pointer to the given function type.
	//We initialize bookstore from compareIsbn, which means that when we add elements to bookstore , those elements will be ordered by calling compareIsbn.
	//That is, the elements in bookstore will be ordered by their ISBN members. We can write compareIsbn instead of & compareIsbn as the constructor argument because when we use the name of a function,
	//it is automatically converted into a pointer if needed. We could have written &compareIsbn with the same effect.

	//11.2.3 The pair Type
	//A pair holds two data members. Like the containers, pair is a template from which we generate specific types. We must supply two type names when we create a pair.
	//The data members of the pair have the corresponding types. There is no requirement that the two types be the same.
	std::pair<std::string, std::string> anon;
	std::pair<std::string, size_t> count;
	std::pair<std::string, std::vector<int>> line;
	//We can also provide initializers for each members
	std::pair<std::string, std::string> author{ "James","Joyce" };
	//Unlike other library types, the data members of pair are public. These members are named first and second, respectively.
	std::cout << author.first << " " << author.second << std::endl;
	//Operations on pairs
	int a = 1, b = 2;
	std::pair x = std::make_pair(1, 2);

	//A Function to Create pair objects
	//see function process
}