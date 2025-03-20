#include <iostream>
#include <string>
#include <vector>
#include "Bank.h"
using namespace std;

void Bank::addClient(Client client) {
	clients.push_back(client);
}


void Bank::openAccount(Account account) {
	accounts.push_back(account);
}

