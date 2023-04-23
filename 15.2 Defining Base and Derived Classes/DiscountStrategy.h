#pragma once
class discount_strategy
{
public:
	discount_strategy() :sold_qty_(new size_t(0)), price_(0.0), discount_rate_(0.0) {  }
	discount_strategy(double price, size_t limit, double discount) :sold_qty_(new size_t(0)), price_(price), limit_(limit), discount_rate_(discount) {  }
	discount_strategy(const discount_strategy&);
	discount_strategy& operator=(const discount_strategy&);
	~discount_strategy();
	double get_price() const { return price_; }
	void set_price(const size_t new_price) { price_ = new_price; }
	double get_discount_rate() const { return discount_rate_; }
	void set_discount_rate(const double new_rate) { discount_rate_ = new_rate; }
	bool is_reached_limit() { return *sold_qty_ >= limit_; }
	double new_order_created();
	double revenue();

private:
	size_t* sold_qty_;
	double price_;
	size_t limit_;
	double discount_rate_;
};
