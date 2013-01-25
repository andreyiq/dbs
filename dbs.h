#include <string>
#include <fstream>

using namespace std;

class Script{
private:
	ifstream* file;	
	string currentString;
	string term;
	size_t posTerm;
public:
	string script;
	bool fetch(void);
	Script(const char* filename);
	~Script(void);
};
