#pragma once
#include <vector>
#include <string>

struct Transaction {
	std::string type; 
	double amount;    
	bool isReversed;  
};

class Account {
protected:
	int accountID;
	double balance;
public:
	std::vector<Transaction> transactHistory; 

	Account() : accountID(0), balance(0) {};
	virtual ~Account() = default;
	virtual void deposit(double amount) = 0;
	virtual bool withdraw(double amount) = 0;
	virtual double getBalance() = 0;
	void reverseTransaction(int transactionID); 
};