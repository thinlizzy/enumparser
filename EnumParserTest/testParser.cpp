#include <tut.h>

#include "../src/Parser.h"
#include <sstream>

namespace {
    struct setup {
    	Parser parser;
    };
}

namespace tut {
	using std::istringstream;
	using std::ostringstream;

    typedef test_group<setup> tg;
    tg parser_test_group("Parser");

	typedef tg::object testobject;

    template<>
    template<>
    void testobject::test<1>()
    {
        set_test_name("load");

        istringstream input("enum EnumName { A, B  = 2,  C, };");
        parser.load(input);
        ensure_equals(parser.name,"EnumName");
        ensure_equals(parser.values.size(),3);
        ensure_equals(parser.values[0].name,"A");
        ensure_equals(parser.values[0].textValue,"A");
        ensure_equals(parser.values[0].numValue,"");
        ensure_equals(parser.values[1].name,"B");
        ensure_equals(parser.values[1].textValue,"B");
        ensure_equals(parser.values[1].numValue,"2");
        ensure_equals(parser.values[2].name,"C");
        ensure_equals(parser.values[2].textValue,"C");
        ensure_equals(parser.values[2].numValue,"");
    }

    template<>
    template<>
    void testobject::test<2>()
    {
        set_test_name("$NAME$");

        istringstream input("enum EnumName {};");
        istringstream templ("name = $NAME$");
        ostringstream output;
        parser.load(input);
        ensure_equals(parser.name,"EnumName");
        parser.parse(templ,output);
        ensure_equals(output.str(),"name = EnumName");
    }

    template<>
    template<>
    void testobject::test<3>()
    {
        set_test_name("enum values");

        istringstream input("enum EnumName { A, B  = 2,  C, };");
        istringstream templ(" name = $NAME$ $BEGIN_ENUM$$ENUM$ $VALUE$$NUMVALUE$ $END_ENUM$");
        ostringstream output;
        parser.load(input);
        parser.parse(templ,output);
        ensure_equals(output.str()," name = EnumName A A B B2 C C ");
    }
}
