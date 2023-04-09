#include "Quote.h"

double print_total(std::ostream& os, const Quote& item, size_t n)
{
	double ret = item.net_price(n);
	os << std::format("ISBN: {} # solds: {} total due: {}", item.isbn(), n, ret);
	return ret;
}
