#include <iostream>
#include "dbs.h"

int main(int argc, char** argv)
{
	if(argc!= 6){
		std::cout << "Params error\n";
		return _ERROR;
	}
	const std::string ServerName = argv[1];
	const std::string DatabaseName = argv[2];
	const std::string UserName = argv[3];
	const std::string UserPassword = argv[4];
	const char* filename = argv[5];
	
	Database db = Database();
	if(!db.connect(ServerName, DatabaseName, UserName, UserPassword)){
		std::cout << "Connect error\n";
		return _ERROR_CONNECT;
	}
	Transaction trWrite = Transaction(db, taWrite);
	if(!trWrite.start()){
		std::cout << "Start transaction error\n";
		return _ERROR_TRANSACTION_START;
	}
	Script script(filename);
	while(script.fetch()){
		std::cout << script.script << "\n";
	}
	if(!trWrite.end()){
		std::cout << "End transaction error\n";
		return _ERROR_TRANSACTION_END;
	}
	if(!db.disconnect()){
		return _ERROR_DISCONNECT;
	}
	return 0;
}
