#ifndef TEXT_QUERY_H
#define TEXT_QUERY_H
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
#include "DebugDelete.h"

using line_no = std::vector<std::string>::size_type;

class Query_Result
{
public:
	friend std::ostream& print(std::ostream& os, const Query_Result&);
	auto begin() const { return lines->begin(); }
	auto end() const { return lines->end(); }
	auto get_file() const { return file; }
	Query_Result(std::string s, std::shared_ptr<std::set<line_no>> p, std::shared_ptr<std::vector<std::string>> f) :sought(s), lines(p), file(f) {}
	~Query_Result() = default;
private:
	std::string sought;
	std::shared_ptr<std::set<line_no>> lines;
	std::shared_ptr<std::vector<std::string>> file;
};

std::ostream& print(std::ostream& os, const Query_Result&);


class Text_Query
{
public:
	Text_Query() = default;
	Text_Query(std::ifstream& ifs) :file(new std::vector<std::string>)
	{
		std::string text;
		while (std::getline(ifs, text))
		{
			file->push_back(text);
			int n = file->size() - 1;
			std::istringstream line(text);
			std::string word;
			while (line >> word)
			{
				auto& lines = wm[word];
				if (!lines)
					lines.reset(new std::set<line_no>);
				lines->insert(n);
			}
		}
	}
	auto query(const std::string& sought) const
	{
		static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);
		auto loc = wm.find(sought);
		if (loc == wm.end())
			return Query_Result(sought, nodata, file);
		else
			return Query_Result(sought, loc->second, file);
	}
	~Text_Query() = default;

private:
	std::shared_ptr<std::vector<std::string>> file;
	std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};


#endif
