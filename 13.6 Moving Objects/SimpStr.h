#pragma once
#include <memory>
#include <iostream>

class SimpStr
{
public:
	SimpStr() :content(nullptr), first_free(nullptr), cap(nullptr) {  }
	explicit SimpStr(const char*);
	SimpStr(const SimpStr&);
	SimpStr& operator=(const SimpStr&);
	auto begin() const { return content; }
	auto end() const { return first_free; }
	auto size() const { return first_free - content; }
	auto capacity() const { return cap - content; }
private:
	void range_initializer(const char*, const char*);
	std::pair<char*, char*> alloc_n_copy(const char* beg, const char* end);
	void free();
private:
	std::allocator<char> alloc;
	char* content;
	char* first_free;
	char* cap;
};


