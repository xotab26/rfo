#pragma once

#include "../Character/Character.h"
#include "../Database/Database.h"


class Account{
public:
	Account(){ }
	~Account(){ }
	
	/// <summary>
	/// Verifies the specified account identifier.
	/// </summary>
	/// <param name="accountId">The account identifier.</param>
	/// <param name="accountPass">The account pass.</param>
	/// <returns>True if check passes, otherwise false.</returns>
	bool Verify(char* nick, char* pass){
		std::string query("SELECT * FROM Accounts WHERE nick='" + std::string(nick) + "' AND pass='" + pass + "'");
		CDatabase db;

		if (db.Connect()) {
			auto res = db.Select(query.c_str());
			if (!res.empty()) AccountRow = res[0];

			AccountId = (u_int) atol(AccountRow["id"].c_str());
			Type = (short) atoi(AccountRow["type"].c_str());
			Nick = AccountRow["nick"];
			Pass = AccountRow["pass"];
			Email = AccountRow["email"];
			
			query = std::string("SELECT * FROM Characters WHERE account='" + std::to_string(AccountId) + "'");
			res = db.Select(query.c_str());
			
			for (size_t i = 0; i < res.size(); i++) {
				Character[i].Set(res[i]);
			}

			return Accepted = true;
		}

		return false;
	}

	const char* lock_reason(){
		return AccountRow["lock_reason"].c_str();
	}

	/// <summary>
	/// Creates a new Account instance.
	/// </summary>
	static Account create(u_int localId){
		Account a;
		a.nBillInform = 0;
		a.Accepted = false;
		a.LocalId = localId;
		a.AccountId = 0xFFFFFFFF;
		return a;
	}

	short Type;
	u_int LocalId;
	u_int AccountId;
	std::string Nick;
	std::string Pass;
	std::string Email;

	CCharacter Character[3];

	bool Accepted;
	int nBillInform;

	BYTE CryptPlus;
	WORD CryptKey;
private:
	db_row AccountRow;
};