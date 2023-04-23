#include <iostream>

#include "Quote.h"

class Base
{
public:
	static void statmem();
};

class Derived:public Base
{
	void f(const Derived&);
};

void Derived::f(const Derived& derived_obj)
{
	Base::statmem();
	Derived::statmem();
	derived_obj.statmem(); //accessed through a Derived object
	statmem(); //accessed through this object
}

//When a class is defined, not just declared, can we use it as a base class.
//Each derived class contains, and may use, the members it inherits from its base class. To use those members, the derived class must know what they are. 

class D1 : public Base
{
	
};
class D2 : public D1
{

};
//In this hierarchy, Base is a direct base to D1 and an indirect base to D2.
//The most derived object contains a subobject for its direct base and for each of its indirect bases.

//If you don't wanna other classes to inherit from a class, you can:
class NoDerived final{};

int main()
{
	//Because a derived object contains subparts corresponding to its base classes, we can use an object of a derived type as if it were an object of its base types.
	//In particular, we can bind a base-class reference or pointer to the base-class part of a derived object

	Quote item;
	Bulk_Quote bulk;
	Quote* p = &item;
	p = &bulk;
	Quote& r = bulk;
	//p and r can only use members the base class, that is quote, has.
	print_total(std::cout, item, 12);
	print_total(std::cout, bulk, 12);

	//15.2.3 Conversions and Inheritance
	//We can bind a pointer or reference to a base-class type to an object of a type derived from that base class.
	//When we use a reference (or a pointer) to a base-class type, we don't know a base or a derived class is bound.
	//Smart pointers support this as well.
	std::shared_ptr<Quote> quotes(std::make_shared<Bulk_Quote>());
	

	//Static Type and Dynamic Type
	//Static type is known at compile time, it is a type with which a variable is declared or that an expression yields., whereas dynamic type is known till run time, and that is the type of
	//the object in memory that the variable or expression represents.
	double ret = r.net_price(10);
	//The static type of r is Quote&. The dynamic type depends on the type of the argument to which r is bound. That type cannot be known until a call is executed at run time.
	//In this case, the static type is Quote&, the dynamic type is Bulk_Quote
	//The dynamic type of a expression that is neither a pointer or a reference will always be the same type corresponding to its static type.

	//There Is No Implicit Conversion from Base to Derived...
	//Alternatively, in those cases when we know that the conversion from base to derived is safe, we can use static_cast to override the compiler.

	//...and No Conversion between Objects
	//If we pass a derived class to the constructors of the base class, the constructor only knows the members it has.
	//If we assign a derived class to a base class, the copy-assignment operator of the base class will be invoked
	//Because the bulk_quote is ignored, we say that is sliced down. 
}
