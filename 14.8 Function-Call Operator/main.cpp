#include <iostream>
#include <istream>
#include <ostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>

struct absInt
{
	int operator()(int val) const
	{
		return val < 0 ? -val : val;
	}
};

class PrintString
{
public:
	PrintString(std::ostream& os = std::cout, char c = ' ') :os_(os), sep_(c) {  }
	void operator()(const std::string& s) const { os_ << s << sep_; }

private:
	std::ostream& os_;
	char sep_;
};

class ReadString
{
public:
	ReadString(std::istream& is) :is_(is) {  }
	void operator()(std::string& s)
	{
		if (is_) {
			std::cin >> s;
		}
	}
private:
	std::istream& is_;
};

struct isEqual
{
	template<class T>
	bool operator()(T& lhs, T& rhs)
	{
		return lhs == rhs;
	}
};

struct IfThenElse
{
	template<class T1,class T2>
	auto operator()(T1 expr1,T2 expr2,T2 expr3)
	{
		if (expr1)
			return expr2;
		return expr3;
	}
};

class isSizeInRange
{
public:	
	isSizeInRange(const size_t& min, const size_t& max) :min_(min), max_(max) {  }
	bool operator()(const std::string& s)
	{
		return s.size() >= min_ && s.size() <= max_;
	}
private:
	size_t min_;
	size_t max_;
};

void practice(std::ifstream& ifs)
{
	size_t cnt = 0;
	std::string line;
	isSizeInRange is_size_in_range(1, 10);
	std::map<size_t, size_t> size_count;
	while (std::getline(ifs,line))
	{
		std::istringstream strm(line);
		std::string word;
		while (ifs >> word)
		{
			if (is_size_in_range(word)) 
			{
				++cnt;
				++size_count[word.size()];
			}
		}
	}
}

int add(int lhs, int rhs)
{
	return lhs + rhs;
}

struct div
{
	int operator()(int lhs, int rhs) const
	{
		return lhs / rhs;
	}
};

void calculator(std::map<std::string, std::function<int(int, int)>>& binops_improved)
{
	while (true)
	{
		std::string expr;
		std::cin >> expr;
		auto op = std::find_if(expr.cbegin(), expr.cend(), [](const char s) {return s == '+' || s == '-' || s == '*' || s == '/' || s == '%'; });
		if (op != expr.cend())
		{
			auto lhs = std::stoi(expr.substr(0, op - expr.cbegin()));
			auto rhs = std::stoi(expr.substr((op - expr.cbegin()) + 1));
			std::string opr;
			opr.push_back(*op);
			std::cout << binops_improved[opr](lhs, rhs) << std::endl;
		}
	}
}

int main()
{
	int i = -42;
	absInt absObj;
	int ui = absObj(-42);
	PrintString errors(std::cerr, '\n');
	std::vector<std::string> vs{ "1","2","3","4","5" };
	std::for_each(vs.cbegin(), vs.cend(), PrintString(std::cerr, '\n'));
	IfThenElse ite;
	std::cout << ite(1, "hi", "bye") << std::endl;
	std::for_each(vs.cbegin(), vs.cend(), isEqual());

	//14.8.1 Lambdas Are Function Objects
	//14.8.2 Library-Defined Functions Objects
	std::plus<int>; std::minus<int>; std::multiplies<int>; std::divides<int>; std::modulus<int>; std::equal_to<int>;
	std::not_equal_to<int>; std::greater<int>; std::less<int>; std::logical_and<int>;
	std::vector<std::string*> vp;
	//library guarantees that less on pointer types is well defined
	std::sort(vp.begin(), vp.end(), std::less<std::string*>());

	//14.8.3 Callable Objects and function
	//Two callable objects may share the same call signature. A call signature corresponds to a function type
	//int (int, int)

	//Different Types Can Have the Same Call Signature
	//We might wanna use these callables to build a simple dest calculator. To do so, we'd want to define a function table to store "pointers" to these callables.\
	//When the program needs to execute a particular operation, it will look in the table to find which function to call.
	auto mod = [](int lhs, int rhs) {return lhs % rhs; };
	std::map<std::string, int(*)(int, int)> binops;
	binops.insert({ "+", add });
	//binops.insert({ "%",mod }); //The problem is that mod is a lambda, and each lambda has its own class type. That type does not match the type of the values stored in binops

	//The Library function Type
	std::function<int(int, int)> ff; //f is a null function object can store callable objects with a call signature that is equivalent to the function type int (int, int)
	std::function<int(int, int)>ff2(add); //stores a copy of the callable object in f3
	ff; //use f as a condition, true if f holds a callable object; false otherwise.
	ff2(1, 2); //Calls the object in f passing args.

	std::function<int(int, int)> f1 = add;
	std::function<int(int, int)> f2 = div::div();
	std::function<int(int, int)> f3 = mod;
	std::function<int(int, int)> f4 = [](int lhs, int rhs) {return lhs * rhs; };
	std::map<std::string, std::function<int(int, int)>> binops_improved
	{
		{"+",add},
		{"-",std::minus<int>()},
		{"*",[](int lhs,int rhs) {return lhs * rhs; }},
		{"/",div::div()},
		{"%",mod}
	};
}