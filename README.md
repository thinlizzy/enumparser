# enumparser
a C++ enum parser application that generates code

usage EnumParser enumfile.h templatefile [+]generatedfile [templatefile [+]generatedfile]...

it will parse the first enum declaration from enumfile.h and then it generates a file based on a template file, 
by replacing tags with the enumeration values

All tags should be written between dollar signs. The templatefile currently supports the following tags:
- NAME - the enumeration type name
- BEGIN_ENUM - starts a loop with enum values 
- END_ENUM - ends a loop
- ENUM - the current enum identifier for the loop
- VALUE - same as above for now. it will be used for custom enum values
- NUMVALUE - the numerical value of the enum identifier when it is explictly assigned

# BUGS
- C++ comments can be parsed too :-(

# TODO
- support nested loops
- support custom enum text values
- ignore line break after BEGIN_ENUM and END_ENUM tags 
