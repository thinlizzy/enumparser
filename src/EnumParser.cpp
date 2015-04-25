#include <iostream>
#include <fstream>
#include <string>
#include "Parser.h"
using namespace std;

int main(int argc, char * argv[]) {
	if( argc < 2 ) {
		cerr << "usage EnumParser <enumfile> [templatefile [+]resultfile]..." << endl;
		return 1;
	}

	ifstream file(argv[1]);
	if( ! file ) {
		cerr << "can't open " << argv[1] << endl;
		return 1;
	}

	Parser parser(file);
	cout << "loaded " << argv[1] << endl;
	for( int a = 2; a+1 < argc; a+=2 ) {
		ifstream templateFile(argv[a], ios_base::in | ios_base::binary);
		string outputFile = argv[a+1];
		ios_base::openmode mode = ios_base::out | ios_base::binary;
		if( outputFile[0] == '+' ) {
			outputFile.erase(outputFile.begin());
			mode |= ios_base::app;
		} else {
			mode |= ios_base::trunc;
		}
		ofstream output(outputFile,mode);
		if( templateFile && output ) {
			cout << "parsing " << argv[a] << " into " << outputFile << endl;
			parser.parse(templateFile,output);
		}
	}
}
