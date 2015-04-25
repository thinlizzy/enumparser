#include "Scanner.h"

Scanner::Scanner(std::istream & is):
	is(is)
{
}

auto noOp = [](char ch){};

char Scanner::skipUntil(Matcher const & matcher)
{
	char result{};
	doUntil(matcher, [&result](char ch){ result = ch; }, noOp);
	return result;
}

std::string Scanner::extractUntil(Matcher const & matcher)
{
	std::string result;
	doUntil(matcher, noOp, [&result](char ch){ result.push_back(ch); });
	return result;
}

void Scanner::streamUntil(Matcher const & matcher, std::ostream & os)
{
	doUntil(matcher, noOp, [&os](char ch){ os.put(ch); });
}

void Scanner::doUntil(Matcher const & matcher, std::function<void(char)> before, std::function<void(char)> after)
{
	if( ! is ) return;

	int g;
	while( (g = is.get()) != std::istream::traits_type::eof() ) {
		char ch = g;
		before(ch);
		if( matcher.matches(ch) ) {
			is.putback(ch);
			break;
		}
		after(ch);
	}
}

void Scanner::skipAfter(char ch)
{
	if( ! is ) return;

	int g;
	do {
		g = is.get();
	} while( g != std::istream::traits_type::eof() && g != ch );
}

void Scanner::skipAfter(std::string const & word)
{
	bool notFound = true;
	while( is && notFound ) {
		skipAfter(word[0]);
		notFound = false;
		for( size_t c = 1; c != word.size(); ++c ) {
			if( is.peek() != word[c] ) {
				notFound = true;
				break;
			}
			is.get();
		}
	}
}

