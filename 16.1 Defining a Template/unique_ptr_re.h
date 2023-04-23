#pragma once

class built_int_deleter
{
public:
	built_int_deleter() = default;
	template<typename T>
	void operator()(T* ptr)
	{
		delete ptr;
	}
};

template<typename ElemType, typename DeleterType = built_int_deleter >
class unique_ptr_re
{
	friend void swap(unique_ptr_re& lhs, unique_ptr_re& rhs)
	{
		std::swap(lhs.ptr_, lhs.ptr_);
		std::swap(lhs.deleter_, rhs.deleter_);
	}
public:
	unique_ptr_re() = default;
	explicit  unique_ptr_re(const ElemType& elem) :ptr_(new ElemType(elem)), deleter_(DeleterType()) {  }
	unique_ptr_re(const ElemType& elem, const DeleterType& deleter) :ptr_(new ElemType(elem)), deleter_(deleter) {  }
	explicit  unique_ptr_re( const DeleterType& deleter) :ptr_(new ElemType()), deleter_(deleter) {  }
	unique_ptr_re(const unique_ptr_re&) = delete;
	unique_ptr_re(unique_ptr_re&&) noexcept;
	unique_ptr_re& operator=(const unique_ptr_re&) = delete;
	unique_ptr_re& operator=(unique_ptr_re&&) noexcept;
	~unique_ptr_re();

	ElemType& operator*() const { return *ptr_; }
	ElemType* operator->() const { return ptr_; }
	operator bool() { return ptr_; }

	ElemType* get() const;
	DeleterType& get_deleter() const;
	ElemType* release();
	void reset();
	void reset(ElemType* new_elem);

private:
	void to_delete();
	ElemType* ptr_;
	DeleterType deleter_;
};

template <typename ElemType, typename DeleterType>
unique_ptr_re<ElemType, DeleterType>::unique_ptr_re(unique_ptr_re&& upr) noexcept :ptr_(std::move(upr.ptr_)), deleter_(std::move(upr.deleter_))
{
	upr.ptr_ = nullptr;
}

template <typename ElemType, typename DeleterType>
unique_ptr_re<ElemType, DeleterType>& unique_ptr_re<ElemType, DeleterType>::operator=(unique_ptr_re&& rhs) noexcept
{
	ptr_ = std::move(rhs.ptr_);
	deleter_ = std::move(rhs.deleter_);
	rhs.ptr_ = nullptr;
}

template <typename ElemType, typename DeleterType>
unique_ptr_re<ElemType, DeleterType>::~unique_ptr_re()
{
	to_delete();
}

template <typename ElemType, typename DeleterType>
ElemType* unique_ptr_re<ElemType, DeleterType>::get() const
{
	{
		return ptr_;
	}
}

template <typename ElemType, typename DeleterType>
DeleterType& unique_ptr_re<ElemType, DeleterType>::get_deleter() const
{
	return deleter_;
}

template <typename ElemType, typename DeleterType>
ElemType* unique_ptr_re<ElemType, DeleterType>::release()
{
	ElemType* temp = ptr_;
	ptr_ = nullptr;
	return temp;
}

template <typename ElemType, typename DeleterType>
void unique_ptr_re<ElemType, DeleterType>::reset()
{
	to_delete();
}

template <typename ElemType, typename DeleterType>
void unique_ptr_re<ElemType, DeleterType>::reset(ElemType* new_elem)
{
		to_delete();
		ptr_ = new_elem;
}

template <typename ElemType, typename DeleterType>
void unique_ptr_re<ElemType, DeleterType>::to_delete()
{
	if (ptr_ != nullptr)
	{
		deleter_(ptr_);
		ptr_ = nullptr;
	}
}
