#pragma once

#ifdef _WIN32
#include "winsock.h"
#endif
#include "mysql.h"
#include "../Utilities.h"


typedef std::map<std::string, std::string> db_row;
typedef std::vector<db_row> db_rows;

class CDatabase
{
public:

	CDatabase(){
		auto cfg = Config::ReadCfg();
		Host = cfg["MySQL"]["DbHost"];
		Name = cfg["MySQL"]["DbName"];
		User = cfg["MySQL"]["DbUser"];
		Pass = cfg["MySQL"]["DbPass"];

		bIsConnected = false;
	}

	~CDatabase(){
		Disconnect();
	}

	bool Connect(){
		try {
			const char *server = Host.c_str();
			const char *user = User.c_str();
			const char *password = Pass.c_str();
			const char *database = Name.c_str();

			conn = mysql_init(NULL);
			if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
				printf("%s\n", mysql_error(conn));
			}
			return bIsConnected = true;
		}
		catch (std::exception &e) {
			printf("%s\n", e.what());
			return bIsConnected = false;
		}
	}

	bool Disconnect(){
		if (bIsConnected){
			mysql_close(conn);
			bIsConnected = false;
		}
		return true;
	}

	db_rows Select(const char *queryStr){
		MYSQL_RES* res;
		db_rows rows;

		if(!IsOpen()) Connect();

		try{
			if (mysql_query(conn, queryStr)) {
				printf("%s\n", mysql_error(conn));
			}

			if(res = mysql_store_result(conn)){

				int num_fields = mysql_num_fields(res);

				MYSQL_ROW row;
				MYSQL_FIELD *field;
				std::vector<MYSQL_FIELD*> fields;
				char* field_name;

				while ((row = mysql_fetch_row(res))) {
					int num_fields = mysql_num_fields(res);

					db_row my_row;
					for(int i = 0; i < num_fields; i++) {

						while(field = mysql_fetch_field(res)) {
							fields.push_back(field);
						}

						field_name = fields[i]->name;
						my_row[field_name] = row[i];
					} 
					rows.push_back(my_row);
				}
			}
		}
		catch (std::exception &e) {
			printf("%s\n", e.what());
		}

		mysql_free_result(res);
		return rows;
	}

	bool Query(const char* queryStr){
		if (mysql_query(conn, queryStr)) {
			printf("%s\n", mysql_error(conn));
			return false;
		}
		return true;
	}

	bool Insert(const char *queryStr){
		if (mysql_query(conn, queryStr)) {
			printf("%s\n", mysql_error(conn));
			return false;
		}
		return true;
	}

	bool IsOpen(){
		if(conn != NULL){
			return bIsConnected = true;
		}else{
			return bIsConnected = false;
		}
	}

	const char* GetError(){
		return SqlError.c_str();
	}

	static std::string Name;
	static std::string Host;
	static std::string User;
	static std::string Pass;

private:
	MYSQL* conn;
	std::string SqlError;
	bool bIsConnected;
};