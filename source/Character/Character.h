#pragma once

#include "../Database/Database.h"

class CCharacter{
public:
	CCharacter() { }

	~CCharacter(){ }

	bool Set(db_row row){
		return (CharacterRow = row).size() == 0;
	}
private:
	db_row CharacterRow;
};