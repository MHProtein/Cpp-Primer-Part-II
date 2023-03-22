#ifndef SALES_DATA_H
#define SALES_DATA_H
#pragma once
#include <string>
#include <istream>
#include <ostream>

class Sales_data
{
public://interfaces
    Sales_data();
    Sales_data(std::string BOOKNO, unsigned int UNIT_SOLD, double REVENUE) :bookNo(BOOKNO), unit_sold(UNIT_SOLD), revenue(REVENUE){}
    std::string isbn() const;//const member function
    //how isbn function is called
    //Sales_data::isbn(&sales_data)
    //The compiler passes the address of sales_data to implicit this parameter in isbn.
    //this is a const pointer, its value cannot be changed
    //const means this is pointing to a const.
    //the function is actually like this:
    //inline std::string isbn(const Sales_data* const this);

    Sales_data& combine(Sales_data& newData);
    friend Sales_data add(Sales_data& Data1, Sales_data& Data2);
    //If you declared a friend function, you sacrificed Encapsulation and maintainability//封装性与可维护性, in the meantime, you can access the private members of the class
    friend std::istream& read(std::istream& in, Sales_data& Data);
    friend std::ostream& print(std::ostream& out, const Sales_data& Data);

private://implement//实现
    double avg_price() const;

private:

    //The compiler will first compile member declarations then it will come to member functions

    std::string bookNo;
    unsigned int unit_sold;
    double revenue;
};

std::istream& read(std::istream& in, Sales_data& Data);
std::ostream& print(std::ostream& out, const Sales_data& Data);

//Benefits of Encapsulation
//User code cannot inadvertently//无意的 corrupt the state of an encapsulated object
//The implementation of an encapsulated class can change over time without requiring changes in user level-code //like you don't have to change the values of members or something
#endif
