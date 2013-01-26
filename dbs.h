#include <string>
#include <fstream>

using namespace std;

class Script{
private:
	ifstream* file;	
	string curStr;
	string term;
	size_t posTerm;
	bool checkTermAndCut(void);
	void changeTerm(void);
public:
	string script;
	bool fetch(void);
	Script(const char* filename);
	~Script(void);
};
