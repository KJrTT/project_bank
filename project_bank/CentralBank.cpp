#include "CentralBank.h"
#include <iostream>

CentralBank::CentralBank(double baseInterestRate, double baseFeeRate)
    : baseInterestRate(baseInterestRate), baseFeeRate(baseFeeRate) {}

void CentralBank::addBank(Bank bank) {
    banks.push_back(bank);
}

Bank* CentralBank::getBank(int index) {
    if (index >= 0 && index < banks.size()) {
        return &banks[index];
    }
    return nullptr;
}

size_t CentralBank::getBankCount() const {
    return banks.size();
}

void CentralBank::setBaseInterestRate(double rate) {
    baseInterestRate = rate;
    notifyBanksOfBalanceChange();
}

void CentralBank::setBaseFeeRate(double fee) {
    baseFeeRate = fee;
    notifyBanksOfFee();
}

double CentralBank::getBaseInterestRate() const {
    return baseInterestRate;
}

double CentralBank::getBaseFeeRate() const {
    return baseFeeRate;
}

void CentralBank::notifyBanksOfBalanceChange() {
    std::cout << "Центральный Банк: Изменение базовой процентной ставки на " 
              << baseInterestRate * 100 << "%\n";
              
    for (auto& bank : banks) {
        bank.SetDepositRate(baseInterestRate);
        std::cout << "Банк уведомлен об изменении процентной ставки\n";
    }
}

void CentralBank::notifyBanksOfFee() {
    std::cout << "Центральный Банк: Изменение базовой комиссии на " 
              << baseFeeRate * 100 << "%\n";
              
    for (auto& bank : banks) {
        bank.SetCreditRate(baseFeeRate);
        std::cout << "Банк уведомлен об изменении комиссии\n";
    }
}

bool CentralBank::transferBetweenBanks(int fromBankIndex, int fromAccountIndex,
                                     int toBankIndex, int toAccountIndex,
                                     double amount) {
    if (fromBankIndex < 0 || fromBankIndex >= banks.size() ||
        toBankIndex < 0 || toBankIndex >= banks.size()) {
        std::cout << "Ошибка: неверный индекс банка\n";
        return false;
    }
    Account* fromAccount = banks[fromBankIndex].getAccount(fromAccountIndex);
    Account* toAccount = banks[toBankIndex].getAccount(toAccountIndex);

    if (!fromAccount || !toAccount) {
        std::cout << "Ошибка: счет не найден\n";
        return false;
    }

    if (fromAccount->withdraw(amount)) {
        toAccount->deposit(amount);
        std::cout << "Межбанковский перевод выполнен успешно\n";
        return true;
    }

    std::cout << "Ошибка: недостаточно средств для перевода\n";
    return false;
}

void CentralBank::updateAllBanks(int days) {
    std::cout << "Центральный Банк: Обновление состояния всех банков на " 
              << days << " дней\n";
              
    for (auto& bank : banks) {
        bank.updateTime(days);
    }
}


