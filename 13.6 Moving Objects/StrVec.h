#ifndef STRVEC_H
#define STRVEC_H
#pragma once

#include <memory>
#include <string>
#include <algorithm>

class StrVec
{
public:
	StrVec() :contents(nullptr), first_free(nullptr), cap(nullptr) {  }
	StrVec(std::initializer_list<std::string> il);
	StrVec(const StrVec&);
	StrVec& operator=(const StrVec&);
	~StrVec();
	auto size() const { return first_free - contents; }
	auto capacity() const { return cap - contents; }
	void push_back(const std::string& str);
	std::string* begin() const { return contents; }
	std::string* end() const { return first_free; }
	void resize(const size_t sz);
	void reserve(size_t sz);

private:
	void reallocate();
	void check_n_size() { if (size() == capacity()) reallocate(); }
	std::pair<std::string*, std::string*> copy(const std::string*, const std::string*);
	void free();
	void alloc_n_move(size_t new_cap);

private:
	std::allocator<std::string> alloc;
	std::string* contents;
	std::string* first_free;
	std::string* cap;
};

#endif

