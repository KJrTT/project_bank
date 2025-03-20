#pragma once
#include <vector>
#include <string>
#include "Client.h"
#include "Account.h"

using namespace std;

class Bank {
	vector<Client> clients;
	vector<Account*> accounts;
	string NameBank;
	double DepositRate;
	double CreditRate;
	int daysPassed;
public:
	Bank(double DepositRate, double CreditRate); 
	void AddClient(Client client);
	void OpenAccount(Account* account);
	double GetDepositRate() const;
	double GetCreditRate() const;
	void SetDepositRate(double rate);
	void SetCreditRate(double fee);
	void updateTime(int days); 
	Client* getClient(int index);
	Account* getAccount(int index);
}; 