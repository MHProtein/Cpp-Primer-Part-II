#include <iostream>
#include <sstream>
#include <string>

template<typename  T>
std::string debug_rep(const T& t)
{
	std::ostringstream ret;
	ret << t;
	return ret.str();
}

template<typename T>
std::string debug_rep(T* p)
{
	std::ostringstream ret;
	ret << "pointer: " << p;
	if (p)
		ret << " " << debug_rep(*p);
	else
		ret << " null pointer";
	return ret.str();
}

//Nontemplate and Template Overloads
std::string debug_rep(const std::string& s)
{
	return '"' + s + '"';
}
//When a nontemplate function provides an equally good match for a call as a function template, the nontemplate version is preferred.

std::string debug_rep(char* p)
{
	return debug_rep(std::string(p));
}
std::string debug_rep(const char* p)
{
	return debug_rep(std::string(p));
}

//remember to declare all versions of overloaded functions

int main()
{
	std::string s("hi");
	auto str = debug_rep("hi");
	std::cout << str << std::endl;
}