#include "SimpStr.h"

SimpStr::SimpStr(const char* str)
{
	char* s1 = const_cast<char*>(str);
	while (*s1)
		++s1;
	range_initializer(str, ++s1);
}

SimpStr::SimpStr(const SimpStr& str)
{
	range_initializer(str.begin(), str.end());
	std::cout << "copy constructor" << std::endl;
}

SimpStr& SimpStr::operator=(const SimpStr& str)
{
	auto ite = alloc_n_copy(str.begin(), str.end());
	free();
	content = ite.first;
	cap = first_free = ite.second;
	std::cout << "copy-assignment operator" << std::endl;
	return *this;
}

std::pair<char*, char*> SimpStr::alloc_n_copy(const char* beg, const char* end)
{
	auto newLoc = alloc.allocate(end - beg);
	return { newLoc,std::uninitialized_copy(beg,end,newLoc) };
}

inline void SimpStr::range_initializer(const char* first, const char* last)
{
	auto newstr = alloc_n_copy(first, last);
	content = newstr.first;
	cap = first_free = newstr.second;
}

void SimpStr::free()
{
	if(content)
	{
		for (auto i = first_free; i != content; --i)
		{
			alloc.destroy(i);
		}
		alloc.deallocate(content, capacity());
	}
}
