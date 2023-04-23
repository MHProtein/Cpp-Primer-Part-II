#include <iostream>

#include "\C++ Primer Part II\15.5 Access Control and Inheritance\Quote.h"
#include <vector>
#include <memory>

int main()
{
	std::vector<Quote> basket;
	basket.push_back(Quote("201", 50));
	basket.push_back(Bulk_Quote("201-8", 50, 10, .25));
	//The derived objects are sliced down, their derived parts are ignored.

	//Put (Smart) Pointers, Not Objects, in Containers
	std::vector<std::shared_ptr<Quote>> ptr_basket;
	ptr_basket.push_back(std::make_shared<Quote>(Quote("201", 50)));
	ptr_basket.push_back(std::make_shared<Bulk_Quote>(Bulk_Quote("201-8", 50, 10, .25)));
	//We can convert derived type pointers to base type pointers
	std::cout << basket.back().net_price(15) << std::endl;
	std::cout << ptr_basket.back()->net_price(15) << std::endl;
}