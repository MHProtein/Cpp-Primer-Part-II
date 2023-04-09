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

StrVec::StrVec(StrVec&& s) noexcept :contents(s.contents), first_free(s.first_free), cap(s.cap) //member initializers take over the resources in s
{
	//leave s in a state in which it is safe to run the destructor
	s.contents = s.first_free = s.cap = nullptr;
}

StrVec& StrVec::operator=(std::initializer_list<std::string>&& il)
{
	auto newLoc = alloc.allocate(il.size());
	free();
	auto theEnd = std::uninitialized_copy(std::make_move_iterator(il.begin()), std::make_move_iterator(il.end()), newLoc);
	contents = newLoc;
	cap = first_free = theEnd;
	return *this;
}

StrVec& StrVec::operator=(const StrVec& sv)
{
	auto i = copy(sv.begin(), sv.end());
	contents = i.first;
	first_free = i.second;
	cap = i.second;
	return *this;
}

StrVec& StrVec::operator=(StrVec&& sv) noexcept
{
	if (this != &sv) 
	{
		free();
		contents = sv.contents;
		first_free = sv.first_free;
		cap = sv.cap;
		sv.contents = sv.first_free = sv.cap = nullptr;
	}
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

void StrVec::push_back(std::string&& str)
{
	check_n_size();
	alloc.construct(first_free++, std::move(str));
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
	auto first = alloc.allocate(newCap);
	//Un like other iterators, the dereference operator of a move iterator yields an rvalue reference.
	auto last = std::uninitialized_copy(std::make_move_iterator(begin()), std::make_move_iterator(end()), first);
	free();
	contents = first;
	first_free = last;
	cap = contents + newCap;

	
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

bool operator==(const StrVec& lhs, const StrVec& rhs)
{
	if (lhs.size() != rhs.size())
		return false;

		for (auto lite = lhs.begin(), rite = rhs.begin(); lite != lhs.end();)
		{
			if (*lite++ != *rite++)
				return false;
		}
	return true;
}

bool operator!=(const StrVec& lhs, const StrVec& rhs)
{
	return !(lhs == rhs);
}
