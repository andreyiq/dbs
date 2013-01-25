#include "dbs.h"

using namespace std;

Script::Script(const char* filename){
	file = new ifstream(filename);
	posTerm = string::npos;
	term = ";";
	currentString = "";
	script = "";
}

Script::~Script(void){
	if(file->is_open()){
		file->close();
	}
	delete file;
}

bool Script::fetch(void){
	if(file->eof()){
		return false;
	}
	script.clear();
	while((!file->eof())&&(posTerm==string::npos)){
		getline(*file, currentString);
		posTerm = currentString.find(term);
		if(posTerm!=string::npos){
			script += currentString.substr(0, posTerm + 1) + "\n";
		}else{
			script += currentString + "\n";
		}
	}

	posTerm = string::npos;

	return true;
}
