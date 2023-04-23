#pragma once
#include <functional>

template<typename ElementType>
class shared_ptr_re
{
	friend bool operator==(const shared_ptr_re<ElementType>& lhs, const shared_ptr_re<ElementType>& rhs);

public:
	shared_ptr_re() : ptr_(new ElementType()), reference_count_(new size_t(1)), deleter_(nullptr) {  }
	explicit shared_ptr_re(ElementType* elem) : ptr_(new ElementType(*elem)), reference_count_(new size_t(1)), deleter_(nullptr) {  }
	shared_ptr_re(ElementType* elem, const std::function<void(ElementType*)>& deleter) : ptr_(elem), reference_count_(new size_t(1)), deleter_(new std::function<void(ElementType*)>(deleter)) {  }
	shared_ptr_re(const shared_ptr_re&);
	shared_ptr_re(shared_ptr_re&&) noexcept;
	shared_ptr_re& operator=(const shared_ptr_re&);
	shared_ptr_re& operator=(shared_ptr_re&&) noexcept;
	~shared_ptr_re() { to_delete(); }

	void reset();
	void reset(ElementType* ptr);
	void reset(ElementType* ptr, const std::function<void(ElementType*)>& deleter);

	ElementType* get() const { return ptr_; }
	bool unique() const { return *reference_count_ == 1; }
	size_t use_count() const { return *reference_count_; }

	ElementType& operator*() const { return *ptr_; }
	ElementType* operator->() const { return ptr_; }

private:
	void to_delete();
	ElementType* ptr_;
	size_t* reference_count_;
	std::function<void (ElementType*)> deleter_;
};
template<typename ElementType>
bool operator==(const shared_ptr_re<ElementType>& lhs, const shared_ptr_re<ElementType>& rhs)
{
	return lhs.ptr_ == rhs.ptr_ && lhs.reference_count_ == rhs.reference_count_ && lhs.deleter_ == rhs.deleter_;
}

template<typename ElementType>
bool operator!=(const shared_ptr_re<ElementType>& lhs, const shared_ptr_re<ElementType>& rhs)
{
	return !operator==(lhs, rhs);
}

template <typename ElementType>
shared_ptr_re<ElementType>::shared_ptr_re(const shared_ptr_re& spr) :ptr_(spr.ptr_), reference_count_(spr.reference_count_), deleter_(spr.deleter_)
{
	++* reference_count_;
}

template <typename ElementType>
shared_ptr_re<ElementType>::shared_ptr_re(shared_ptr_re&& spr) noexcept :ptr_(std::move(spr.ptr_)), reference_count_(std::move(spr.reference_count_)), deleter_(std::move(spr.deleter_))
{
	spr.ptr_ = spr.reference_count_ = spr.deleter_ = nullptr;
}

template <typename ElementType>
shared_ptr_re<ElementType>& shared_ptr_re<ElementType>::operator=(const shared_ptr_re& rhs)
{
	if (rhs != *this) 
	{
		to_delete();
		ptr_ = rhs.ptr_;
		reference_count_ = rhs.reference_count_;
		deleter_ = rhs.deleter_;
		++* reference_count_;
	}
	return *this;
}

template <typename ElementType>
shared_ptr_re<ElementType>& shared_ptr_re<ElementType>::operator=(shared_ptr_re&& rhs) noexcept
{
	if (rhs != *this)
	{
		to_delete();
		ptr_ = std::move(rhs.ptr_);
		reference_count_ = std::move(rhs.reference_count_);
		deleter_ = std::move(rhs.deleter_);
		++* reference_count_;
		rhs.ptr_ = rhs.reference_count_ = rhs.deleter_ = nullptr;
	}
	return *this;
}

template <typename ElementType>
void shared_ptr_re<ElementType>::reset()
{
	to_delete();
}

template <typename ElementType>
void shared_ptr_re<ElementType>::reset(ElementType* ptr)
{
	to_delete();
	ptr_ = ptr;
}

template <typename ElementType>
void shared_ptr_re<ElementType>::reset(ElementType* ptr, const std::function<void(ElementType*)>& deleter)
{
	to_delete();
	ptr_ = ptr;
	deleter_ = new std::function<void(ElementType*)>(deleter);
}

template <typename ElementType>
void shared_ptr_re<ElementType>::to_delete()
{
	if (ptr_ && -- * reference_count_ == 0)
	{
		deleter_ ? deleter_.operator()(ptr_) : delete ptr_;
		delete reference_count_;
	}
	else if (!ptr_)
	{
		return;
	}
}

template<typename Ty_, typename ...Args>
shared_ptr_re<Ty_> make_shared_re(Args&&... args)
{
	return shared_ptr_re<Ty_>(new Args(std::forward<Args>(args)...));
}


