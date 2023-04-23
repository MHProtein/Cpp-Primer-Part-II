#include <iostream>
#include <vector>
#include <string>
#include <ostream>
#include <memory>
#include "Blob.h"
#include "Vec.h"
#include "shard_ptr_re.h"
#include "unique_ptr_re.h"
#include <functional>
#include "D:\\C++ Primer Part II\\14.2 Input and Output Operators\\Sales_data.h"



//16.1.1 Function Templates
template<typename T>
int compare(const T& lhs, const T& rhs)
{
	if (std::less<T>()(lhs, rhs)) return -1; //makes sure we can pass pointers to the function
	if (std::less<T>()(rhs, lhs)) return 1; //The tests in the body use only < comparisons
	return 0;
	//Template programs should try to minimize the number of requirements placed on the argument types
} 

//Nontype Template Parameters
template<unsigned N, unsigned M>
int compare(const char(&p1)[N],const char(&p2)[M])
{
	return strcmp(p1, p2);
}
//A nontype parameter may be an integer type, or a pointer or reference to an object or to a function
//type.

//inline and constexpr Function Templates
template<typename T>
inline T min(const T&, const T&);

//To generate an instantiation, the compiler needs to have the code that defines a function template or
//class template member function.
//So we gotta define template functions when declaring them in the header.

template<typename IteratorType, typename ValueType>
IteratorType find(IteratorType beg, IteratorType end, const ValueType& target_value)
{
	for (; beg != end; ++beg)
	{
		if (*beg == target_value)
			return beg;
	}
	return end;
}

template<typename Array, size_t size>
void print(const Array (&arr)[size])
{
	for (const auto & elem : arr)
	{
		std::cout << elem << std::endl;
	}
}

//Template Type Aliases
typedef Blob<std::string> StrBlob;
template<typename T> using twin = std::pair<T, T>;
twin<std::string> authors;
template<typename T> using partNo = std::pair<T, unsigned>;
partNo<int> pn; //std::pair<int, unsigned>

//static Members of Class Templates
template<typename T> class Foo
{
public:
	static std::size_t count() { return ctr_; }

	static std::size_t ctr_;
};

Foo<std::string> fs; //instantiates static members Foo<std::string>::ctr and Foo<std::string>::count
Foo<int> fi1, fi2, fi3; //all three objects share the same Foo<int>::ctr and Foo<int>::count members
size_t Foo<int>::ctr_ = 10;

template<unsigned Width, unsigned Height>
struct Screen
{
	unsigned width = Width;
	unsigned height = Height;
};

//16.1.3 Template Parameters
template<typename Foo>
Foo clac(const Foo& a, const Foo& b)
{ //You can use any name to name template parameter
	Foo tem = a;
	return tem;
}

template<typename T>
typename T::value_type top(const T& c)
{
	if (!c.empty())
		return c.back();
	else
		return typename T::value_type(); //use the constructor of value_type
	//top function expects a container as its argument  and uses typename to specify its return type and to generate a value initialized element to return if c has no
	//elements
}

//Default Template Arguments
template<typename T, typename F = std::less<T>>
int compare(const T& v1, const T& v2, F f = F())
{
	if (f(v1, v2)) return -1;
	if (f(v2, v1)) return 1;
	return 0;
}

//Sales_data item1, item2;
//compare(item1, item2, [](const Sales_data& s1, const Sales_data& s2) {return s1.isbn() < s2.isbn(); });

//Template Default Arguments and Class Templates
template<class T = int> class Numbers
{
public:
	Numbers(T v = 0) :val_(v) {  }
private:
	T val_;
};

Numbers<> num;

template<typename ContainerType>
void print_elem(const ContainerType& container)
{
	for (typename ContainerType::size_type i = 0; i != container.size(); ++i)
	{
		std::cout << container.at(i) << std::endl;
	}
}

template<typename IteratorType>
void print_elem(IteratorType begin, const IteratorType end)
{
	for (IteratorType ite=begin; ite != end; ++ite)
	{
		std::cout << *ite << std::endl;
	}
}

//16.1.4 Member Templates
class DebugDelete
{
public:
	DebugDelete(std::ostream& s = std::cerr) :os_(s) {  }
	template<typename T> void operator()(T* p) const
	{
		os_ << "deleting unique_ptr" << std::endl;
		delete p;
	}
private:
	std::ostream& os_;
};

void use_ptr(unique_ptr_re<int, DebugDelete>& p)
{
	
}

//Controlling Instantiations
//explicit instantiation can avoid the overhead to instantiate same templates in different separated-compiled files
extern template Blob<std::string>; //declaration
template Blob<std::string>; //definition
//declaring an instantiation as extern promises there will be a definition of it somewhere else in the program
//There can be several declarations but only one definition
  
//Instantiation Definitions Instantiate All Members

int main()
{
	//std::cout << compare(1, 0) << std::endl;
	//std::vector<int> vec1{ 1,2,3,4 };
	//std::vector<int> vec2{ 5,6,7,8 };
	//std::vector<std::string> vec3{ "hi","hello","bye" };
	//std::cout << compare(vec1, vec2) << std::endl;
	//std::cout << (vec1 >  vec2) << std::endl;
	//std::cout << *::find(vec2.begin(), vec2.end(), 7) << std::endl;
	//std::cout << *::find(vec3.begin(), vec3.end(), "bye") << std::endl;
	//int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };
	//print(arr);
	//Blob<int> int_blob;

	//BlobPtr<int> p;
	//Blob<double> d1;
	//Blob<double> d2;
	//Screen<1920, 1080> s;
	//std::cout << s.height << "" << s.width << std::endl;

	Vec<int> v{ 1,2,3,4,5 };
	v.push_back(10);
	v.push_back(10);
	v.push_back(10);
	v.push_back(10);
	v.push_back(10);
	v.push_back(10);
	v.push_back(10);
	v.push_back(10); 
	v.push_back(10);
	v.pop_back();
	for (int v1 : v)
	{
		std::cout << v1 << std::endl;
	}
	for (auto it = v.begin(); it != v.end(); ++it)
	{
		std::cout << *it << std::endl;
	}

	//Template Parameters and Scope
	//a template parameter may not be reused within the template
	//and a parameter name cannot be reused.

	//Template Declarations
	//The type and number of typenames of the definition must be the same as the declaration, but not for the parameter names

	//Using Class Members That Are Types


	//std::cout << top(std::vector<int>{}) << std::endl;

	//double* p = new double;
	//DebugDelete d;
	//d(p);
	//int* ip = new int;
	//DebugDelete()(ip);
	//std::unique_ptr<std::string, DebugDelete> str_ptr(new std::string("hello"), DebugDelete());
	//Blob<std::string> strblob;

	unique_ptr_re<int, DebugDelete> unip(10, DebugDelete());
	unip.reset(new int(20));
	std::cout << *unip.get() << std::endl;
	use_ptr(unip);
	unique_ptr_re<std::vector<int>> uniq_ptr(std::vector<int>{1, 2, 3, 4});
	std::function<void(int*)> f(DebugDelete());
	//f(new int(10));

	shared_ptr_re<int> sp(new int(10), DebugDelete());
}

