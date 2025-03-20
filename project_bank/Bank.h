#pragma once
#include <vector>
#include "Client.h"
#include "Account.h"



class Bank {
	vector <Client> clients;
	vector <Account> accounts;
public:
	
	void addClient(Client client);
	void openAccount(Account account);
	void processDailyOperations();
};