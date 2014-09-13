#include "Character.h"

CCharacter::CCharacter() {
	
}

CCharacter::~CCharacter(){

}

bool CCharacter::Set(mysqlpp::Row row){
	return (CharacterRow = row) != NULL;
}