#pragma once

#ifdef _WIN32
#include "winsock.h"
#endif
#include "mysql.h"
#include "../Common/Utilities.h"


typedef std::map<std::string, std::string> db_row;
typedef std::vector<db_row> db_rows;

class CDatabase
{
public:
	CDatabase(Config* _cfg){
		Log("Loading database class...");
		bIsConnected = false;
		cfg = _cfg;
	}

	~CDatabase(){
		Disconnect();
	}

	bool Connect(){
		try {
			if (Config::DEBUG) Log("Connecting to database...");
			conn = mysql_init(NULL);
			ConnectionAlive();
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
			mysql_server_end();
			bIsConnected = false;
		}
		return true;
	}

	bool ConnectionAlive(){
		mysql_init(conn);
		if (!mysql_real_connect(conn, cfg->DbHost, cfg->DbUser, cfg->DbPass, cfg->DbName, 0, NULL, 0)) {
			printf("%s\n", mysql_error(conn));
			return false;
		}
		else{
			mysql_ping(conn);
		}

		return true;
	}

	db_rows Select(std::string queryStr){
		MYSQL_RES* res;
		db_rows rows;

		if(!IsOpen()) Connect();

		try{
			if (mysql_query(conn, queryStr.c_str())) {
				printf("%s\n", mysql_error(conn));
			}

			if((res = mysql_store_result(conn))){
				std::vector<MYSQL_FIELD*> fields;
				MYSQL_ROW row;
				MYSQL_FIELD* field;
				char* field_name;

				while ((row = mysql_fetch_row(res))) {
					int num_fields = mysql_num_fields(res);

					db_row my_row;
					for(int i = 0; i < num_fields; i++) {

						while((field = mysql_fetch_field(res))) {
							fields.push_back(field);
						}

						field_name = fields[i]->name;
						my_row[field_name] = row[i];
					} 
					rows.push_back(my_row);
					delete field;
				}
			}
		}
		catch (std::exception &e) {
			printf("%s\n", e.what());
		}

		mysql_free_result(res);
		return rows;
	}

	bool Query(std::string queryStr){
		if (mysql_query(conn, queryStr.c_str())) {
			printf("%s\n", mysql_error(conn));
			return false;
		}
		return true;
	}

	bool Insert(std::string queryStr){
		if (mysql_query(conn, queryStr.c_str())) {
			printf("%s\n", mysql_error(conn));
			return false;
		}
		return true;
	}

	bool IsOpen(){
		if (conn != NULL){
			return bIsConnected = true;
		}
		else{
			return bIsConnected = false;
		}
	}

private:
	MYSQL* conn;
	Config* cfg;
	bool bIsConnected;
};