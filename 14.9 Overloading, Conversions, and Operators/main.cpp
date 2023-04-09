#include <stdexcept>

int main()
{
	//14.9.1 Conversion Operators
	//operator type() const;
	//Conversion operators have no explicit stated return type and no parameters, and they must be defined as member functions.
	//Conversion operations ordinarily shouldn't change the object they are converting. As a result, conversion operators usually should be defined as const members.

	//Defining a Class with a Conversion Operator
	class smallInt
	{
	public:
		smallInt(int i=0):val_(i)
		{
			if (i < 0 || i>255)
				throw std::out_of_range("Bad SmallInt value");
		}
		operator int() const { return val_; }
	private:
		size_t val_;
	};

	smallInt si;
	si = 4; //implicitly convert si to int
	si + 3; //implicitly convert si to int
	//an implicit user-defined conversion can be preceded or followed by a followed by a standard conversion.
	smallInt si2 = 3.14; //double->int
	si + 3.14;//si->int->double

	//Conversion Operators Can Yield Surprising Results
	//It is not uncommon for classes to define conversions to bool

	//explicit Conversion Operators
	{
		class smallInt
		{
		public:
			smallInt(int i = 0) :val_(i)
			{
				if (i < 0 || i>255)
					throw std::out_of_range("Bad SmallInt value");
			}
			explicit operator int() const { return val_; }
		private:
			size_t val_;
		};

		smallInt si = 3; //ok: the SmallInt constructor is not explicit
		//si + 3; //error: implicit is conversion required, but operator int is explicit
		static_cast<int>(si) + 3; //ok

		//An explicit conversion will be used implicitly to convert an expression used as
			//The condition of an if, while, or do statement
			//The condition expression in a for statement header
			//An operand to the logical NOT, OR, or AND operators
			//The condition expression in a conditional operator

		//Conversion to bool is usually intended for use in conditions, as a result, operator bool ordinarily should be defined as explicit
	}

	//14.9.2 Avoid Ambiguous Conversions
	//Ordinarily, it's a bad idea to define classes with mutual conversions or to define conversions to or from two arithmetic types

	//Argument Matching and Mutual Conversions
	//rule: With the exception of an explicit conversion to bool, avoid defining conversion functions and limit nonexplicit constructors to those that are "obviously right".

	//Conversion Order
	//1. Precise Matching
	//2. const Conversion
	//3. Promotion
	//4. Arithmetic Conversion
	//5. class Type Conversion

	//13.9.3 Function Matching and Overloaded Operators
}