#pragma once
#include <vector>
#include <string>
#include "Bank.h"

class CentralBank {
private:
    std::vector<Bank> banks;
    double baseInterestRate; 
    double baseFeeRate;       

public:
    CentralBank(double baseInterestRate = 0.05, double baseFeeRate = 0.01);
    void addBank(Bank bank);
    Bank* getBank(int index);
    size_t getBankCount() const;

    void setBaseInterestRate(double rate);
    void setBaseFeeRate(double fee);
    double getBaseInterestRate() const;
    double getBaseFeeRate() const;
    void notifyBanksOfBalanceChange(); 
    void notifyBanksOfFee();           
    bool transferBetweenBanks(int fromBankIndex, int fromAccountIndex, int toBankIndex, int toAccountIndex, double amount);
    void updateAllBanks(int days);
};
