#include <iostream>
#include "dbs.h"

using namespace std;

Script::Script(const char* filename){
	file = new ifstream(filename);
	posTerm = string::npos;
	term = ";";
	curStr = "";
	script = "";
}

Script::~Script(void){
	if(file->is_open()){
		file->close();
	}
	delete file;
}

bool Script::fetch(void){
	if(!file->good()){
		return false;
	}
	script.clear();
	posTerm = string::npos;
	if(checkTermAndCut()){
		return !script.empty();
	}
	while(!file->eof()){
		getline(*file, curStr);
		if(curStr.empty()){
			continue;
		}
		if(checkTermAndCut()){
			return !script.empty();
		}
		script += curStr + "\n";
		curStr.clear();
	}
	return !script.empty();
}

bool Script::checkTermAndCut(void){
	posTerm = curStr.find(term);
	if(posTerm != string::npos){
		int scriptLen = posTerm + term.length();
		script += curStr.substr(0, scriptLen);
		changeTerm();
		curStr = curStr.substr(scriptLen, curStr.length() - scriptLen);
		return true;
	}else{
		return false;
	}
}

void Script::changeTerm(void){
	const string strSetTerm = "SET TERM";
	int posSetTerm = curStr.find(strSetTerm);
	if(posSetTerm < posTerm){
		int posNewTerm = posSetTerm + strSetTerm.length() + 1;
		int newTermLen = posTerm - posNewTerm - 1;
		string newTerm = curStr.substr(posNewTerm, newTermLen);
		if(!newTerm.empty()){
			term = newTerm;
		}
	}
}
