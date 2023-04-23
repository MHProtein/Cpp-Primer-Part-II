#pragma once
#include <string>
#include <ostream>
#include <format>
#include <iostream>
#include <vector>

class Quote
{
public:
	Quote() = default;
	Quote(const std::string& book, const double sales_price) :book_no_(book), price_(sales_price) {  }
	Quote(const Quote&);
	Quote(Quote&&) noexcept;
	Quote& operator=(const Quote&);
	Quote& operator=(Quote&&) noexcept;
	std::string isbn() const { return book_no_; }
	virtual ~Quote() = default; //dynamic binding for the destructor.
	//virtual destructor is needed if a base pointer pointing to a derived object is deleted.
	virtual double net_price(std::size_t n) const
	{
		std::cout << "Quote::net_price" << std::endl;
		return n * price_;
	};
	virtual Quote* clone() const & { return new Quote(*this); }
	virtual Quote* clone() const&& { return new Quote(std::move(*this)); }
private:
	std::string book_no_;
protected:
	double price_ = 0.0;
};

//Member functions that are not declared as virtual are resolved at compile time, not run time.
//But virtual members are resolved at run time.
//Sometimes, a base class has members that it wants to let its derived classes use while prohibiting access to those same members by other users. So, we got protected.

class Disc_Quote :public Quote
{
public:
	Disc_Quote() = default;
	Disc_Quote(const std::string& book, double price, std::size_t qty, double disc) :Quote(book, price), quantity_(qty), discount_(disc) {  }
	virtual double net_price(std::size_t) const = 0;
	std::pair<size_t, double> discount_policy() const;
protected:
	std::size_t quantity_ = 0;
	double discount_ = 0.0f; 
};

class Bulk_Quote :public Disc_Quote
{//When derivation is public, the public memebrs of the base class become part of the interface of the derived class as well.
public:
	Bulk_Quote() = default;
	//The following is what the Bulk_Quote default constructor does:
	//1. It runs the Disc_Quote default constructor, which in turn run the Quote default constructor.
	//2. The Quote constructor default initializes the bookNo member and price to 0
	//3. When the Quote constructor finishes, the Disc_Quote continues to initialize qty and discount.
	//4. When the Disc_Quote constructor finishes, the Bulk_Quote constructor continues, but does no work.
	Bulk_Quote(const std::string book, double p, std::size_t qty, double disc) :Disc_Quote(book, p, qty, disc) {  }
	Bulk_Quote(const Bulk_Quote&);
	Bulk_Quote( Bulk_Quote&&) noexcept;
	Bulk_Quote& operator=(const Bulk_Quote&);
	Bulk_Quote& operator=( Bulk_Quote&&) noexcept;
	Bulk_Quote* clone() const& override { return new Bulk_Quote(*this); }
	Bulk_Quote* clone() const&& override { return new Bulk_Quote(std::move(*this)); }

	//Classes derived from Quote will automatically obtain synthesized move operations as well, unless they have members that otherwise preclude move.

	//The base class is initialized first, and then the members of the derived class are initialized in the order in which they are declared in the class.
	//A derived class should respect the interfaces of its
	double net_price(std::size_t cnt) const;

	//Each Bulk_Quote has a direct base class, Disc_Quote, and an indirect base class, Quote. Each Bulk_Quote object has three subobjects: an (empty) Bulk_Quote part,
	//a Disc_Quote subobject, and a Quote subobject.

	//Adding Disc_Quote to the Quote hierarchy is refactoring. 
};

class If_Part_Over_Limit_Quote :public Disc_Quote
{
public:
	If_Part_Over_Limit_Quote() = default;
	If_Part_Over_Limit_Quote(const std::string& book, double p, std::size_t qty, double disc) :Disc_Quote(book, p, qty, disc) {  }
	double net_price(std::size_t) const override;
};

class Over_Limit_NoDisc_Quote:public Disc_Quote
{
public:
	Over_Limit_NoDisc_Quote() = default;
	Over_Limit_NoDisc_Quote(const std::string& book, double p, std::size_t qty, double disc) :Disc_Quote(book, p, qty, disc) {  }
	double net_price(std::size_t) const override;
};

double print_total(std::ostream& os, const Quote& item, size_t n);

