#pragma once

#include "../Utilities/utils.h"

#include "MySQL++/mysql++.h"

class DBConfig{
public:
	DBConfig();
	std::string Name;
	std::string Host;
	std::string User;
	std::string Pass;
};

class CDatabase
{
public:
	CDatabase();
	~CDatabase();
	bool Connect();
	bool Disconnect();
	const char* GetError();
	bool Query(const char *queryStr);
	bool Insert(const char *queryStr);
	mysqlpp::StoreQueryResult Select(const char *queryStr);

private:
	mysqlpp::Connection conn;
	std::string SqlError;
	bool bIsConnected;

	const char* PrintError(mysqlpp::Exception &e);
};