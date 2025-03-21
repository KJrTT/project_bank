#include <iostream>
#include <string>
#include <vector>
#include "Bank.h"
#include "Account.h"
#include "DebitAccount.h"
#include "DepositAccount.h"
#include "CreditAccount.h"


using std::cout;
using std::vector;
using std::string;

Bank::Bank(double DepositRate, double CreditRate)
	: DepositRate(DepositRate), CreditRate(CreditRate), daysPassed(0) {}

void Bank::AddClient(Client client) {
	clients.push_back(client); 
} 

void Bank::OpenAccount(Account* account) {
	accounts.push_back(account); 
}

void Bank::updateTime(int days) {
	daysPassed += days;
	for (auto account : accounts) {
		DebitAccount* debitAccount = dynamic_cast<DebitAccount*>(account);
		if (debitAccount) {
			debitAccount->applyInterest();
			continue;
		}
		
		DepositAccount* depositAccount = dynamic_cast<DepositAccount*>(account);
		if (depositAccount) {
			depositAccount->applyInterest(DepositRate);
			continue;
		}
		
		CreditAccount* creditAccount = dynamic_cast<CreditAccount*>(account);
		if (creditAccount) {
			creditAccount->applyFee(CreditRate);
			continue;
		}
	}
	
	std::cout << "Проценты и комиссии начислены для всех счетов.\n";
}

double Bank::GetDepositRate() const {
	return DepositRate;
}

void Bank::SetDepositRate(double rate) {
	DepositRate = rate;
}

double Bank::GetCreditRate() const {
	return CreditRate;
}

void Bank::SetCreditRate(double fee) {
	CreditRate = fee;
}

Client* Bank::getClient(int index) {
	if (index >= 0 && index < clients.size()) {
		return &clients[index];
	}
	return nullptr;
}

Account* Bank::getAccount(int index) {
	if (index >= 0 && index < accounts.size()) {
		return accounts[index];
	}
	return nullptr;
}



