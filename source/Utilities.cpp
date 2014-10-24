#include "Utilities.h"

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