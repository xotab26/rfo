#include "utils.h"
#include "../Database/Database.h"

void WriteLine(char* line){
	std::cout << line << "\n";
}

void WriteLine(const char* line){
	WriteLine((char*)line);
}

void WriteLine(std::string line){
	WriteLine(line.c_str());
}

ConfigContainer ReadCfg(){
	boost::property_tree::ptree pt;

	if (!boost::filesystem::exists("config.ini")){
		std::ofstream outfile("config.ini");
		outfile.close();
	}

	ConfigContainer map;

	read_ini("config.ini", pt);
	
	for (auto section : pt){		
		Config cfg;
		for (auto& key : section.second){
			cfg[key.first] = key.second.get_value<std::string>();			
		}
		map[section.first] = cfg;
	}

	return map;
}