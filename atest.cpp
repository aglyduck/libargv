#include "argv.h"
#include <iostream>
using namespace std;

void test()
{
  int i;
	char buff[100] = ":/usr/bin::/usr/local/bin:";
	char **argv;
	int argc;
	
	cout << "=======" << endl;
	argc = makeargv(buff, ":", EMPTYTOKENS, &argv);
    cout << "argc:" << argc << endl;
	for (i = 0; i < argc; i ++){
		cout << argv[i] << endl;
	}
	cout << "=======" << endl;
}
int main()
{
	int i;
	char buff[100] = "Hello World";
	char **argv;
	int argc;
	
	argc = makeargv(buff, " ", NOTOKENS, &argv);
	for (i = 0; i < argc; i ++){
		cout << argv[i] << endl;
	}

	test();
	return 0;
}
