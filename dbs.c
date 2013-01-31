#include <iostream>
#include <fstream>
#define IBPP_LINUX
#include <ibpp/all_in_one.cpp>
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

//=========================================================================
// Database
//=========================================================================

bool Database::disconnect(void){
	try{
		if(db->Connected()){
			db->Disconnect();
			connected = false;
		}
	}
	catch(IBPP::Exception& e){
		return false;
	}
	return true;
}

bool Database::connect(const std::string ServerName, const std::string DatabaseName, const std::string UserName, const std::string UserPassword){
	try{
		db = IBPP::DatabaseFactory(ServerName, DatabaseName, UserName, UserPassword);
		db->Connect();
		connected = true;
	}
	catch(IBPP::Exception& e){
		disconnect();
		return false;
	}
	return true;
}

//=========================================================================
// Transaction
//=========================================================================
Transaction::Transaction(Database& db, TransactionAccess access){
	using namespace IBPP;
	try{
		switch(access){
			case taWrite:{
				tr = TransactionFactory(db.db, amWrite);
				break;
			}
			case taRead:{
				tr = TransactionFactory(db.db, amRead, ilReadCommitted, lrNoWait);
				break;
			}
		}
	}
	catch(Exception& e){
		tr = NULL;
	}
}

bool Transaction::start(void){
	try{
		tr->Start();
	}
	catch(IBPP::Exception& e){
		return false;
	}
	return true;
}

bool Transaction::end(void){
	try{
		tr->Commit();
	}
	catch(IBPP::Exception& e){
		tr->Rollback();
		return false;
	}
	return true;
}
