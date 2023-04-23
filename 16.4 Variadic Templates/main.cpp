#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include "D:\C++ Primer Part II\Classes That Manage Dynamic Memory\StrVec.h"
//A variadic template is a template function or class that can take a varying number of parameters.
//The varying parameters are known as a parameters are known as a parameter pack.
//There are template parameter packs and function parameter packs.
template<typename T, typename ... Args>
void foo(const T&, const Args&...rest)
{
	std::cout << sizeof ...(Args) << std::endl; //number of type parameters
	std::cout << sizeof ...(rest) << std::endl; //number of function parameters
}

//16.4.1 Writing a Variadic Function Template
template<typename T>
std::ostream& print(std::ostream& os, const T& obj)
{
	os << obj<<" ";
	return os;
}
template<typename T,typename ...Args>
std::ostream& print(std::ostream& os, const T& obj, const Args&...objs) //expand args
{
	os << obj<<" ";
	return print(os, objs...); //expand objs
}

//Understanding Pack Expansions
template<typename T>
std::string debug_rep(const T& obj)
{
	std::ostringstream strm;
	strm << obj;
	return strm.str();
}

template<typename T>
std::string debug_rep(const T* obj)
{
	std::ostringstream strm;
	strm << obj;
	if (obj)
		strm << ": " << *obj;
	else
		strm << ": nullptr";
	return strm.str();
}

template<typename T>
void debug_rep(T* obj)
{
	debug_rep(const_cast<const T*>(obj));
}

std::string debug_rep(const char* p)
{
	return debug_rep(std::string(p));
}
std::string debug_rep(char* p)
{
	return debug_rep(std::string(p));
}
std::string debug_rep(const std::string& obj)
{
	return obj;
}

template<typename ...Args>
std::ostream& errorMsg(std::ostream& os, const Args&...rest)
{
	return print(os, debug_rep(rest)...);
	//The pattern in an expansion applies separately to each element in the pack.
}

//16.4.3 Forwarding Parameter Packs
//see 16.1 make_shared_re

int main()
{
	int i = 0;
	double d = 3.14;
	std::string s("how now brown cow");
	foo(i, d, s, 42); //3 parameters in the pack
	foo(s, 23, i); //two parameters in the pack
	foo(s); //empty pack
	errorMsg(std::cout, i, d, s, "hi");
}