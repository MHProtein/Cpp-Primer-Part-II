#include "StrVec.h"

StrVec::StrVec(std::initializer_list<std::string> il)
{
	auto b = alloc.allocate(il.size());
	auto iterator = b;
	for (const auto& str : il)
	{
		alloc.construct(iterator++, str);
	}
	contents = b;
	first_free = cap = iterator;
}

StrVec::StrVec(const StrVec& sv)
{
	auto b = alloc.allocate(sv.size());
	auto iterator = b;
	for (const auto& str : sv)
	{
		alloc.construct(iterator++, str);
	}
	contents = b;
	first_free = cap = iterator;
}

StrVec& StrVec::operator=(const StrVec& sv)
{
	auto i = copy(sv.begin(), sv.end());
	contents = i.first;
	first_free = i.second;
	cap = i.second;
	return *this;
}

StrVec::~StrVec()
{
	free();
}

void StrVec::push_back(const std::string& str)
{
	check_n_size();
	alloc.construct(first_free++, str);
}

void StrVec::resize(const size_t sz)
{
	if (sz < capacity())
	{
		if (sz < size())
		{
			for (auto i = first_free; i != contents + sz;)
			{
				alloc.destroy(--i);
			}
		}
		else
		{
			alloc.deallocate(contents + sz, capacity() - sz);
		}
	}
	else
	{
		alloc_n_move(sz);
	}
}

void StrVec::reserve(size_t sz)
{
	if (sz < size())
		alloc_n_move(sz);
}

void StrVec::reallocate()
{
	auto newCap = size() == 0 ? 0 : size() * 2;
	auto newLoc = alloc.allocate(newCap);
	auto dest = newLoc;
	auto conts = contents;
	for (size_t i = 0; i != size(); ++i)
		alloc.construct(dest++, std::move(*conts++));
	free();
	contents = newLoc;
	first_free = dest;
	cap = newLoc + newCap;
}

std::pair<std::string*, std::string*> StrVec::copy(const std::string* beg, const std::string* end)
{
	auto it = alloc.allocate(end - beg);
	return{ it,std::uninitialized_copy(beg,end,it) };
}

void StrVec::free()
{
	if (contents) {
		for (auto i = first_free; i != contents; )
		{
			alloc.destroy(--i);
		}
		alloc.deallocate(contents, capacity());
	}
}

void StrVec::alloc_n_move(size_t new_cap)
{
	auto newdata = alloc.allocate(new_cap);
	auto dest = newdata;
	auto cont = contents;
	for (size_t i = 0; i < size(); ++i)
	{
		alloc.construct(dest++, *cont++);
	}
	contents = newdata;
	first_free = dest;
	cap = newdata + new_cap;
}
