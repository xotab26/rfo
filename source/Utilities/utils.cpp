#include "utils.h"

void WriteLine(char* line){
	std::cout << line << "\n";
}

void WriteLine(const char* line){
	WriteLine((char*)line);
}

void WriteLine(std::string line){
	WriteLine(line.c_str());
}

std::map<std::string, std::string> ReadCfg(){
	boost::property_tree::ptree pt;

	if (!boost::filesystem::exists("config.ini")){
		std::ofstream outfile("config.ini");
		outfile.close();
	}

	std::map<std::string, std::string> map;

	read_ini("config.ini", pt);
	
	for (auto section : pt){
		for (auto& key : section.second){
			map[key.first] = key.second.get_value<std::string>();
		}
	}

	return map;
}