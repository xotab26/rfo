#pragma once

#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <exception>

typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef unsigned char BYTE;

typedef std::map<std::string, std::string> Option;
typedef std::map<std::string, Option> ConfigContainer;


int setTitle(std::string titleMsg);

DWORD GetIPAddress(const char* ipAddress);

void Log(std::string text);

class Config{
public:
	static ConfigContainer PreLoad(ConfigContainer map){
		LogLevel = map["General"]["LogLevel"];
		DbType = map["General"]["DbType"];

		LoginIP = map["Login"]["Address"];
		LoginPort = map["Login"]["Port"];

		WorldIP = map["World"]["Address"];
		WorldPort = map["World"]["Port"];

		ZoneIP = map["Zone"]["Address"];
		ZonePort = map["Zone"]["Port"];

		DbHost = map["MySQL"]["DbHost"];
		DbName = map["MySQL"]["DbName"];
		DbUser = map["MySQL"]["DbUser"];
		DbPass = map["MySQL"]["DbPass"];

#ifdef _DEBUG
		Config::DEBUG = true;
#else
		Config::DEBUG = false;
#endif
		return map;
	}

	static ConfigContainer ReadCfg(){
		Log("Loading configuration...\n");
		std::ifstream infile("./config.ini");
		
		std::string line;
		std::vector<std::string> tmp;
		while (std::getline(infile, line)){
			if(line.length() == 0) continue;
			tmp.push_back(line);
		}

		Option temp;
		std::string section;
		ConfigContainer map;

		for(auto str : tmp){
			auto front = str.front();
			auto back = str.back();
			if(front == '[' && back == ']'){
				str.erase(0, 1);
				str.erase(str.length()-1);
				section = str;
			}

			size_t i = str.rfind("=");
			if(i != std::string::npos && str.length() >= 2){
				std::string key = str.substr(0, i);
				std::string value = str.substr(i + 2, str.length() - i - 2);

				while(key.front() == ' ' || key.front() == '\t' || key.back() == ' ' || key.back() == '\t'){
					key.erase(key.length()-1);
				}
				
				temp[key] = value;
				map[section] = temp;
			}else{
				temp.clear();
			}
		}

		infile.close();		
		return PreLoad(map);
	}

	static bool DEBUG;

	static std::string LogLevel;
	static std::string DbType;

	static std::string LoginIP;
	static std::string LoginPort;

	static std::string WorldIP;
	static std::string WorldPort;

	static std::string ZoneIP;
	static std::string ZonePort;

	static std::string DbHost;
	static std::string DbName;
	static std::string DbUser;
	static std::string DbPass;
private:
};

class Print{
public:
	static void Error(int error_num, const char *error){
		std::cerr << "Error #" << error_num << ": " << error << std::endl;
	}
};

class Convert {
public:
	static short ToShort(const char *b){
		return ((b[1] << 8) | b[0]);
	}

	static int ToInt(const char *b){
		return (b[3] << 24) | (b[2] << 16) | (b[1] << 8) | (b[0]);
	}

	static char* ToChar(std::string str){
		char* res = new char[str.size()];
		for (size_t i = 0; i < str.size(); i++)
		{
			res[i] = str[i];
		}
		res[str.size()] = '\0';
		return res;
	}
};

class Crypt {
public:
	static void crypt_login(char* pMsg, size_t nSize, BYTE byPlus, WORD wCryptKey){
		for(size_t i = 0; i < nSize; i++)
		{
			int source = pMsg[i] + byPlus;
			pMsg[i] = source ^ wCryptKey;
		}
	}

	static void decrypt_Move(int nSize, char *pMsg, WORD wXorKey, WORD byPlusKey)
	{
		for(int i = 0; i < nSize; i++)
		{
			pMsg[i] ^= 32 + wXorKey;
			pMsg[i] -= 23 + byPlusKey;
		}
	}

	static void encrypt_Move(int nSize, char *pMsg, WORD wXorKey, WORD byPlusKey)
	{
		for(int i=0;i<nSize;i++)
		{
			pMsg[i] += 23 + byPlusKey;
			pMsg[i] ^= 32 + wXorKey;
		}
	}
};