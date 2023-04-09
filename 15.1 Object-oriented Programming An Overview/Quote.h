#pragma once
#include <string>

class Quote
{
public:
	std::string isbn() const;
	virtual double net_price(std::size_t n) const;
};

class Bulk_Quote :public Quote
{
public:
	double net_price(std::size_t n) const override;
};
