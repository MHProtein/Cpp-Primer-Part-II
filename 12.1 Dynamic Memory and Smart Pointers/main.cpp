#include <vector>
#include <string>
#include <iostream>
#include <memory>

//The library defines two kinds of smart pointers that differ in how they manage their underlying pointers:
//shared_ptr, which allows multiple pointers to refer to the same object
//unique_ptr, which "owns" the object to which it points
//weak_ptr, which is a weak reference to an object managed by a shared_ptr.

template<class T>
class Blob
{
	
};

struct Foo
{
	Foo(int x)
	{
		n = x;
	}
	int n;
}; 

std::shared_ptr<Foo> factory(int n)
{
	return std::make_shared<Foo>(n);
	//Since factory returns a shared_ptr, we can be sure that the object allocated by factory will be freed when appropriate.
}

void use_factory(int n)
{
	std::shared_ptr<Foo> p = factory(10);
} //p goes out of scope; the memory to which p points is automatically freed
//Because p is local to p. When use_factory ends, it will be automatically destroyed. And when it's destroyed, its reference count will be decremented and checked.
//In this case, p is the only object referring to the memory returned by factory. The reference count will be 0, and the object to which p points will be destroyed and the memory in which that
//object resides will be freed.

int main()
{
	//12.1.1 The shared_ptr Class
	std::shared_ptr<std::string> p1;
	std::shared_ptr<std::vector<int>> p2;
	//a default initialized smart pointer holds a null pointer.
	if(p1&&p1->empty())
	{
		*p1 = "hi";
	}

	//operations that are common to shared_ptr and unique_ptr
	//shared_ptr<T> sp  //Null smart pointer that can point to objects of type T
	//unique_ptr<T> up
	//p; //Use p as a condition; true if p points to an object
	//*p; //Dereference p to get the object to which p points
	//p->mem
	//p.get() //Returns the pointer in p. Use with caution; the object to which the returned pointer points will disappear when the smart pointer deletes it.
	//swap(p,q)   or   p.swap(q)  //Swaps the pointers in p and q

	//Operations Specific to shared_ptr
	//make_shared<T>(args)  //Returns a shared_ptr pointing to a dynamically allocated object of type T. Use args to initialize that object
	//shared_ptr<T> p(q)  //p is a copy of the shared_ptr q; increments the count in q. The pointer in q must be convertible to T*.
	// p = q;  //p and q are shared_ptrs holding pointers that can be converted to one another. Decrement p's reference count and increments q's count
					//deletes p's existing memory if p's count goes to 0
	//p.unique() //Returns true if p.use_count() is one; false otherwise.
	//p.use_count() //Returns the number of objects sharing with p; may be a slow operation, intended primarily for debugging purposes.

	//The make_shared Function
	//The safest way to allocate and use dynamic memory is to call a library function named make_shared. This function allocates and initializes an object in dynamic memory
	//and returns a shared_ptr that points to that object.
	std::shared_ptr<int> p3 = std::make_shared<int>(42);
	std::shared_ptr<std::string> p4 = std::make_shared<std::string>(10, '9');
	std::shared_ptr<int> p5 = std::make_shared<int>();
	auto p6 = std::make_shared<std::vector<int>>();

	//Coping and Assigning shared_ptrs
	auto p = std::make_shared<int>(42);
	auto q(p); //p and q point to the same object
											//object to which p and q point has two users
	//We can think of a shared_ptr as if it has an associated counter, usually referred to as a reference count. Whenever we copy a shared_ptr, the count is incremented.
	//For example, the counter associated with a shared_ptr, the count is incremented when we use it ro initialize another shared_ptr, when we use it as
	//the right-hand operand of an assignment, or when we pass it to or return it from a function by the value.
	//The counter is decremented when we assign a new value to the shared_ptr and when the shared_ptr itself is destroyed, such as when a local shared_ptr goes out of scope
	//Once a shared_ptr's counter goes to zero, the shared_ptr automatically frees the object that it manages.

	auto r = std::make_shared<int>(42);
	r = q; //assign to r, making it point to a different address
			// increase the use count for the object to which q points
			//reduce the use count of the object to which r had pointed
			//the object r had pointed to has no users; that object is automatically freed

	//It is up to implementation whether to use a counter or another data structure to keep track of how many pointers share state. The key point is that the class keeps track of how many
	//shared_ptrs point to the same object and automatically frees that object when appropriate.

	//shared_pointer Automatically Destroy Their Objects...
	//When the last shared_ptr pointing to an object is destroyed, the shared_ptr class automatically destroys the object to which that shared_ptr points. It does so through another
	//special member function known as a destructor.
	//Analogous to ite constructors, the destructor controls what happens when objects of that class type are destroyed.
	//The destructor for shared_ptr decrements the reference count of the object to which that shared_ptr points. If the count goes to zero, the shared_ptr destructor destroys the object
	//to which the shared_ptr points and frees the memory used by that object.

	//...and Automatically Free the Associated Memory
	//The fact that the shared_ptr class automatically frees dynamic objects when they no longer needed makes it fairly easy to use dynamic memory.

	//If you put shared_ptrs in a container, and you subsequently need to use some, but not all, of the elements, remember to erase the elements you no longer use.

	//Classes with Resources That Have Dynamic Lifetime
	//Program tend to use dynamic memory for one of three purposes:
	//1. They don't know how many objects they'll need
	//2. They don't know the precise type of the objects they need
	//3. They want to share data between several objects

	std::vector<std::string> v1;
	{
		std::vector<std::string> v2 = { "a","an","the" };
		v1 = v2;
	}//v2 is destroyed, which destroys the elements in v2
	//v1 has three elements, which are copies of the ones originally in  v2
}