#pragma once

#include "../Network/Protocol.h"
#include "../Database/Database.h"
#include "../Character/Character.h"


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
		return Accepted = Load(query);
	}


	bool Load(u_int aid) {
		std::string query("SELECT * FROM Accounts WHERE id='" + std::to_string(aid) + "'");
		return Load(query);
	}

	bool Load(std::string query){
		if (db->Connect()) {
			auto res = db->Select(query.c_str());
			if (!res.empty()) {
				AccountRow = res[0];
				if (AccountRow.size() <= 1){
					return false;
				}
			}

			AccountId = (u_int)atol(AccountRow["id"].c_str());
			UserGrade = (BYTE)atoi(AccountRow["type"].c_str());
			Nick = AccountRow["nick"];
			Pass = AccountRow["pass"];
			Email = AccountRow["email"];

			query = std::string("SELECT * FROM Characters WHERE account='" + std::to_string(AccountId) + "'");
			res = db->Select(query.c_str());

			CharNum = res.size();

			for (size_t i = 0; i < CharNum; i++) {
				character[i].Set(res[i]);
			}

			return true;
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
		a.CharNum = 0;
		a.nBillInform = 0;
		a.Accepted = false;
		a.LocalId = localId;
		a.AccountId = 0xFFFFFFFF;
		return a;
	}

	bool Accepted;
	int nBillInform;
	short CharNum;
	BYTE UserGrade;
	u_int LocalId;
	u_int AccountId;
	std::string Nick;
	std::string Pass;
	std::string Email;
	BYTE CryptPlus;
	WORD CryptKey;
	Character character[3];

	DWORD m_dwMasterKey[CHECK_KEY_NUM];

	CDatabase* db;
private:
	db_row AccountRow;
};