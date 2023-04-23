#include <memory>
#include <string>
#include <vector>
#include <stdexcept>
#include "BlobPtr.h"

template<typename T> class BlobPtr;

template<typename T>
class Blob
{
	//One to One Friendship
	friend class BlobPtr<T>;
	friend bool operator==(const Blob<T>&, const Blob<T>&);
public:
	using value_type = T;
	using size_type = std::size_t;
	Blob();
	//Member Templates of Class Templates
	template<typename IteType> Blob(IteType begin, IteType end);
	Blob(std::initializer_list<T> il);
	std::size_t size() const { return data_->size(); }
	bool empty() const { return data_->empty(); }
	void push_back(const T& value) const { data_->push_back(value); }
	void push_back(T&& value) const { data_->push_back(std::move(value)); }
	void pop_back() const;
	value_type& back();
	value_type& operator[](size_t i);
	auto begin() const { return data_->begin(); }
	auto end() const { return data_->end(); }
	~Blob() = default;

private:
	std::shared_ptr<std::vector<value_type>> data_;
	void check(std::size_t i, const std::string& msg) const;

	//Each instantiation of a class template constitutes an independent class. The type Blob<string> has no relationship, or any special access to, the members of any other Blob type
	//By default, a member of an instantiated class template is instantiated only if the member is used.
};

template<typename T>
bool operator==(const Blob<T>& lhs, const Blob<T>& rhs)
{
	return *lhs.data_ == *rhs.data_;
}

template <typename T>
Blob<T>::Blob() :data_(std::make_shared<std::vector<value_type>>())
{
}

template <typename T>//type parameter for the class
template <typename IteType> //type parameter for the constructor
Blob<T>::Blob(IteType begin, IteType end): data_(std::make_shared<std::vector<T>>(begin, end))
{
}

template <typename T>
Blob<T>::Blob(std::initializer_list<value_type> il) :data_(std::make_shared<std::vector<value_type>>(il))
{
}

template <typename T>
void Blob<T>::pop_back() const
{
	check(0, "pop_back on an empty Blob");
	data_->pop_back();
}

template <typename T>
typename Blob<T>::value_type& Blob<T>::back()
{
	check(0, "back on empty Blob");
	return data_->back();
}

template <typename T>
typename Blob<T>::value_type& Blob<T>::operator[](std::size_t i)
{
	check(i, "access out of range");
	return data_->at(i);
}

template <typename T>
void Blob<T>::check(std::size_t i, const std::string& msg) const
{
	if (i >= data_->size())
		throw std::out_of_range(msg);
}

template<typename T> class Pal;
class C
{
	friend class Pal<C>; //Pal instantiated with class C is a friend to C

	//all instances of Pal2 are friends to C;
	//no forward declaration required when we befriend all instantiations
	template <typename T> friend class Pal2;
};
template<typename T> class C2
{
	//each instantiation of C2 has the same instance of C2
	friend class Pal<T>; //forward declaration needed
	//Pal3 is a nontemplate class that is a friend of every instance of C2
	friend class Pal3; //prior declaration for Pal3 is not needed.
};

//Befriending the Template's Own Type Parameter
template<typename Type>
class bar
{
	friend Type;  
};
