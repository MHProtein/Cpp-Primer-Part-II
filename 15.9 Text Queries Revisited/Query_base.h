#ifndef QUERY_BASE_H
#define QUERY_BASE_H
#pragma once
#include "Text_Query.h"

class Query_base
{
	friend class Query;
protected:
	using line_no = std::size_t;
	virtual ~Query_base() {}
private:
	virtual Query_Result eval(const Text_Query&) const = 0;
	virtual std::string rep() const = 0;
};

#endif

