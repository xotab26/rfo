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