#ifndef WORD_QUERY_H
#define WORD_QUERY_H
#pragma once
#include "Query_base.h"

class Word_Query :public Query_base
{
	friend class Query;
	Word_Query(const std::string& s) :query_word_(s) {  }
	Query_Result eval(const Text_Query& t) const override { return t.query(query_word_); }
	std::string rep() const override { return query_word_; }
	std::string query_word_;
};
#endif

