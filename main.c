#include <iostream>
#include "dbs.h"

int main(void)
{
	const char* filename = "./script.sql";
	Script script(filename);
	while(script.fetch()){
		std::cout << script.script << "\n";
	}
	return 0;
}
