#include <string>
#include <vector>
#include <memory>

#include "Sales_data.h"

//13.1.1 The Copy Constructor
class Foo
{
public:
	Foo(); //default constructor
	Foo(const Foo&); //copy constructor
	Foo& operator=(const Foo&);
};

class HasPtr
{
public:
	HasPtr(const std::string& s = std::string()) :ps(new std::string(s)) {}
	HasPtr(const HasPtr& rhs) :ps(new std::string(*rhs.ps)), i(rhs.i) {}
	bool operator==(const HasPtr& rhs) const
	{
		return (*this->ps == *rhs.ps) && (this->i == rhs.i);
	}
	HasPtr& operator=(const HasPtr& rhs)
	{
		if (rhs == *this)
			return *this;
		delete ps;
		this->ps = new std::string(*rhs.ps);
		this->i = rhs.i;
		return *this;
	}
	~HasPtr()
	{
		if (ps)
		{
			delete ps;
			ps = nullptr;
		}
	}
private:
	std::string* ps;
	int i;
};

class Employee
{
public:
	Employee()
	{
		identifier = std::to_string(std::stoull("152022000") + (ID++));
	}
	Employee(const std::string& Name) :name(Name)
	{
		identifier = std::to_string(std::stoull("152022000") + (ID++));
	}
	Employee(const Employee&) = delete;
	Employee& operator=(const Employee&) = delete;

private:
	static size_t ID = 0;
	std::string name;
	std::string identifier;
};

int main()
{
	std::string dots(10, '.'); //direct initialization
	std::string s(dots); //direct initialization
	std::string s2 = dots; //copy initialization
	std::string null_book = "9-999-99999-9"; //copy initialization
	std::string nines = std::string(100, '9'); //copy initialization
	//When we use direct initialization, we are asking the compiler to use ordinary function matching to select the constructor
	//When we use copy initialization, we are asking the compiler to copy the right-hand operand into the object being created, converting that operand if necessary.
	//When copy initialization happens, either the copy constructor or move constructor is required.
	//Copy initialization happens when:
	//1. we define variables using an =
	//2. pass an object as an argument to a parameter of nonreference type
	//3. return an object from a function that has a nonreference return type
	//4. brace initialize the elements in an array or the members of an aggregate class (struct)

	//the library containers copy initialize their elements when we initialize the container, or when we call an insert or push member. By contrast, elements created by an emplace member are directly initialized

	//Parameters and Return Values
	//The fact that the copy constructor is used to initialize nonreference parameters of class type explains why the copy constructor's own parameter must be a reference.
	//If that parameter were not a reference, then the call would never succeed------to call the copy constructor, we'd need to use the copy constructor to copy argument, but to copy the argument
	//, we'd need to call the copy constructor, and so no indefinitely

	//Contraints on Copy Initialization
	std::vector<int> v1(10);
	//std::vector<int> v2 = 10; //error: constructor that takes a size is explicit
	void f(std::vector<int>); //f's parameter is copy initialized
	//f(10); //error: can't use an explicit constructor to copy an argument
	f(std::vector<int>(10)); //of: directly construct a temporary vector from an int

	//The Compiler Can Bypass the Copy Constructor
	//The compiler is permitted to rewrite
	std::string null_book2 = "9-999-99999-9";
	//into
	//std::string null_book2("9-999-99999-9");

	//13.1.2 The Copy-Assignment Operator
	//assignment operators usually return a reference to their left-hand operand.
	//The library generally requires that types stored in a container have assignment operators that return a reference to the left-hand operand.

	//The Synthesized Copy-Assignment Operator
	//see it in Sales_data.h

	//13.1.3 The Destructor
	//The destructor operates inversely to the constructors: they do whatever word is needed to free the resources used by an object and destroy the nonstatic date members of the object
	//In a constructor, members are initialized before the function body is executed, and members are initialized in the same order as they appear in the class.
	//In a destructor, the function body is executed first and then the members are destroyed. Members are destroyed in reverse order from the oder in which they were initialized.
	//The implicit destruction of a member of built-in pointer type does not delete the object to which that pointer points
	//The smart pointers are class types and have destructors, as a result, members that are smart pointers are automatically destroyed during the destruction phase.

	//When a Destructor Is Called
	//The destructor is used automatically whenever an object of its type is destroyed:
	//1. Variables are destroyed when they go out of scope.
	//2. Members of an object are destroyed when the object of which they are a part is destroyed.
	//3. Elements in a container---whether a library container or an array---are destroyed when the container is destroyed.
	//4. Dynamically allocated objects are destroyed when the delete operator is applied to a pointer to the object.
	//5. Temporary objects are destroyed at the end of the full expression in which the temporary was created.

	{
		Sales_data* p = new Sales_data; //p is a built-in pointer
		auto p2 = std::make_shared<Sales_data>(); //p2 is a shared_ptr
		Sales_data item(*p); //copy constructor copies *p into item
		std::vector<Sales_data> vec; //local object
		vec.push_back(*p2); //copies the object to which p2 points
		delete p; //destructor called on the object pointed to by p
	}//exit local scope; destructor called on item, p2, and vec
	 //destroying p2 decrements its use count; if the count goes to 0, the object is freed.
	 //destroying vec destroys the elements in vec.

	//The destructor is not run when a reference or a pointer to an object goes out of scope

	//The Synthesized Destructor
	//The members are automatically destroyed after the (empty) destructor body is run. In particular, the string destructor will be run to free the memory used by the bookNo member.
	//It is important to realize that the destructor body does not directly destroy the members themselves. Members are destroyed as part of the implicit destruction phase that follows the
	//destructor body. A destructor body executes in addition to the memberwise destruction that takes place as part of destroying an object.

	//13.1.4 The Rule of Three/Five
	//RULE 1: Classes That Need Destructors Need Copy and Assignment
	//When you define a class needs to define its owen versions of the copy-control members is to decide first whether the class needs a destructor.
	//Often, the need for a destructor is more obvious than the ned for the copy constructor or assignment operator. If the class needs a destructor, it almost surely needs a copy
	//constructor and copy-assignment operator as well.

	//If in the HasPtr class, you didn't define your own version of copy constructor and copy-assignment operator, this will lead to a serious bug.
	//HasPtr f(HasPtr hp)  //HasPtr passed by value, so it is copied
	//{
	//	HasPtr ret = hp; //copies the given HasPtr
	//	return ret; //ret and hp are destroyed
	//}
	//the sp in ret will denote the same object as hp's, which means ret.sp will be destroyed as hp.sp going out of scope.
	HasPtr p("some value");
	//f(p);
	HasPtr q(p); //now both q and p point to invalid memory
	//If a class needs a destructor, it almost surely needs also both copy constructor and copy-assignment operator

	//RULE 2: Classes That Need Copy Need Assignment, and Vice Versa

	//13.1.5 Using =default
	class Sales_data2
	{
	public:
		Sales_data2() = default;
		Sales_data2(const Sales_data2&) = default;
		Sales_data2& operator=(const Sales_data2&);
		~Sales_data2() = default;
	};
	//Sales_data2& Sales_data2::operator=(const Sales_data2&) = default;
	//When we specify =default on the declaration of the member inside the class body, the synthesized function is implicitly inline(just as is any other member function defined in the body of the class)
	//If wo don't want the synthesized function to be an inline function, just specify =default on the member's definition.
	//We can use =default only on member functions that have a synthesized version

	//13.1.6 Preventing Copies
	//We can't prevent copies by not defining the copy-control members, because if we don't define them, the compiler will automatically synthesize them.

	//Defining af Function as Deleted
	struct NoCopy
	{
		NoCopy() = default;
		NoCopy(const NoCopy&) = delete;
		NoCopy& operator=(const NoCopy&) = delete;
		~NoCopy() = default;
	};
	//we can prevent copies by defining the copy constructor and copy-assignment operator as deleted functions
	//The =delete signals to the compiler(and to readers of our code) that we are intentionally not defining these members.
	//The =delete must appear on the first declaration of a deleted function.
	//A defaulted member affects only what code the compiler generates; hence the =default is not needed until the compiler generates code. On the other hand, the compiler needs to know that
	//a function is deleted in order to prohibit operations that attempt to use it.
	//We can specify =delete on any function. deleted functions are sometimes also useful when we wanna guide the function matching process.

	//The Destructor Should Not be a Deleted Member
	//The compiler will not let us define variables or create temporaries of a class that has a member whose type has a deleted destructor. If a member has a deleted destructor, then that
	//member cannot be destroyed. If a member can't be destroyed, the object as a whole can't be destroyed

	//The Copy-Control Members May Be Synthesized as Deleted
	//For Some Classes, the compiler defines these synthesized members as deleted functions:
	//1. The synthesized destructor is defined as deleted if the class has a member whose own destructor is deleted or is inaccessible.
	//2. The synthesized copy constructor is defined as deleted if the class has a member whose own copy constructor is deleted or inaccessible. It is also deleted
	//    if the class has a member with a deleted or inaccessible destructor
	//3. The synthesized copy-assignment operator is defined as deleted if a member has a deleted or inaccessible copy-assignment operator, or if the class has a const or reference member
	//4. The synthesized default constructor is defined as deleted if the class has a member with a deleted or inaccessible destructor; or has a reference member that does not have an in-class
	//    initializer; or has a const member whose type does not explicitly define a default constructor and that member does not have an in-class initializer

	//In essence, the copy-control members are synthesized as deleted when it is impossible to copy, assign, or destroy a member of the class

	//private Copy Control
	class PrivateCopy
	{
	private:
		//copy control is private and so is inaccessible to ordinary user code
		PrivateCopy(const PrivateCopy&);
		PrivateCopy& operator=(const PrivateCopy&);
	public:
		PrivateCopy() = default;
		~PrivateCopy();
	};
	//Because the destructor is public, users will be able to define PrivateCopy objects. However, friends and members can still make copies.
	//To prevent copies by friends and members, we declare these members as private but do not define them.

	//Classes that want to prevent copying should define their copy constructor and copy-assignment operators using =delete rather than making those members private
}