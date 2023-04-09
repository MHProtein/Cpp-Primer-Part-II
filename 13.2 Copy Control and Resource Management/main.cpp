#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

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
		auto newp = new std::string(*rhs.ps);
		delete ps;
		this->ps = newp;
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

class StrBlob
{
public:
	StrBlob() = default;
	StrBlob(const StrBlob& ini) :sp(std::make_shared<std::vector<std::string>>(*ini.sp)) {  }
	StrBlob& operator=(const StrBlob& rhs)
	{
		auto newptr = std::make_shared<std::vector<std::string>>(*rhs.sp);
		delete sp;
		sp = newptr;
		return *this;
	}
private:
	std::shared_ptr<std::vector<std::string>> sp;
	void checked(size_t i, std::string msg)
	{
		if (i >= sp->size())
			throw std::out_of_range(msg);
	}
};

class TreeNode
{
public:
	TreeNode() :value(std::string()), count(new int(1)), left(nullptr), right(nullptr) {  }
	TreeNode(const TreeNode& ini) :value(ini.value), left(ini.left), right(ini.right) { ++* count; }
	TreeNode& operator=(const TreeNode& rhs)
	{
		++* rhs.count;
		if(--*count==0)
		{
			delete left; delete right; delete count;
		}
		left = rhs.left; right = rhs.right; count = rhs.count;
		return *this;
	}
private:
	std::string value;
	int* count;
	TreeNode* left;
	TreeNode* right;
};

class BinStrTree
{
public:
	BinStrTree() :root(new TreeNode()) {  }
	BinStrTree(const BinStrTree& ini) :root(new TreeNode(*ini.root)) {  }
	BinStrTree& operator=(const BinStrTree& rhs)
	{
		auto newp = new TreeNode(*rhs.root);
		delete root;
		root = newp;
		return *this;
	}
private:
	TreeNode* root;
};

int main()
{
	//13.2.1 Classes That Act Like Values
	//To implement valuelike behavior HasPtr needs:
	//1. A copy constructor that copies the string, not just the pointer
	//2. A destructor to free the string
	//3. A copy-assignment operator to free the object's existing string and copy the string from its right-hand operand
	class HasPtrValuelike
	{
	public:
		HasPtrValuelike(const std::string& s = std::string()) :ps_(new std::string(s)), i_(0) {  }
		HasPtrValuelike(const HasPtrValuelike& p) :ps_(new std::string(*p.ps_)), i_(p.i_) {  }
		HasPtrValuelike& operator=(const HasPtrValuelike& p)
		{
			auto newp = new std::string(*p.ps_);
			delete ps_;
			ps_ = newp;
			i_ = p.i_;
			return *this;
		}
		~HasPtrValuelike() { delete ps_; }
	private:
		std::string* ps_;
		int i_;
	};
	//There are two points to keep in mind when you write an assignment operator:
	//Assignment operators must work correctly if an object is assigned to itself
	//Most assignment operators share work with the destructor and copy constructor
	//A good pattern to use when you write an assignment operator is to first copy the right-hand operand into a local temporary. After the copy is done, it is safe to destroy the existing
	//members of the left-hand operand. Once the left-hand operand is destroyed, copy the data from the temporary into the members of the left-hand operand

	//13.2.2 Defining Classes That Act Like Pointers
	//The easiest way to make a class act like a pointer is to use shared_ptrs to manage resources in the class.

	//Reference Counts
	//Reference Counting as follows:
		//1. In addition to initializing the object, each constructor (other than the copy constructor) creates a counter. This counter will keep track of how many objects share state with the object
	//we are creating. When we create an object, there is only one such object, so we initialize the counter to 1.
		//2. The copy constructor does not allocate a new counter; instead, it copies the data members of its given object, including the counter. The copy constructor increments this shared counter,
	//indicating that there is another user of that object's state
		//3. The destructor decrements the counter, indicating that there is one less user of the shared state. If the count goes to zero, the destructor deletes that state
		//4. The copy-assignment operator increments the right-hand operand's counter and decrements the counter of the left-hand operand. If the counter for the left-hand operand goes to
	//zero, there are not more users. In this case, the copy-assignment operator must destroy the state of the left-hand operand.

	//One way to solve the where-to-place-reference-count problem is to store the counter in dynamic memory. When we create an object, we'll also allocate a new counter.

	//Defining a Reference-Counted Class
	class HasPtrPointerlike
	{
	public:
		HasPtrPointerlike(const std::string& s = std::string()) :ps_(new std::string(s)), i_(0), use_(new std::size_t(1)) {  }
		HasPtrPointerlike(const HasPtrPointerlike& p) :ps_(p.ps_), i_(p.i_) { ++* use_; }
		HasPtrPointerlike& operator=(const HasPtrPointerlike& rhs)
		{
			++* rhs.use_;
			if (-- * use_ == 0)
			{
				delete ps_;
				delete use_;
			}
			ps_ = rhs.ps_;
			i_ = rhs.i_;
			use_ = rhs.use_;
			return *this;
		}
		~HasPtrPointerlike()
		{
			if (-- * use_ == 0)
			{
				delete ps_;
				delete use_;
			}
		}

	private:
		std::string* ps_;
		int i_;
		std::size_t* use_;
	};
}