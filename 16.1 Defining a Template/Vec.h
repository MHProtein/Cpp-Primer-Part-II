#pragma once
#include <memory>

template<typename Ty>
class Vec
{
public:
	Vec();
	Vec(std::initializer_list<Ty> il);
	explicit Vec(size_t sz);
	template<typename IteTy> Vec(IteTy beg, IteTy end);
	Vec(const Vec&);
	Vec(Vec&&) noexcept;
	Vec& operator=(const Vec&);
	Vec& operator=(Vec&&) noexcept;
	void push_back(const Ty& element);
	void pop_back();
	size_t size() const { return end_ - begin_; }
	size_t capacity() const { return capacity_ - begin_; }
	auto begin() const { return begin_; }
	auto end() const { return end_; }
	~Vec();

private:
	void free();
	void reallocate();
	std::allocator<Ty> alloc_;
	Ty* begin_;
	Ty* end_;
	Ty* capacity_;
};

template <typename Ty>
Vec<Ty>::Vec()
{
	begin_ = alloc_.allocate(1);
	capacity_ = end_ = begin_ + 1;
}

template <typename Ty>
Vec<Ty>::Vec(std::initializer_list<Ty> il)
{
	begin_ = alloc_.allocate(il.size());
	capacity_ = end_ = std::uninitialized_copy(il.begin(), il.end(), begin_);
}

template <typename Ty>
Vec<Ty>::Vec(size_t sz)
{
	begin_ = alloc_.allocate(sz);
	capacity_ = end_ = begin_ + sz;
}

template <typename Ty>
template <typename IteTy>
Vec<Ty>::Vec(IteTy beg, IteTy end)
{
	begin_ = alloc_.allocate(end-beg);
	capacity_ = end_ = std::uninitialized_copy(beg, end, begin_);
}

template <typename Ty>
Vec<Ty>::Vec(const Vec& vec)
{
	begin_ = alloc_.allocate(vec.size());
	capacity_ = end_ = std::uninitialized_copy(vec.begin(), vec.end(), begin_);
}

template <typename Ty>
Vec<Ty>::Vec(Vec&& vec) noexcept :begin_(std::move(vec.begin_)), end_(std::move(vec.end_)), capacity_(std::move(vec.capacity_))
{
	vec.begin_ = vec.end_ = vec.capacity_ = nullptr;
}

template <typename Ty>
Vec<Ty>& Vec<Ty>::operator=(const Vec& vec)
{
	if (*vec != *this) 
	{
		free();
		begin_ = alloc_.allocate(vec.size());
		capacity_ = end_ = std::uninitialized_copy(vec.begin(), vec.end(), begin_);
	}
	return *this;
}

template <typename Ty>
Vec<Ty>& Vec<Ty>::operator=(Vec&& vec) noexcept
{
	if (*vec != *this)
	{
		free();
		begin_ = std::move(vec.begin_);
		end_ = std::move(vec.end_);
		capacity_ = std::move(vec.capacity_);
		vec.begin_ = vec.end_ = vec.capacity_ = nullptr;
	}
	return *this;
}

template <typename Ty>
void Vec<Ty>::push_back(const Ty& element)
{
	reallocate();
	alloc_.construct(end_++, element);
}

template <typename Ty>
void Vec<Ty>::pop_back()
{
	alloc_.destroy(--end_);
}

template <typename Ty>
Vec<Ty>::~Vec()
{
	free();
}

template <typename Ty>
void Vec<Ty>::free()
{
	for (auto it = end_; it != begin_; --it)
	{
		alloc_.destroy(it);
	}
	alloc_.deallocate(begin_, capacity_ - begin_);
}

template <typename Ty>
void Vec<Ty>::reallocate()
{
	if (size() == capacity())
	{
		size_t new_capacity = size() == 1 ? 4 : size() * 2;
		auto new_begin = alloc_.allocate(new_capacity);
		auto new_end = std::uninitialized_copy(std::make_move_iterator(begin()), std::make_move_iterator(end()), new_begin);
		free();
		begin_ = new_begin;
		end_ = new_end;
		capacity_ = begin_ + new_capacity;
	}
}

