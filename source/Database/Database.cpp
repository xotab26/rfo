#include "Database.h"

DBConfig::DBConfig(){
	auto cfg = ReadCfg();
	Host = cfg["DbHost"];
	Name = cfg["DbName"];
	User = cfg["DbUser"];
	Pass = cfg["DbPass"];
}

CDatabase::CDatabase(){
	bIsConnected = false;
}

CDatabase::~CDatabase(){
	Disconnect();
}

bool CDatabase::Connect(){
	try {
		DBConfig *cfg = new DBConfig;
		conn.connect(cfg->Name.c_str(), cfg->Host.c_str(), cfg->User.c_str(), cfg->Pass.c_str());
		conn.query();
	}
	catch (mysqlpp::Exception &e) {
		PrintError(e);
	}
	
	return true;
}

bool CDatabase::Disconnect(){
	if (bIsConnected) 
		conn.disconnect();
	
	bIsConnected = false;
	return true;
}

mysqlpp::StoreQueryResult CDatabase::Select(const char *queryStr){
	mysqlpp::StoreQueryResult res;
	try{
		mysqlpp::Query query = conn.query(queryStr);

		if ((res = query.store()).empty()) {
			throw mysqlpp::BadQuery("Item not found in table");
		}

		return res;
	}
	catch (mysqlpp::Exception &e) {
		PrintError(e);
	}
	return res;
}

bool CDatabase::Query(const char* queryStr){
	try{
		mysqlpp::Query query = conn.query(queryStr);
		query.parse();
	}
	catch (mysqlpp::Exception &e) {
		PrintError(e);
		return false;
	}
	return true;
}

bool CDatabase::Insert(const char *queryStr){
	try{
		mysqlpp::Query query = conn.query(queryStr);
		query.execute();
	}
	catch (mysqlpp::Exception &e) {
		PrintError(e);
		return false;
	}
	return true;
}

const char* CDatabase::GetError(){
	return SqlError.c_str();
}

const char* CDatabase::PrintError(mysqlpp::Exception &e){
	std::ostringstream buf;
	std::ostream& os(buf);

	os << "\nERR: SQLException in " << __FILE__;
	os << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
	os << "\n# ERR: " << e.what() << std::endl;

	SqlError = buf.str();

	printf(SqlError.c_str());
	return SqlError.c_str();
}