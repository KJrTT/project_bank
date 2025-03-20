#include "DebitAccount.h"

DebitAccount::DebitAccount(double initialBalance, double interestRate)
    : interestRate(interestRate) {
    balance = initialBalance;
}

void DebitAccount::deposit(double amount) {
    balance += amount;
}

bool DebitAccount::withdraw(double amount) {
    if (amount <= balance) {
        balance -= amount;
        return true;
    }
    return false;
}

double DebitAccount::getBalance() {
    return balance;
}

void DebitAccount::applyInterest() {
    balance += balance * interestRate;
}
