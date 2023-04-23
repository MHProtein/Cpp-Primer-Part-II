#include "Quote.h"

double Bulk_Quote::net_price(std::size_t cnt) const
{
	if (cnt >= min_qty_)
		return cnt * (1 - discount_) * price_;
	else
		return cnt * price_;
}

double print_total(std::ostream& os, const Quote& item, size_t n)
{
	double ret = item.net_price(n);
	os << std::format("ISBN: {} # solds: {} total due: {}", item.isbn(), n, ret);
	return ret;
}
