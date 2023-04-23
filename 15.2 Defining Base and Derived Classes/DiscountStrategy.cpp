#include "DiscountStrategy.h"

discount_strategy::discount_strategy(const discount_strategy& strategy) :sold_qty_(new size_t(*strategy.sold_qty_)), price_(strategy.price_),
limit_(strategy.limit_), discount_rate_(strategy.discount_rate_)
{

}

discount_strategy& discount_strategy::operator=(const discount_strategy& strategy)
{
	if (sold_qty_)
	{
		delete this->sold_qty_;
	}
	sold_qty_ = new size_t(*strategy.sold_qty_);
	price_ = strategy.price_;
	limit_ = strategy.limit_;
	discount_rate_ = strategy.discount_rate_;
	return *this;
}

discount_strategy::~discount_strategy()
{
	if (sold_qty_)
	{
		delete sold_qty_;
		sold_qty_ = nullptr;
	}
}

double discount_strategy::new_order_created()
{
	if (!is_reached_limit())
		return price_ * (1 - discount_rate_);
	else
		return price_;
}

double discount_strategy::revenue()
{
	if (is_reached_limit())
		return (*sold_qty_ - limit_) * price_ + limit_ * (1 - discount_rate_) * price_;
	else
		return price_ * *sold_qty_;
}
