#include <utility>
#include "SimpStr.h"
#include "StrVec.h"
#include "Message.h"

int main()
{
	//13.6.1 Rvalue References
	//To support move operations, we have rvalue reference here, which must be bound to a rvalue.
	//An rvalue reference is obtained by using && rather than &.
	//They may be bound only to an object that is about to be destroyed. As a result, we are free to "move" resources from an rvalue reference to another object.
	//We can bind rvalue references to to expressions that require a conversion, to literals, or to expressions that return an rvalue.
	int i = 42;
	int& r = i;
	const int& r3 = i * 42; //ok: we can bind a reference to const to an rvalue
	int&& rr1 = i + 42; //ok: bind rr2 to the result of sum

	//Functions that return a nonreference type, along with the arithmetic, relational, bitwise, and postfix increment/decrement operators, all yields rvalues.

	//Lvalue Persist; Rvalue Are Ephemeral
	//Lvalues have persistent state, whereas rvalues are either literals or temporary objects created in the course of evaluating expressions.
	//Because rvalue references can only be bound to temporaries, we know that
	// 1. The referred-to object is about to be destroyed.
	// 2. There can  be no other users of that object.
	//The facts together mean that code that uses an rvalue reference is free to take over resources from the object to which the reference refers
	//Rvalue references refer to objects that are about to be destroyed. Hence, we can "steal" state from an object bound to an rvalue reference.

	//Variables are Lvalues
	//A variable can be recognized as an operand with no operator.
	//We cannot bind a rvalue reference to another rvalue reference.

	//The Library move Function
	//We can explicitly cast an lvalue to its corresponding rvalue reference type. We can also obtain an rvalue reference bound to an lvalue by calling a new library function named move.
	//The move function return an rvalue reference to its given object.
	int&& rr3 = std::move(rr1);
	//Calling move tells the compiler that we have an lvalue that we want to treat as if it were an rvalue. It is essential to realize that the call to move promises that we do not intend to use
	//rr1 again except to assign to it or destroy it. After a call to move, we cannot make any assumptions about the value of the moved-from object.

	//13.6.2 Move Constructor and Move Assignment
	{
		//These operations are similar to the corresponding copy operations, but they "steal" resources for their given object rather than copy them.

		//The move constructor does not allocate any new memory; it takes over the memory in the given StrVec. Having taken over the memory from its argument, the constructor body sets the
		//pointers in the given object to nullptr. After an object is moved from, that object continues to exist. Eventually, the move-from object will be destroyed, meaning the destructor will be
		//run on that object. The StrVec destructor calls deallocate on first_free. If we neglected to change s.free_first, then destroying the moved-from object will delete the memory we just moved.

		//Move Operations, Library Containers, and Exceptions
		//Since move operations executes by "stealing" resources, it ordinarily does not itself allocate any resources, so move operations will not throw and exceptions,
		//and we should inform the compiler to to less work to exam exceptions.

		//Move-Assignment Operator
		//A Moved-from Object Must Be Destructible

		//The Synthesized Move Operations
		//The compiler will synthesize a move constructor or a move-assignment operator only if the class doesn't define any of its own copy-control members and if every non-static date
		//member of the class can be moved.
		struct X
		{
			int i;
			std::string s;
		};
		struct hasX
		{
			X mem;
		};
		X x, x2 = std::move(x);
		hasX hx, hx2 = std::move(hx);

		//If a class defines either a move constructor or a move-assignment operator, the synthesized copy constructor and copy-assignment operator will be defined as deleted.

		//Rvalues Are Moved, Lvalues Are Copied
		//But Rvalues Are Copied If There Is No Move Constructor
		//If a class has a usable copy constructor and no move constructor, objects will be "moved" by the copy constructor. Similarly for the copy-assignment operator and move-assignment

		//Copy-and-Swap Assignment Operators and Move

		//Move Iterators
		//Library makes no guarantees about which algorithms can be used with move iterators and which cannot. Because moving an object can obliterate the source, you should pass move
		//iterators to algorithms only when you are confident that the algorithm does not access an element after it has assigned to that element or passed that element to a user=defined function.

		{
			//13.6.3 Rvalue References and Member Functions

			//To prevent right-hand value assignment
			//We can use reference qualifier after the parameter list
			class Foo
			{
			public:
				Foo& operator=(const Foo&)&&
				{
					return *this;
				}
			};

			//The reference qualifier can be either & or &&, indicating that this may point to an rvalue or lvalue, respectively.

			//Overloading and Reference Functions

		}
	}
}