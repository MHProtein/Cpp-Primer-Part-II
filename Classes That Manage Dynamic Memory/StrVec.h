#ifndef STRVEC_H
#define STRVEC_H
#pragma once

#include <memory>
#include <string>
#include <algorithm>

class StrVec
{
	friend bool operator==(const StrVec& lhs, const StrVec& rhs);
	friend bool operator!=(const StrVec& lhs, const StrVec& rhs);

public:
	StrVec() :contents(nullptr), first_free(nullptr), cap(nullptr) {  }
	StrVec(std::initializer_list<std::string> il);
	StrVec(const StrVec&);
	StrVec(StrVec&&) noexcept;
	StrVec& operator=(std::initializer_list<std::string>&& il);
	StrVec& operator=(const StrVec&);
	StrVec& operator=(StrVec&&) noexcept;
	std::string& operator[](size_t n) { return contents[n];  }
	const std::string& operator[](size_t n) const { return contents[n]; }
	~StrVec();
	auto size() const { return first_free - contents; }
	auto capacity() const { return cap - contents; }
	void push_back(const std::string& str);
	void push_back(std::string&&);
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

