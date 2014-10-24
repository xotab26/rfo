#include "Character.h"


bool CCharacter::Set(mysqlpp::Row row){
	return (CharacterRow = row) != NULL;
}