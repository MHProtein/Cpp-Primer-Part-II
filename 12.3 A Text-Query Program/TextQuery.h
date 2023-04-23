#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <set>
#include <sstream>
#include <memory>
#include <algorithm>
#include <iostream>

using line_no = std::vector<std::string>::size_type;
class QueryResult;

class TextQuery
{
public:
	TextQuery() = default;
	TextQuery(std::ifstream&);
	auto query(const std::string&) const;

private:
	std::shared_ptr<std::vector<std::string>> file;
	std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};

class Query_Result	
{
public:
	friend std::ostream& print(std::ostream& os, const QueryResult&);
	auto begin() const;
	auto end() const;
	auto getfile() const;
	Query_Result(std::string s, std::shared_ptr<std::set<line_no>> p, std::shared_ptr<std::vector<std::string>> f) :sought(s), lines(p), file(f){}
private:
	std::string sought;
	std::shared_ptr<std::set<line_no>> lines;
	std::shared_ptr<std::vector<std::string>> file;
};

std::ostream& print(std::ostream& os, const QueryResult&);