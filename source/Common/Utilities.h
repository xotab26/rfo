#pragma once

#include <map>
#include <memory>
#include <cstring>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <exception>

#define MAX_KEY_VALUES 50
#define CONFIG_STR_SIZE 50

typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef unsigned char BYTE;

struct Key_Value{
	operator std::string() const { return Value; }
	std::string operator=(std::string value){
		return Value = value;
	}
	std::string Key;
	std::string Value;
};

struct KeyValue_Pairs{
	KeyValue_Pairs(){ clear(); }
	Key_Value* operator[](std::string key){
		for (short i = 0; i < kv_count; i++){
			if (_kv[i].Key == key){
				return &_kv[i];
			}
		}
		_kv.push_back(Key_Value());
		_kv[kv_count].Key = key;
		return &_kv[kv_count++];
	}
	void clear(){
		kv_count = 0;
		_kv.clear();
	}
private:
	short kv_count;
	std::vector<Key_Value> _kv;
};

typedef KeyValue_Pairs Option;
typedef std::map<std::string, Option> ConfigContainer;

int setTitle(std::string titleMsg);
DWORD GetIPAddress(const char* ipAddress);
void Log(const std::string fmt, ...);
void thread_sleep(int seconds);

class Config{
public:
	Config(){
		ReadCfg();
	}

	void ReadCfg(){
		if(DEBUG) Log("Loading configuration...\n");
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
					key.erase(key.length() - 1);
				}

				temp[key]->Value = value;
				map[section] = temp;
				Set(key.c_str(), value.c_str());
			}else{
				temp.clear();
			}
		}

		infile.close();
	}

	void Set(const char* key, const char* value){
		if (!strcmp(key, "LogLevel")) memcpy(LogLevel, value, strlen(value) + 1);
		if (!strcmp(key, "DbType"))	memcpy(DbType, value, strlen(value) + 1);
		if (!strcmp(key, "LoginIP")) memcpy(LoginIP, value, strlen(value) + 1);
		if (!strcmp(key, "LoginPort")) memcpy(LoginPort, value, strlen(value) + 1);
		if (!strcmp(key, "WorldIP")) memcpy(WorldIP, value, strlen(value) + 1);
		if (!strcmp(key, "WorldPort")) memcpy(WorldPort, value, strlen(value) + 1);
		if (!strcmp(key, "WorldName")) memcpy(WorldName, value, strlen(value) + 1);
		if (!strcmp(key, "ZoneIP")) memcpy(ZoneIP, value, strlen(value) + 1);
		if (!strcmp(key, "ZonePort")) memcpy(ZonePort, value, strlen(value) + 1);
		if (!strcmp(key, "DbHost")) memcpy(DbHost, value, strlen(value) + 1);
		if (!strcmp(key, "DbName")) memcpy(DbName, value, strlen(value) + 1);
		if (!strcmp(key, "DbUser")) memcpy(DbUser, value, strlen(value) + 1);
		if (!strcmp(key, "DbPass")) memcpy(DbPass, value, strlen(value) + 1);
	}

	static bool DEBUG;

	char LogLevel[CONFIG_STR_SIZE];
	char DbType[CONFIG_STR_SIZE];
	char LoginIP[CONFIG_STR_SIZE];
	char LoginPort[CONFIG_STR_SIZE];
	char WorldIP[CONFIG_STR_SIZE];
	char WorldPort[CONFIG_STR_SIZE];
	char WorldName[CONFIG_STR_SIZE];
	char ZoneIP[CONFIG_STR_SIZE];
	char ZonePort[CONFIG_STR_SIZE];
	char DbHost[CONFIG_STR_SIZE];
	char DbName[CONFIG_STR_SIZE];
	char DbUser[CONFIG_STR_SIZE];
	char DbPass[CONFIG_STR_SIZE];
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