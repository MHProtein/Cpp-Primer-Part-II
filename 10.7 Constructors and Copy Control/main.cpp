#include "\C++ Primer Part II\15.5 Access Control and Inheritance\Quote.h"

int main()
{
	Quote* itemP = new Quote;
	delete itemP;
	itemP = new Bulk_Quote;
	delete itemP;
	//So long as the base class destructor is virtual, when we delete a pointer to base, the correct destructor will be run.

	//Virtual Destructors Turn Off Synthesized Move
	//The fact that Quote does not have move operations means that its derived classes don't either.

	//Base Classes and Deleted Copy Control in the Derived
	//If the default constructor, copy constructor, copy assignment operator, or destructor in the base class is deleted or inaccessible, then the ones in the derived class will be
	//defined as deleted, since the compiler cannot use the functions in the base class.
	//If the move operation is deleted or inaccessible in the base class, and try to use =default in the derived class move operation, it will be a deleted function.
	//If the base destructor is deleted or inaccessible, the move constructor will also be deleted.

	//Move Operations and Inheritance

	//15.7.3 Derived-Class Copy-Control Members
	//When a derived class defines a copy or move operation, it's responsible for copying or moving the entire object including the base part.

	//Defining a Derived Copy or Move Constructor
	//By default, the base-class default constructor initializes the base-class part of a derived object. If we wanna copy or move the base-class part, we must explicitly use the copy or move
	//constructor for the base class in the derived's constructor initializer list

	//Derived-Class Destructor
	//A derived destructor is only responsible to destroy the resources allocated by the derived class
	//The derived destructor is run first, then the base-class destructor are invoked, back up through the inheritance hierarchy

	//Calls to Virtuals in Constructors and Destructors
	//When we create a Bulk_Quote object, a type transformation takes place, so does when we destroy it.
	//creation: Quote->Bulk_Quote
	//destruction: Bulk_Quote->Quote.

	//15.7.4 Inherited Constructors
	class Base
	{
	public:
		Base() :a_(1) {  }
		Base(int a) :a_(a) {  }
	private:
		int a_;
	};
	class Derv :public Base
	{
	public:
		using Base::Base; //inherit Base's constructors
		//The compiler generates a derived constructor corresponding to each constructor in Base, the compiler generates a constructor in the derived class that has the same parameter
		//list.
		//Derived(int a): Base(a)
		//a constructor using declaration does not change the access level of the inherited constructors.
	};
	
}