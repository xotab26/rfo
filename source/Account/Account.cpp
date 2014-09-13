#include "Account.h"

CAccount::CAccount(uint accountId){
	Set(accountId);
}

CAccount::CAccount(){

}

CAccount::~CAccount(){

}

void CAccount::Set(uint _id){
	auto id = std::to_string(_id);

	std::string query("SELECT * FROM Accounts WHERE id='" + id + "'");
	CDatabase db;
	
	if (db.Connect()){
		mysqlpp::StoreQueryResult rows = db.Select(query.c_str());
		if (!rows.empty()) AccountRow = rows[0];
		Id = (uint) AccountRow["id"];
		Nick = AccountRow["nick"];
		Pass = AccountRow["pass"];
		Email = AccountRow["email"];
		Type = (short) AccountRow["type"];

		query = std::string("SELECT * FROM Characters WHERE account='" + id + "'");
		rows = db.Select(query.c_str());
		
		if(rows.empty()) return;

		for (int i = 0; i < 3 ; i++)
		{
			if(rows[i].empty()) continue;
			Character[i].Set(rows[i]);
		}
	}
}