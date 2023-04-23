#pragma once
#include <string>
#include <ostream>
#include <format>
#include <iostream>

class Quote
{
public:
	Quote() = default;
	Quote(const std::string& book, const double sales_price) :book_no_(book), price_(sales_price) {  }
	std::string isbn() const { return book_no_; }
	virtual double net_price(std::size_t n) const { return n * price_; }
	virtual ~Quote() = default;
	virtual void debug(std::ostream& os = std::cout);

private:
	std::string book_no_;
protected:
	double price_ = 0.0;};

//Member functions that are not declared as virtual are resolved at compile time, not run time.
//But virtual members are resolved at run time.
//Sometimes, a base class has members that it wants to let its derived classes use while prohibiting access to those same members by other users. So, we got protected.

class Disc_Quote :public Quote
{
public:
Disc_Quote() = default;
Disc_Quote(const std::string& book, double price, std::size_t qty, double disc) :Quote(book, price), quantity_(qty), discount_(disc) {  }
double net_price(std::size_t) const;
protected:
std::size_t quantity_ = 0;
double discount_ = 0.0f;
};


class Bulk_Quote :public Quote
{//When derivation is public, the public memebrs of the base class become part of the interface of the derived class as well.
public:
	Bulk_Quote() = default;
	Bulk_Quote(const std::string&, double, std::size_t);
	Bulk_Quote(const std::string book, double p, std::size_t qty, double disc) :Quote(book, p), min_qty_(p), discount_(disc) {  }
	//The base class is initialized first, and then the members of the derived class are initialized in the order in which they are declared in the class.
	//A derived class should respect the interfaces of its
	double net_price(std::size_t cnt) const override;
	void debug(std::ostream& os) override;

private:
	std::size_t min_qty_ = 0;
	double discount_ = 0.0;
};

double print_total(std::ostream& os, const Quote& item, size_t n);