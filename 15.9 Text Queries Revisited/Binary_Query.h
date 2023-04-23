#ifndef BINARY_QUERY_H
#define BINARY_QUERY_H
#pragma once
#include "Query.h"
#include "Query_base.h"

class Binary_Query :public Query_base
{
protected:
	Binary_Query(const Query& lhs, const Query& rhs, const std::string& op) :lhs_(lhs), rhs_(rhs), op_sym_(op) {  }
	std::string rep() const override { return "(" + lhs_.rep() + "" + op_sym_ + " " + rhs_.rep() + ")"; }
	Query lhs_, rhs_;
	std::string op_sym_;
};

#endif

