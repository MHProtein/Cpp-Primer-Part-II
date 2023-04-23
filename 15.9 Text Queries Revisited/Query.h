#ifndef QUERY_H
#define QUERY_H
#pragma once
#include <string>
#include <memory>
#include "Query_base.h"

class Query_base;

class Query
{
	friend Query operator~(const Query&);
	friend Query operator|(const Query&, const Query&);
	friend Query operator& (const Query&, const Query&);
	friend std::ostream& operator<<(std::ostream& os, const Query& q);

public:
	Query(const std::string& word);
	Query_Result eval(const Text_Query& t)const { return q_->eval(t); }
	std::string rep() const { return q_->rep(); }
	~Query() = default;

private:
	Query(std::shared_ptr<Query_base> query) :q_(query) {  }
	std::shared_ptr<Query_base> q_;
};

Query operator~(const Query&);
Query operator|(const Query&, const Query&);
Query operator& (const Query&, const Query&);
std::ostream& operator<<(std::ostream& os, const Query& q);

#endif
