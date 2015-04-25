#ifndef PARSER_H_ENUM_PARSER_2015_20_04
#define PARSER_H_ENUM_PARSER_2015_20_04

#include <iostream>
#include <string>
#include <vector>

class Parser {
public:
	Parser();
	explicit Parser(std::istream & enumStream);
	void load(std::istream & enumStream);
	void parse(std::istream & templateStream, std::ostream & output);

	struct Value {
		std::string name;
		std::string textValue;
		std::string numValue;
	};

	std::string name;
	typedef std::vector<Value> Values;
	Values values;
private:
	void do_load(std::istream & enumStream);
};

#endif
