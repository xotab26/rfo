#pragma once

#include "../Database/Database.h"

class CCharacter{
public:
	CCharacter();
	~CCharacter();

	bool Set(mysqlpp::Row row);
private:
	mysqlpp::Row CharacterRow;
};