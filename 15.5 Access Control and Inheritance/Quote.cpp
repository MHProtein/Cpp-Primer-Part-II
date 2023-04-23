#include "Quote.h"

Quote::Quote(const Quote& q) :price_(q.price_), book_no_(q.book_no_)
{
}

Quote::Quote(Quote&& q) noexcept : book_no_(std::move(q.book_no_)), price_(std::move(q.price_))
{
}

Quote& Quote::operator=(const Quote& q)
{
	if (this->price_ != q.price_ && this->book_no_ != q.book_no_)
	{
		this->price_ = q.price_;
		this->book_no_ = q.book_no_;
	}
	return *this;
}

Quote& Quote::operator=(Quote&& q) noexcept
{
	if (this->price_ != q.price_ && this->book_no_ != q.book_no_) {
		this->price_ = std::move(q.price_);
		this->book_no_ = std::move(q.book_no_);
	}
	return *this;
}

std::pair<size_t, double> Disc_Quote::discount_policy() const
{
	return { quantity_, discount_ };
}

Bulk_Quote::Bulk_Quote(const Bulk_Quote& q) :Disc_Quote(q)
{
}

Bulk_Quote::Bulk_Quote(Bulk_Quote&& q) noexcept :Disc_Quote(std::move(q))
{
}

Bulk_Quote& Bulk_Quote::operator=(const Bulk_Quote& rhs)
{
	Disc_Quote::operator=(rhs);
	return *this;
}

Bulk_Quote& Bulk_Quote::operator=(Bulk_Quote&& rhs) noexcept
{
	Disc_Quote::operator=(std::move(rhs));
	return *this;
}

double Bulk_Quote::net_price(std::size_t cnt) const
{
	std::cout << "Bulk_Quote::net_price" << std::endl;
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