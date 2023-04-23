#include "Quote.h"
#include <iostream>

class B
{
public:
	virtual void f1() {  }
};

class D1: public B
{
public:
	void f1() override final
	{
		std::cout << "hi" << std::endl;
	}
};

class D2 :public D1
{
public:
	//void f1() override {  }
	//You can't override a function that is specified final before.
};

int main()
{
	//Whether we will use a virtual function or not, we should always define it, due to the compiler will not know the virtual function will be used or not.
	//When a virtual function through reference or pointer, the compiler generates code to decide at run time which function to call.
	//Dynamic binding happens only when a reference or a pointer calls a function.
	Quote base("0-201-82470-1", 50);
	print_total(std::cout, base, 10); //calls Quote::net_price()
	Bulk_Quote derived("0-201-82470-1", 0.7, 50);
	print_total(std::cout, derived, 20); //calls Bulk_Quote::net_price()
	base = derived; 
	base.net_price(10); //calls Quote::net_price
	//When we call a virtual function on an expression that has a plain---nonreference and nonpointer---type, that call is bound at compile time.

	//Virtual Functions in a Derived Class
	//A derived-class function that overrides an inherited virtual function must have exactly the same parameter type as the base-class function that it overrides
	//And the return type must match, however, there is an exception.
	//When the return type of the function in the base-class is B* or B&, the overridden function can return D* or D&, and this operation require that the derived-to-base conversion is accessible.

	//final and override Specifiers

	//Virtual Functions and Default Arguments
	//When we call a virtual function with default arguments through pointers of references to the base class, the function will use the default arguments in the base-class version.
	//So, better make the arguments in a virtual function and their overridden versions the same.

	//Circumventing the Virtual Mechanism
	Bulk_Quote bq;
	bq.Quote::net_price(12);
	//We used the scope operator to force the bq to call the covered Quote version net_price function, which is resolved at compile time.
	//Do remember to add the scope operator when you wanna call the base-class version of the virtual function inside the overridden version,
	//or this will cause a infinite recursion.

	//When a base-class pointer or a reference binding to a derived class calls a virtual function, the overridden version is invoked.
	//And it's resolved at run time.
}