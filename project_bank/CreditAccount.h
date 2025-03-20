#pragma once
#include "Account.h"

class CreditAccount : public Account {
private:
    double creditLimit;

public:
    CreditAccount(double initialBalance, double creditLimit);
    void deposit(double amount) override;
    bool withdraw(double amount) override;
    double getBalance() override;
    void applyFee(double fee);
};
