#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <new>
#include <istream>

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

Foo* factory1(int n)
{
	return new Foo(n); //caller is responsible for deleting this memory
}

std::vector<int>* func1()
{
	return new std::vector<int>();
}

void func2(std::vector<int>* v,std::istream& os)
{
	int temp = 0;
	while (os >> temp)
		v->push_back(temp);
}

void func3(const std::vector<int>* v)
{
	for (const auto & num : *v)
	{
		std::cout << num << std::endl;
	}
}

std::shared_ptr<std::vector<int>> create(std::vector<int>::size_type length)
{
	return std::make_shared<std::vector<int>>(length);
}

void in(std::shared_ptr<std::vector<int>> v, std::istream& is = std::cin)
{
	int temp = 0;
	while (is >> temp)
	{
		v->push_back(temp);
	}
}

void print(const std::shared_ptr<std::vector<int>> v)
{
	for (const auto & num : *v)
	{
		std::cout << num << std::endl;
	}
}

struct connection
{
};
void disconnect(connection* p)
{
}

void end_connection(connection* p) { disconnect(p); }

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

	//12.1.2 Managing Memory Directly
	//Programs that use smart pointers are likely to be easier to write and debug.

	//Using new to Dynamically Allocate and Initialize Objects
	int* pi = new int; //pi points to a dynamically allocated unnamed, uninitialized int
	std::vector<int>* pv = new std::vector<int>{ 1,2,3,4,5,6,7,8,9 };

	//Dynamically Allocated const Objects
	const int* pci = new const int(1024);
	const std::string* ps = new const std::string;

	//Memory Exhaustion
	int* pp1 = new int; //if allocation fails, new throws std::bad_alloc
	int* pp2 = new (std::nothrow) int; //if allocation fails, new returns a null pointer
	//This form new is referred to as placement new. A placement new expression lets us pass additional arguments to new.
	//In this case, we pass an object named nothrow that is defined by the library. When we pass nothrow to new, we tell new that it must not throw an exception.
	//If this form of new is unable to allocate the requested storage, it will return a null pointer. Both bad_alloc and nothrow are defined in the new header

	//Freeing Dynamic Memory
	//In order to prevent memory exhaustion, we must return dynamically allocated memory to the system once we are finished using it.
	delete pp1; //p must point to a dynamically allocated object or be null pointer. Deleting a pointer to memory that was not allocated by new, or deleting the same pointer value more than once, is undefined:

	//Dynamically Allocated Objects Exist until They Are Freed
	auto ppp = factory1(12);
	delete ppp; //Don't forget to free ppp when finishing using it

	//Caution: Managing Dynamic Memory Is Error-Prone
	//Here are three common problems with using new and delete to manege dynamic memory:
	//1. Forgetting to delete memory. Neglecting to delete dynamic memory is known as a "memory leak," because the memory is never returned to the free store.
	//Testing for memory leaks is difficult because they usually cannot be detected until the application is run for a long enough time to actually exhaust memory.
	//2.Using an object after it has been deleted. This error can sometimes be detected by making the pointer null after the delete.
	//3.Deleting the same memory twice. This error can happen when two pointers address the same dynamically allocated object. If delete is applied to one of the pointers,
	//then the object's memory is returned to the free store. If we subsequently delete the second pointer, then the free store may be corrupted.
	//Better use smart pointers
	//After the deleting, the pointer becomes what is referred to as a dangling pointer. A dangling pointer is one that refers to memory that once held an object but no longer does.
	ppp = nullptr; //do remember to give a dangling pointer the value of nullptr
	//This indicates that the pointer no longer points to an object.

	//12.1.3 Using shard_ptrs with new
	std::shared_ptr<double> ppp1(new double(12.2121));

	//Other Ways to Define and Change shared_ptrs
	//shared_ptr<T> p(q) //p manages the object to which the built-in pointer q points; q must point to memory allocated by new and must be convertible to T*
	//shared_ptr<T> p(u) //p assumes ownership from the unique_ptr u; make u null.
	//shared_ptr<T> p(q, d) //p assumes ownership for the object to which the built-in pointer q points. q must be convertible to T*. p will use the callable object d in place of delete to free q.
	//p.reset() //If p is the only shared_ptr pointing at its object, reset frees p's existing object. If the optional built-in pointer q is passed, makes p point to q, otherwise makes p null.
	//p.reset(p) //If d is supplied, will call d to free q otherwise uses delete to free q.
	//p.reset(p, d)

	//Don't Mix Ordinary Pointers and Smart Pointers...
	//A shared_ptr can coordinate destruction only with other shared_ptrs that are copies of itself. So make_shared is recommended rather than new.
	//That way, we bind a shared_ptr to the object at the same time that we allocate it. There's no way to inadvertently bind the same memory to more than one independently created shared_ptr

	//void process(std::shared_ptr<int> ptr)
	//{
	//	   the argument to process is copied into ptr. Coping a shared_ptr increments its reference count. Thus, inside process the count is at least 2. When process completes, the reference count
	//  of ptr is decremented but cannot goto zero. Therefore, when the local variable ptr is destroyed, the memory to which ptr points will not be deleted.
	//}

	//It's dangerous to use a built-in pointer to access an object owned by a smart pointer, because we may not know when that object is destroyed/

	//...and Don't use get to Initialize or Assign Another Smart Pointer
	//The get function that returns a built-in type pointer that the smart pointer is managing is intended to be used when you can't use a shared_ptr.
	//The code that uses the return from get must not delete that pointer.
	std::shared_ptr<int> pa(new int(42));
	int* qa = pa.get();
	{
		//undefined: two independent shared_ptr point to the same memory
		std::shared_ptr<int>(q); 
	}//block ends, q is destroyed, and the memory tot which q points is freed.
	int foo = *p; //undefined, the memory to which p points was freed.

	//It is an error to bind another smart pointer to the pointer returned by get.
	//Use get only to pass access to the pointer to code that you know will not delete the pointer. In particular, never use get to initialize or assign to another smart pointer.

	//12.1.4 Smart Pointers and Exceptions
	//When an exception occurs, a smart pointer will free its memory automatically but memory that we manage directly won't.

	//Smart Pointers and Dumb//ÑÆ Classes
	//Classes that allocate resources--and that do not define destructors to free those resources------can be subject to the same kind of errors that arise when we use dynamic memory.
	//If an exception happens between when the resource is allocated and when it's freed, the program will leak that resource.

	//Using Our Own Deletion Code
	connection cnt;
	std::shared_ptr<connection> pconnect(&cnt, [](connection* p) {disconnect(p); });
	pconnect.reset();
	//When pconnect is destroyed, pconnect will call end_connection. In turn, end_connection will call disconnect, thus ensuring that the connection is closed.

	//Caution: Smart Pointer Pitfalls
	//1. Don't use the same built-in pointer to initialize or reset more than one smart pointer
	//2. Don't delete the pointer returned from get()
	//3. Don't use get() to initialize or reset another smart pointer
	//4. If you use a pointer returned by get(), remember that the pointer will become invalid when the last corresponding smart pointer goes away.
	//5. If you use a smart pointer to manage a resource other than memory allocated by new, remember to pass a deleter.

	//12.1.5 unique_ptr
	//A unique_ptr "owns" the object to which it points. Unlike shared_ptr, only one unique_ptr at a time can point to a given object. The object to which a unique_ptr points is destroyed when the unique_ptr is destroyed.
	std::unique_ptr<int> a = std::make_unique<int>(10);
	std::unique_ptr<double> up1;
	std::unique_ptr<int> up2(new (std::nothrow) int(2));
	//std::unique_ptr<int> up3(up2); error: no copy and assign for unique_ptr

	//Tho we can't copy or assign a unique_ptr, we can transfer ownership from one (non const) unique_ptr,  to another by calling release or reset:
	std::unique_ptr<int> up4(up2.release()); //release makes up2 null
	std::unique_ptr<int> up5(new (std::nothrow) int(12));
	up5.reset(up4.release()); //use the pointer up4 manages to reset up5
}
