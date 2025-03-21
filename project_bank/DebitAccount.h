#pragma once
#include "Account.h"

class DebitAccount : public Account {
private:
    double interestRate;

public:
    DebitAccount(double initialBalance, double interestRate);
    void deposit(double amount) override;
    bool withdraw(double amount) override;
    double getBalance() override;
    void applyInterest();
};
