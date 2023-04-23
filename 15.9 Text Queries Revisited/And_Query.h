#ifndef AND_QUERY_H
#define AND_QUERY_H

#pragma once
#include "Binary_Query.h"

class And_Query :public Binary_Query
{
	friend Query operator&(const Query&, const Query&);
	And_Query(const Query& lhs, const Query& rhs) :Binary_Query(lhs, rhs, "&") {  }
	Query_Result eval(const Text_Query&) const override;
};

#endif
