#pragma once
#include "Account.h"

class DepositAccount : public Account {
private:
    int maturityPeriod;
    int monthsPassed;

public:
    DepositAccount(double initialBalance, int maturityPeriod);
    void deposit(double amount) override;
    bool withdraw(double amount) override;
    double getBalance() override;
    void applyInterest(double interestRate);
    bool isMature();
};
