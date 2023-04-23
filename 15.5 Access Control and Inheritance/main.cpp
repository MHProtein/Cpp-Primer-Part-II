#include "Quote.h"
class Base
{
	friend class Pal;
public:
	void pub_mem();
protected:
	int prot_mem;
private:
	char priv_mem;
};

class Sneaky :public Base
{
	friend void clobber(Sneaky& s);
	friend void clobber(Base& s);
	int j;

};

class Pal
{
public:
	int f(Base b) { b.priv_mem; return b.prot_mem; }
	int f2(Sneaky s) { return s.prot_mem; }
};

class D2 :public Pal
{
public:
	//int f(Base b) { return b.prot_mem; } //no access, friend won't be inherited.
};

void clobber(Sneaky& s)
{
	s.j = s.prot_mem = 0;
}
void clobber(Base& b)
{
	//b.prot_mem = 0;
	//You can't access protected members of the base class through derived class
}

struct Pub_Derv :public Base
{
	int f() { return prot_mem; }
	//char g() { return priv_mem; } //inaccessible to private members of the base class
};

struct Priv_Derv :private Base
{
	int f1() { return prot_mem; }

	//char g1() { return priv_mem; } //inaccessible to private members of the base class
};

struct Prot_Derv :protected Base
{
	int f1() { return prot_mem; }
	//char g1() { return priv_mem; } //inaccessible to private members of the base class
};

struct  Derived_from_Public :public Pub_Derv
{
	int use_base() { return prot_mem; }
};

struct  Derived_from_Protected :public Prot_Derv
{
	int use_base() { return prot_mem; }
};

struct  Derived_from_Private :public Priv_Derv
{
	//All members in Base are private
	//int use_base() { return prot_mem; } //Base::prot_mem is private in Priv_Derv
	int f2()
	{
		//Base* p = &Priv_Derv(); //derived-to-base conversion inaccessible
	}
};

int main()
{
	//protected Members
	//Users can't access to it, whereas its derived classes can.
	//A derived class member or friend may access the protected members of the base class only through a derived object. The derived class has no special access to the protected
	//members of base-class objects.

	//public, private, and protected Inheritance
	//derivation access specifiers control the access of the users and other classes derived from the derived class have to the members inherited from Base:
	Pub_Derv d1;
	Priv_Derv d2;
	Prot_Derv d3;
	d1.pub_mem();
	//d2.pub_mem();  //cannot access members of Base part of Priv_Derv object, the inheritance specifier is private
	//d3.pub_mem(); //base members are protected

	//Friendship and Inheritance
	//Friendship is not interited. Friends of the base have no special access to members of its derived classes, and friends of a derived class have no special access to the base class.

	//Exempting Individual Members
	//Sometimes we need to change the access level of a name that a derived class inherits. We can do so by providing a using declaration.
	class Base1
	{
	public:
		std::size_t size() const { return n; }
	protected:
		std::size_t n;
	};
	class Derived1 :private Base1
	{
	public:
		using Base1::size;
	protected:
		using Base1::n;
		//By default, the size and n members of Base1 should've been private to users, whereas, we used the using operator to make size and n respectively public and protected.
	};
	Derived1 dd1;
	dd1.size();
	//A using declaration can name any member but private ones of a direct or indirect class.

	class DD1 :Base {  }; //private inheritance by default
	struct DD2 :Base {  }; //public inheritance by default

}