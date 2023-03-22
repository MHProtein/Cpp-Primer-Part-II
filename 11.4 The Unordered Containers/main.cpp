#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <format>
#include "Sales_data.h"

//These unordered containers use a hash function and the key type's == operation.
//An unordered container is most useful when we have a key type for which there's no obvious ordering relationship among the elements.
//These containers are also useful for applications in which the cost of maintaining the elements in order is prohibitive

//Although hashing gives better average case performance in principle, achieving good results in particular often requires a fair bit of performance testing and tweaking. As a result,
//it is usually easier (and often yields better performance) to use an ordered container.

auto hasher(const Sales_data& sd)
{
	//Our hasher function uses an object on the library hash of string type to generate a hash code from the ISBN member.
	return std::hash<std::string>()(sd.isbn());
}
bool eqOp(const Sales_data& lhs, const Sales_data& rhs)
{
	return lhs.isbn() == rhs.isbn();
}
int main()
{
	std::unordered_map<std::string, size_t> word_count;
	std::string word;
	while(std::cin>>word)
	{
		++word_count[word];
	}
	for (const auto & count : word_count)
	{
		std::cout << std::format("{} occurs {} {}", count.first, count.second, (count.second > 1 ? "times" : "time"));
	}

	//Managing the Buckets
	//The unordered containers are organized as a collections of buckets, each of which holds zero or more elements. These containers use a hash function to map elements to buckets.
	//To access an element, the container first computes the element's hash code, which tells which bucket to search. The container puts all of its elements with a given hash value into the same bucket.
	//As a result, the performance of an unordered container depends on the quality of its hash function and on the number and size of its buckets.
	//The hash function must always yield the same result when called with the same argument. Ideally, the hash function also maps each particular value to a unique bucket.
	//However, a hash function is allowed to map elements with differing keys to the same bucket. When a bucket holds several elements, those elements are searched sequentially to find the one we want.
	//Typically, computing an element's hash code and finding its bucket is a fast operation. However, if the bucket has many elements, many comparisons may be needed to find a particular element.

	//Bucket Interface
	std::unordered_map<std::string, std::string> unomap;
	unomap.bucket_count(); //Number of buckets in use
	unomap.max_bucket_count(); //Largest number of buckets this container can hold
	unomap.bucket_size(2); //Number of elements in the 2nd bucket
	unomap.bucket("f"); //Bucket in which elements with key k would be found

	//Bucket Iteration
	std::unordered_map<std::string, std::string>::local_iterator it; //Iterator type that can access elements in a bucket.
	std::unordered_map < std::string, std::string >::const_local_iterator cit;//const version of the bucket iterator

	//Hash Policy
	unomap.load_factor(); //Average number of elements per bucket. Returns float.
	unomap.max_load_factor(); //Average bucket size that unomap tries to maintain. unomap adds buckets to keep load_factor<=max_load_factor. Returns float.
	unomap.rehash(12); //Reorganize storage so that bucket_count>=n and the bucket_count > size/max_load_factor
	unomap.reserve(12); //Reorganize so that unomap can hold 12 elements without a rehash.

	//Requirements on Key Type for Unordered Containers
	//By default, the unordered containers use the == operator on the key type to compare elements.
	//They also use an object of type std::hash<key_type> to generate the hash code for each element.
	//The library supplies versions of the hash template for the built-in types, including pointers.
	//It also defines hash for some of the library types, including strings and the smart pointer types.
	//Thus, we can directly define unordered containers whose key is cone of the built-in types, or a string or a smart pointer.
	//To use an unordered container that uses a our own class types
	std::unordered_multiset<Sales_data, decltype(hasher)*, decltype(eqOp)*> SDs(42, hasher, eqOp);

}