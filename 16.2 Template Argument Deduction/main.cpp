#include <type_traits>
#include <functional>
#include <utility>

//Function-Template Explicit Arguments

template<typename T1, typename T2, typename T3>
T1 sum(const T2&, const T3&);

template<typename T1, typename T2, typename T3>
T3 alternative_sum(const T1&, const T2&);

//16.2.3 Trailing Return Types and Type Transformation
template<typename IteratorType>
auto fcn(IteratorType begin, IteratorType end) -> decltype(*begin)
{
	return *begin;
//If we want users themselves to determine the return type.
}

//The Type Transformation Library Template Classes
//if we want fnc to return a value rather than a reference
template<typename IteratorType>
auto fcn(IteratorType begin, IteratorType end) -> std::remove_reference<decltype(*begin)>::type 
{
	return *begin;
	//If we want users themselves to determine the return type.
}

template<typename T>
T compare(const T&, const T&);

//16.2.5 Template Argument Deduction and References
template<typename T> void f1(T& p); //the argument passed must be a lvalue
//Normal reference binding rules apply; and consts are low level, not top level.

//Type Deduction from Lvalue Reference Function Parameters
//f1(5)  //error: argument to a & parameter must be an lvalue
template<typename T> void f2(const T&);//The const is already part of the function parameter type;
																//therefore, it does not also become part of the template
																	//parameter type.
//f2(5); a const& parameter can be bound to an rvalue.

//Type Deduction from Rvalue Reference Function Parameters
template<typename T> void f3(T&&);

//When we indirectly create references to references, such as in a type alias or a template parameter,
//references collapses take place, that is:
//X& &,X& &&, and X&& & all collapse to type X&
//The type X&& && collapses to X&&

//A function parameter that is an rvalue reference to a template type parameter can be bound to an lvalue; and
//If the argument is an lvalue, then the deduced template argument type will be an lvalue reference type and the function parameter will be instantiated as an
//lvalue reference parameter.

//Writing Template Functions with Rvalue Reference Parameters
template<typename T> void f3(T&& val)
{
	//if T is not a reference type,  line 1 will be :int t = val; if it is , line 1 will be: int& t = val, which means binding val to a reference named t; 
	T t = val; //1
	t = func(t);
	if (val == t) {  }
}

//16.2.6 Understand std::move

//16.2.7 Forwarding
int a = 10;
template<typename T1, typename T2>
void f(T1 v1, T2 v2)
{
	
}
template<typename F, typename T1, typename T2>
void flip(F f, T1&& t1, T2&& t2)
{
	f(std::forward<T2>(t2), std::forward<T1>(t1));
}

void ff(int& s)
{
	
}

int main()
{
	sum<long long>(10, 20);
	//For there's no argument whose type can be used to deduce the type of T1, we must provide an explicit template argument for this parameter
	alternative_sum<int, long, long long>(1, 2);
	//An explicit template argument may be omitted only for the trailing(right-most) parameters

	//16.2.4 Function Pointers and Argument Deduction
	std::function<int(const int&, const int&)>comp_func(compare<int>);
	int&& a = 23;
	
}