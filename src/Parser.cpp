#include "Parser.h"
#include "Scanner.h"
#include <sstream>

Parser::Parser()
{
}

Parser::Parser(std::istream & enumStream)
{
	do_load(enumStream);
}

void Parser::load(std::istream & enumStream)
{
	values.clear();
	do_load(enumStream);
}

// TODO MAJOR BUG!!! need to ignore comments on source code
void Parser::do_load(std::istream & enumStream)
{
	// TODO find the correct expression for C++ identifiers
	Matcher identifier = Matcher("_$")
		.addRange('a','z')
		.addRange('A','Z')
		.addRange('0','9')
	;
	Matcher notAlpha = identifier.reverse();
	Matcher identifierOrClose = Matcher(identifier).addChar('}');
	Matcher valueDelims("=,}");
	Matcher enumDelims(",}");

	auto scanner = Scanner{enumStream};
	scanner.skipAfter("enum");
	scanner.skipUntil(identifier);
	name = scanner.extractUntil(notAlpha);
	scanner.skipAfter('{');
	char lastChar{};
	while( enumStream && lastChar != '}' ) {
		if( scanner.skipUntil(identifierOrClose) == '}' ) break;
		Value value;
		value.name = scanner.extractUntil(notAlpha);
		value.textValue = value.name;  // TODO add support for custom values
		lastChar = scanner.skipUntil(valueDelims);
		if( lastChar == '=' ) {
			scanner.skipUntil(identifier);
			value.numValue = scanner.extractUntil(notAlpha);
			lastChar = scanner.skipUntil(enumDelims);
		}
		values.push_back(value);
	}
}

void Parser::parse(std::istream & templateStream, std::ostream & output)
{
	// loop context vars
	bool inLoop = false; // TODO add support for nested loops (e.g: cartesian products, power sets, etc.)
	decltype(templateStream.tellg()) loopPos;
	Values::iterator cursor;

	auto delim = Matcher{'$'};
	auto scanner = Scanner{templateStream};
	while( templateStream ) {
		scanner.streamUntil(delim,output);
		if( ! templateStream ) break;

		templateStream.get();
		auto id = scanner.extractUntil(delim);
		templateStream.get();
		if( id.empty() ) {
			output << '$';
		} else
		if( id == "NAME" ) {
			output << name;
		} else
		if( id == "BEGIN_ENUM" ) {
			if( inLoop ) throw "nested loops shamefully not support yet";

			loopPos = templateStream.tellg();
			cursor = values.begin();
			if( cursor == values.end() ) {
				scanner.skipAfter("$END_ENUM$");  // this will change after nested loops is supported
			} else {
				inLoop = true;
			}
		} else
		if( id == "END_ENUM" ) {
			if( ! inLoop ) throw "loop ends with no beginning";

			++cursor;
			if( cursor == values.end() ) {
				inLoop = false;
			} else {
				templateStream.seekg(loopPos);
			}
		} else
		if( id == "ENUM" ) {
			if( inLoop ) {
				output << cursor->name;
			}
		} else
		if( id == "VALUE" ) {
			if( inLoop ) {
				output << cursor->textValue;
			}
		} else
		if( id == "NUMVALUE" ) {
			if( inLoop ) {
				output << cursor->numValue;
			}
		}
	}
}
