#pragma once

#include <map>

#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include "../Database/Database.h"

void WriteLine(char* line);
void WriteLine(std::string line);

std::map<std::string, std::string> ReadCfg();