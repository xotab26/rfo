#pragma once

#include "../Character/Character.h"
#include "../Database/Database.h"

typedef unsigned int uint;

class CAccount{
public:
	CAccount(uint accountId);
	~CAccount();

	uint Id;
	short Type;
	std::string Nick;
	std::string Pass;
	std::string Email;

	CCharacter Character[3];

private:
	mysqlpp::Row AccountRow;
};