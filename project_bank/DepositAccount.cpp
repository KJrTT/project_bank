#include "DepositAccount.h"

DepositAccount::DepositAccount(double initialBalance, int maturityPeriod)
    : maturityPeriod(maturityPeriod), monthsPassed(0) {
    balance = initialBalance;
}

void DepositAccount::deposit(double amount) {
    balance += amount;
}

bool DepositAccount::withdraw(double amount) {
    if (isMature() && amount <= balance) {
        balance -= amount;
        return true;
    }
    return false;
}

double DepositAccount::getBalance() {
    return balance;
}

void DepositAccount::applyInterest(double interestRate) {
    if (monthsPassed < maturityPeriod) {
        balance += balance * interestRate;
        monthsPassed++;
    }
}

bool DepositAccount::isMature(){
    return monthsPassed >= maturityPeriod;
}
