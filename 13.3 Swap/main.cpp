#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class HasPtrValuelike
{
public:
	friend void swap(HasPtrValuelike&, HasPtrValuelike&);
	friend bool operator<(const HasPtrValuelike& lhs, const HasPtrValuelike& rhs);
	HasPtrValuelike(const std::string& s = std::string()) :ps_(new std::string(s)), i_(0) {  }
	HasPtrValuelike(const HasPtrValuelike& p) :ps_(new std::string(*p.ps_)), i_(p.i_) {  }
	HasPtrValuelike& operator=(HasPtrValuelike);
	auto getstr() const { return *ps_; }
	~HasPtrValuelike() { delete ps_; }
private:
	std::string* ps_;
	int i_;
};

inline void swap(HasPtrValuelike& lhs, HasPtrValuelike& rhs)
{
	std::cout << "HasPtrValuelikeSwaping~" << std::endl;
	std::swap(lhs.ps_, rhs.ps_);
	std::swap(lhs.i_, rhs.i_);
}

bool operator<(const HasPtrValuelike& lhs, const HasPtrValuelike& rhs)
{
	return *lhs.ps_ < *rhs.ps_;
}

//swap is never necessary, but it's an important optimization for classes that allocate resources, which can turn swaps between values into swaps between pointers

//Using swap in Assignment Operators
//Classes that define swap often use swap to define their assignment operator. These operators use a technique known as copy and swap.
//They work like this:
HasPtrValuelike& HasPtrValuelike::operator=(HasPtrValuelike rhs)
{
	swap(*this, rhs); //rhs now points to the memory this object had used
	return *this; //rhs is destroyed, which deletes the pointer in rhs
}
//This technique it automatically handles self assignment and is automatically exception safe,

class HasPtrPointerlike
{
public:
	HasPtrPointerlike(const std::string& s = std::string()) :ps_(new std::string(s)), i_(0), use_(new std::size_t(1)) {  }
	HasPtrPointerlike(const HasPtrPointerlike& p) :ps_(p.ps_), i_(p.i_) { ++* use_; }
	HasPtrPointerlike& operator=(const HasPtrPointerlike& rhs)
	{
		++* rhs.use_;
		if (-- * use_ == 0)
		{
			delete ps_;
			delete use_;
		}
		ps_ = rhs.ps_;
		i_ = rhs.i_;
		use_ = rhs.use_;
		return *this;
	}
	~HasPtrPointerlike()
	{
		if (-- * use_ == 0)
		{
			delete ps_;
			delete use_;
		}
	}

private:
	std::string* ps_;
	int i_;
	std::size_t* use_;
};

int main()
{
	std::vector<HasPtrValuelike> v{ HasPtrValuelike("1"),HasPtrValuelike("2"),HasPtrValuelike("3") };
	std::sort(v.begin(), v.end());
	for (const auto & has_ptr_valuelike : v)
	{
		std::cout << has_ptr_valuelike.getstr() << std::endl;
	}
}