#pragma once
#include <string>
#include <ostream>
#include <format>

	class Quote
	{
	public:
		Quote() = default;
		Quote(const std::string& book, const double sales_price) :book_no_(book), price_(sales_price) {  }
		std::string isbn() const { return book_no_; }
		virtual double net_price(std::size_t n) const { return n * price_; }
		virtual ~Quote() = default;

	private:
		std::string book_no_;
	protected:
		double price_ = 0.0;
	};

	//Member functions that are not declared as virtual are resolved at compile time, not run time.
	//But virtual members are resolved at run time.
	//Sometimes, a base class has members that it wants to let its derived classes use while prohibiting access to those same members by other users. So, we got protected.


	class Bulk_Quote :public Quote
	{//When derivation is public, the public memebrs of the base class become part of the interface of the derived class as well.
	public:
		Bulk_Quote() = default;
		Bulk_Quote(const std::string&, double, std::size_t);
		double net_price(std::size_t n) const override;
		void whateverfunc(){}

	private:
		std::size_t min_qty = 0;
		double discount = 0.0;
	};

	double print_total(std::ostream& os, const Quote& item, size_t n);
