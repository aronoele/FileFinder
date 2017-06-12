#include <iostream>
#include <typeinfo> 
using namespace std;

#include "FileFinder.h"

int main(int argc, char* argv[])
{
	if (argc > 1) {
		FileFinder fileFinder(argv[1]);
		fileFinder.scan();
		fileFinder.saveToXml();
		fileFinder.search();
	}
	else {
		cout << "No path in the command line parameter" << endl;
	}

	return 0;
}