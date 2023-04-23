#ifndef NOT_QUERY_H
#define NOT_QUERY_H
#pragma once
#include "Query.h"

class Not_Query :public Query_base
{
	friend Query operator~(const Query&);
	Not_Query(const Query& q) :query_(q) {  }
	std::string rep() const override { return "~(" + query_.rep() + ")"; }
	Query_Result eval(const Text_Query&) const override;
	Query query_;
};
#endif



