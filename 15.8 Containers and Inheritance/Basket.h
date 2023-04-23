#pragma once
#include <set>
#include <ostream>
#include <memory>
#include "\C++ Primer Part II\15.5 Access Control and Inheritance\Quote.h"

class Basket
{
public:
	void add_item(const Quote& sale) { items_.insert(std::shared_ptr<Quote>(sale.clone())); }
	void add_item(Quote&& sale) { items_.insert(std::shared_ptr<Quote>(std::move(sale).clone())); }

	double total_receipt(std::ostream&) const;
private:
	static bool compare(const std::shared_ptr<Quote>& lhs, const std::shared_ptr<Quote>& rhs) { return lhs->isbn() < rhs->isbn(); }
	std::multiset<std::shared_ptr<Quote>, decltype(compare)*> items_{ compare };
};
