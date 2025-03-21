#include "CreditAccount.h"

CreditAccount::CreditAccount(double initialBalance, double creditLimit)
    : creditLimit(creditLimit) {
    balance = initialBalance;
}

void CreditAccount::deposit(double amount) {
    balance += amount;
}

bool CreditAccount::withdraw(double amount) {
    if (amount <= balance + creditLimit) {
        balance -= amount;
        return true;
    }
    return false;
}

double CreditAccount::getBalance() {
    return balance;
}

void CreditAccount::applyFee(double fee) {
    if (balance < 0) {
        balance -= fee;
    }
}
