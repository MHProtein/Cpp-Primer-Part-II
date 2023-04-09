#pragma once
#include <string>
#include <vector>
#include <initializer_list>
#include <memory>
#include <exception>

class StrBlobPtr;

class StrBlob
{
public:
	friend StrBlobPtr;
	typedef std::vector<std::string>::size_type size_type;
	StrBlob();
	StrBlob(std::initializer_list<std::string> il);
	size_type size() const { return data->size(); }
	bool empty()const { return data->empty(); }
	void push_back(const std::string& str) { data->push_back(str); }
	void pop_back();
	std::string& front();
	std::string& back();

private:
	std::shared_ptr<std::vector<std::string>> data;
	//throws msg if data[i] is invalid
	void check(size_type i, const std::string& msg) const;
};

//The shared_ptr will keep track of how many StrBlobs share the same vector and will delete the vector when the last StrBlob using that vector is destroyed.

class StrBlobPtr
{
public:
	StrBlobPtr() :curr(0) {}
	StrBlobPtr(StrBlob& a, size_t sz = 0) :wptr(a.data), curr(sz) {  }
	std::string& deref() const;
	StrBlobPtr& incr();
	StrBlobPtr& operator++(); //prefix
	StrBlobPtr& operator--();
	StrBlobPtr operator++(int);//postfix
	StrBlobPtr operator--(int);
	std::string& operator*() const;
	std::string* operator->() const;

private:
	std::shared_ptr<std::vector<std::string>> check(size_t i, const std::string& msg) const;
	std::weak_ptr<std::vector<std::string>> wptr;
	size_t curr;
};

class TBD
{
public:
	std::string& operator*() const;
	std::string* operator->() const;
private:
	StrBlobPtr p;
};