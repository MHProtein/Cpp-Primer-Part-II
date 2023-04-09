#include "StrBlob.h"
#include <stdexcept>

StrBlob::StrBlob():data(std::make_shared<std::vector<std::string>>())
{
}

StrBlob::StrBlob(std::initializer_list<std::string> il):data(std::make_shared<std::vector<std::string>>(il))
{
}

void StrBlob::pop_back()
{
	check(0, "pop_back on empty StrBlob");
	data->pop_back();
}

std::string& StrBlob::front()
{
	check(0, "front on empty StrBlob");
	return data->front();
}

std::string& StrBlob::back()
{
	check(0, "back on empty StrBlob");

	return data->back();
}

void StrBlob::check(size_type i, const std::string& msg) const
{
	if (i >= data->size())
		throw std::out_of_range(msg);
}

std::string& StrBlobPtr::deref() const
{
	return check(curr, "dererence past the end")->at(curr);
}

StrBlobPtr& StrBlobPtr::incr()
{
	check(curr, "increment past end of StrBlobPtr");
	++curr;
	return *this;
}

std::shared_ptr<std::vector<std::string>> StrBlobPtr::check(std::size_t i, const std::string& msg) const
{
	if (this->wptr.lock())
	{
		throw std::runtime_error("unbound StrBlobPtr");
	}
	if (i >= wptr.lock()->size())
	{
		throw std::out_of_range(msg);
	}
	return wptr.lock();
}
