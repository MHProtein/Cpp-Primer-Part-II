#include "Basket.h"

double Basket::total_receipt(std::ostream& os) const
{
	double sum = 0.0;
	for (auto iter = items_.cbegin(); iter != items_.cend(); iter = items_.upper_bound(*iter))
	{
		sum += print_total(os, **iter, items_.count(*iter));
	}
	os << "Total Sales: " << sum << std::endl;
	return sum;
}