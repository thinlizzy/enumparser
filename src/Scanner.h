#ifndef SCANNER_H_ENUM_PARSER_2015_04_24
#define SCANNER_H_ENUM_PARSER_2015_04_24

#include <iostream>
#include <string>
#include <functional>
#include "Matcher.h"

class Scanner {
	std::istream & is;
public:
	Scanner(std::istream & is);
	char skipUntil(Matcher const & matcher);
	void skipAfter(char ch);
	void skipAfter(std::string const & word);
	std::string extractUntil(Matcher const & matcher);
	void streamUntil(Matcher const & matcher, std::ostream & os);
private:
	void doUntil(Matcher const & matcher, std::function<void(char)> before, std::function<void(char)> after);
};

#endif
