#include "Quote.h"

double Bulk_Quote::net_price(std::size_t cnt) const
{
	if (cnt >= quantity_)
		return cnt * (1 - discount_) * price_;
	else
		return cnt * price_;
}

double If_Part_Over_Limit_Quote::net_price(std::size_t cnt) const
{
	if (cnt >= quantity_)
		return (cnt - quantity_) * price_ + quantity_ * (1 - discount_) * price_;
	else
		return cnt * (1 - discount_) * price_;
}

double Over_Limit_NoDisc_Quote::net_price(std::size_t cnt) const
{
	if (cnt >= quantity_)
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
