#pragma once

#include <map>

#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

typedef std::map<std::string, std::string> Config;
typedef std::map<std::string, Config> ConfigContainer;

void WriteLine(char* line);
void WriteLine(std::string line);

ConfigContainer ReadCfg();

class Print{
public:
	static void Error(int error_num, const char *error){
		std::cerr << "Error #" << error_num << ": " << error << std::endl;
	}
};

class Convert {
public:
	static short ToShort(char *b){
		return ((b[1] << 8) | b[0]);
	}

	static int ToInt(char *b){
		return (b[3] << 24) | (b[2] << 16) | (b[1] << 8) | (b[0]);
	}
};

class Crypt{
public:
	static void EnCryptString(char* pStr, int nSize, char byPlus, unsigned short wCryptKey)
	{
		for ( int i=0; i<nSize; i++)
		{
			*pStr += byPlus;
			*pStr ^= wCryptKey;
			pStr++;
		}
	}

	static void DeCryptString(char* pStr, int nSize, char byPlus, unsigned short wCryptKey)
	{
		for ( int i=0; i<nSize; i++)
		{
			*pStr ^= wCryptKey;
			*pStr -= byPlus;
			pStr++;
		}
	}
};