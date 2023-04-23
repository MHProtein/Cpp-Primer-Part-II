#include "Quote.h"
#include <iostream>

int main()
{
	//Under Inheritance, the scope of a derived class nests inside the scope of its base classes
	Bulk_Quote bulk;
	std::cout << bulk.isbn();
	//the use of the name isbn is resolved as:
	//The compiler cannot find isbn in the Bulk_Quote class.
	//Then search the Bulk_Quote class, then come to Quote class.

	//Name Lookup Happens at Compile Time
	//The static type of an object of an object reference or pointer to a base class is used to determine which members of that object are visible, even when the dynamic type is different
	//from the static type
	Bulk_Quote* bulkP = &bulk;
	Quote* itemP = &bulk;
	bulkP->discount_policy();
	//itemP->discount_policy(); can not search the members in the derived-class scope

	//Name Collisions and Inheritance
	struct Base
	{
		Base() :mem(10) {  }
	protected:
		int mem;
	};
	struct Derived :Base
	{
		Derived(int i) :Derived::mem(10) {  } //Base::mem is default initialized
		int get_mem() { return mem; } //returns Derived::mem
		int get_base_mem() { return Base::mem; }
		//The scope operator overrides the normal lookup and directs the compiler to look for mem starting in the scope of class Base.
	protected:
		int mem; //hides mem in the base
	};
	//A derived-class member with the same name as a member of the base class hides direct use of the base-class member.

	//As Usual, Name Lookup Happens before Type Checking
	//If the a derived class and its base class have same-named functions, even if they have different parameter lists, the function of base class will still be hidden.

	//Virtual Functions and Scope
	//If the virtual function in the base class has a different parameter list from the same-named function in the derived class, the one in the base class will be hidden.
}
