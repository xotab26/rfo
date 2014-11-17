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


int setTitle(std::string titleMsg)
{
#ifdef _WIN32
#include <windows.h>
#ifdef _UNICODE
	LPCWSTR str;
#else
	LPCSTR str;
#endif
	std::string title = "[RFO Emulator] ";
	title.append(titleMsg);
	
	const char* cs = title.c_str();
	wchar_t filename[4096] = { 0 };
	MultiByteToWideChar(0, 0, cs, (int)strlen(cs), filename, (int)strlen(cs));
	return SetConsoleTitle(str = filename);
#else
	char esc_start[] = { 0x1b, ']', '0', ';', 0 };
	char esc_end[] = { 0x07, 0 };
	std::cout << esc_start << titleMsg << esc_end;
	return 1;
#endif
	return 0;
}

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