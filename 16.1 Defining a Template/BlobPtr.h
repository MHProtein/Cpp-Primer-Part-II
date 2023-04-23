#pragma once
#include <memory>
#include <string>
#include <vector>

template<typename T> class Blob;

template<typename T>
class BlobPtr
{
public:
	BlobPtr() :curr_(0) {  }
	BlobPtr(Blob<T>& a, size_t sz = 0) :blob_ptr_(a.data_), curr_(sz) {  }
	T& operator*() const
	{
		auto p = check(curr_, "deference past end");
		return (*p)[curr_];
	}
	BlobPtr& operator++();
	BlobPtr& operator++(int);
	BlobPtr& operator--();
	BlobPtr& operator--(int);

	//When we are inside the scope of a class template, the compiler treats references to the
	//template itself as if we had supplied template arguments matching the template's own
	//parameters.
private:
	std::shared_ptr<std::vector<T>> check(std::size_t, const std::string&) const;
	std::weak_ptr<std::vector<T>> blob_ptr_;
	std::size_t curr_;
};

template <typename T>
BlobPtr<T>& BlobPtr<T>::operator++()
{
	return ++ *this;
}

template <typename T>
BlobPtr<T>& BlobPtr<T>::operator++(int)
{
	//no check needed here; the call to prefix increment will do the check.
	BlobPtr ret = *this;
	++* this;
	return ret;
}

template <typename T>
BlobPtr<T>& BlobPtr<T>::operator--()
{
	return --*this;
}

template <typename T>
BlobPtr<T>& BlobPtr<T>::operator--(int)
{
	auto ret = *this;
	-- *this;
	return ret;
}
