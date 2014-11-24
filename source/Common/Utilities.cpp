#include "Utilities.h"
#include <ctime>
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdarg.h>

#ifdef _WIN32
#include "winsock2.h"
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif


int setTitle(std::string titleMsg)
{
	std::string title = "[RFO Emulator] ";
#ifdef _WIN32
#include <windows.h>
#ifdef _UNICODE
	LPCWSTR str;
#else
	LPCSTR str;
#endif
	title.append(titleMsg);	
	const char* cs = title.c_str();
	wchar_t filename[4096] = { 0 };
	MultiByteToWideChar(0, 0, cs, (int)strlen(cs), filename, (int)strlen(cs));
	return SetConsoleTitle(str = filename);
#else
	char esc_start[] = { 0x1b, ']', '0', ';', 0 };
	char esc_end[] = { 0x07, 0 };
	std::cout << esc_start << title << titleMsg << esc_end;
	return 1;
#endif
	return 0;
}

DWORD GetIPAddress(const char* ipAddress){
	return inet_addr(ipAddress);
}

void Log(const std::string fmt, ...) {
	time_t now = time(0);
	tm *ltm = localtime(&now);

	char date[256];
	strftime(date, sizeof(date), "%m-%d-%Y %H:%M:%S", ltm);

	int size = ((int)fmt.size()) * 2 + 50;
	std::string str;
	va_list ap;
	while (1) {
		str.resize(size);
		va_start(ap, fmt);
		int n = vsnprintf((char *)str.data(), size, fmt.c_str(), ap);
		va_end(ap);
		if (n > -1 && n < size) {
			str.resize(n);
			break;
		}
		if (n > -1)
			size = n + 1;
		else
			size *= 2; 
	}

	std::stringstream ss;
	ss << "[" << date << "] " << str << '\n';
	std::cout << ss.str().c_str();
}

bool Config::DEBUG;

char Config::LogLevel[CONFIG_STR_SIZE];
char Config::DbType[CONFIG_STR_SIZE];
char Config::LoginIP[CONFIG_STR_SIZE];
char Config::LoginPort[CONFIG_STR_SIZE];
char Config::WorldIP[CONFIG_STR_SIZE];
char Config::WorldPort[CONFIG_STR_SIZE];
char Config::WorldName[CONFIG_STR_SIZE];
char Config::ZoneIP[CONFIG_STR_SIZE];
char Config::ZonePort[CONFIG_STR_SIZE];
char Config::DbHost[CONFIG_STR_SIZE];
char Config::DbName[CONFIG_STR_SIZE];
char Config::DbUser[CONFIG_STR_SIZE];
char Config::DbPass[CONFIG_STR_SIZE];