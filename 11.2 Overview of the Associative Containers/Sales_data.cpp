#include "Sales_data.h"
#include <format>

Sales_data::Sales_data()
{
    this->bookNo = "Default_ISBN";
    this->unit_sold = 0;
    this->revenue = 0;
}

std::string Sales_data::isbn() const
{
        return this->bookNo;
}

double Sales_data::avg_price() const
{
    return this->revenue / this->unit_sold;
}

Sales_data& Sales_data::combine(Sales_data& newData)
{
        this->unit_sold += newData.unit_sold;
        this->revenue += newData.revenue;
        return *this;
}

Sales_data add(Sales_data& Data1, Sales_data& Data2)
{
    Sales_data sum = Data1;
    Data1.combine(Data2);
    return sum;
}

std::istream& read(std::istream& in,Sales_data& Data)
{
    double price = 0;
    in >> Data.bookNo >> Data.unit_sold >> price;
    Data.revenue = price * Data.unit_sold;
    return in;
}

std::ostream& print(std::ostream& out, const Sales_data& Data)
{
    out << std::format("The book's ISBN is {}, it has sold {} units, and its revenue is{}", Data.bookNo, Data.unit_sold, Data.revenue);
    return out;
}