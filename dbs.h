#include <string>
#define IBPP_LINUX
#include <ibpp/ibpp.h>
#include <iostream>

#define _OK 0
#define _ERROR_CONNECT 1
#define _ERROR_DISCONNECT 2
#define _ERROR_TRANSACTION_CREATE 3
#define _ERROR_TRANSACTION_START 4
#define _ERROR_TRANSACTION_END 5
#define _ERROR_STATEMENT 6
#define _ERROR 100

using namespace std;

enum TransactionAccess{taWrite, taRead};

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

class Database{
private:
	IBPP::Database db;
	friend class Transaction;
public:
	bool connected;
	bool connect(const std::string ServerName, const std::string DatabaseName, const std::string UserName, const std::string UserPassword);
	bool disconnect(void);
};
class Transaction{
private:
	IBPP::Transaction tr;
public:
	bool start(void);
	bool end(void);
	Transaction(Database& db, TransactionAccess access);
};
