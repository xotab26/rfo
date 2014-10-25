#include "Utilities.h"
#include <ctime>
#include <iostream>
#include <fstream>

#ifdef _WIN32
#include "winsock2.h"
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif


DWORD GetIPAddress(const char* ipAddress){
	return inet_addr(ipAddress);
}

void Log(std::string _str){
	time_t now = time(0);
	tm *ltm = localtime(&now);

	char date[256];
	strftime(date, sizeof(date), "%m-%d-%Y %H:%M:%S", ltm);

	char buf[4096];
	strcpy(buf, _str.c_str());

	std::stringstream ss;
	ss << "[" << date << "] " << buf << '\n';
	
	std::cout << ss.str();
}

bool Config::DEBUG;

std::string Config::LogLevel;
std::string Config::DbType;

std::string Config::LoginIP;
std::string Config::LoginPort;

std::string Config::WorldIP;
std::string Config::WorldPort;

std::string Config::ZoneIP;
std::string Config::ZonePort;

std::string Config::DbHost;
std::string Config::DbName;
std::string Config::DbUser;
std::string Config::DbPass;