#include <iostream>
#include <locale>
#include <string>
#include "Bank.h"
#include "Client.h"
#include "DebitAccount.h"
#include "CreditAccount.h"
#include "DepositAccount.h"
#include "CentralBank.h"

void createClient(Bank& bank);
void openAccount(Bank& bank);
void performTransaction(Bank& bank);
void displayClientInfo(Bank& bank);
void updateTime(Bank& bank);
void displayClientAccounts(Bank& bank);
void reverseTransactionMenu(Bank& bank);
void centralBankMenu(CentralBank& centralBank);
void transferBetweenBanksMenu(CentralBank& centralBank);
void updateAllBanksMenu(CentralBank& centralBank);

int currentClientIndex = -1;
bool isEmployee = false;

void createClient(Bank& bank) {
    std::string firstName, lastName, address;
    int age, passportSeries, passportNumber;
    
    std::cout << "Введите имя: ";
    std::cin >> firstName;
    std::cout << "Введите фамилию: ";
    std::cin >> lastName;
    std::cout << "Введите возраст: ";
    std::cin >> age;
    std::cout << "Введите адрес: ";
    std::cin.ignore();
    std::getline(std::cin, address);
    std::cout << "Введите серию паспорта: ";
    std::cin >> passportSeries;
    std::cout << "Введите номер паспорта: ";
    std::cin >> passportNumber;

    Client client(firstName, lastName, age, address, passportSeries, passportNumber);
    bank.AddClient(client);

    for (int i = 0; i < 100; i++) {
        Client* c = bank.getClient(i);
        if (c == nullptr) {
            currentClientIndex = i - 1; 
            break;
        }
    }
    
    std::cout << "Вы успешно зарегистрированы под ID: " << currentClientIndex << "\n";
}

bool loginUser(Bank& bank) {
    std::cout << "\n=== Авторизация ===\n";
    std::cout << "1. Войти как существующий клиент\n";
    std::cout << "2. Зарегистрироваться как новый клиент\n";
    std::cout << "3. Войти как сотрудник банка\n";
    std::cout << "0. Выход\n";
    std::cout << "Ваш выбор: ";
    
    int choice;
    std::cin >> choice;
    
    if (choice == 0) {
        return false;
    }
    else if (choice == 1) {
        int clientCount = 0;
        std::cout << "\n=== Список клиентов (только для демонстрации) ===\n";
        for (int i = 0; i < 100; i++) {
            Client* client = bank.getClient(i);
            if (client == nullptr) break;
            
            std::cout << i << ". " << client->GetFirstName() << " " << client->GetLastName() << "\n";
            clientCount++;
        }
        
        if (clientCount == 0) {
            std::cout << "Нет зарегистрированных клиентов. Пожалуйста, зарегистрируйтесь.\n";
            return false;
        }
        
        std::cout << "Введите ваш ID: ";
        std::cin >> currentClientIndex;
        
        Client* client = bank.getClient(currentClientIndex);
        if (client == nullptr) {
            std::cout << "Неверный ID клиента.\n";
            currentClientIndex = -1;
            return false;
        }
        
        std::cout << "Вы вошли как " << client->GetFirstName() << " " << client->GetLastName() << "\n";
        return true;
    }
    else if (choice == 2) {
        createClient(bank);
        return true;
    }
    else if (choice == 3) {
        std::string password;
        std::cout << "Введите пароль: ";
        std::cin >> password;
        if (password == "1234") {
            isEmployee = true;
            std::cout << "Вы вошли как сотрудник банка.\n";
            return true;
        } else {
            std::cout << "Неверный пароль.\n";
            return false;
        }
    }
    
    return false;
}

void displayClientAccounts(Bank& bank) {
    bool found = false;
    std::cout << "\n=== Ваши счета ===\n";
    
    for (int i = 0; i < 100; i++) {
        Account* account = bank.getAccount(i);
        if (account == nullptr) continue;
        std::cout << "Счёт #" << i << " - Баланс: " << account->getBalance() << "\n";
        found = true;
    }
    
    if (!found) {
        std::cout << "У вас пока нет открытых счетов.\n";
    }
}

void openAccount(Bank& bank) {
    int choice;
    double initialBalance;
    
    std::cout << "Выберите тип счета:\n";
    std::cout << "1. Дебетовый счет\n";
    std::cout << "2. Кредитный счет\n";
    std::cout << "3. Депозитный счет\n";
    std::cout << "Ваш выбор: ";
    std::cin >> choice;
    
    std::cout << "Введите начальный баланс: ";
    std::cin >> initialBalance;
    
    Account* account = nullptr;
    
    switch (choice) {
        case 1: {
            account = new DebitAccount(initialBalance, bank.GetDepositRate());
            break;
        }
        case 2: {
            double creditLimit;
            std::cout << "Введите кредитный лимит: ";
            std::cin >> creditLimit;
            account = new CreditAccount(initialBalance, creditLimit);
            break;
        }
        case 3: {
            int maturityPeriod;
            std::cout << "Введите срок депозита (в месяцах): ";
            std::cin >> maturityPeriod;
            account = new DepositAccount(initialBalance, maturityPeriod);
            break;
        }
        default:
            std::cout << "Неверный выбор типа счета.\n";
            return;
    }
    
    bank.OpenAccount(account);
    std::cout << "Счет успешно открыт.\n";
}

void performTransaction(Bank& bank) {
    displayClientAccounts(bank);
    
    int accountIndex;
    int choice;
    double amount;
    
    std::cout << "Выберите операцию:\n";
    std::cout << "1. Пополнить счет\n";
    std::cout << "2. Снять со счета\n";
    std::cout << "Ваш выбор: ";
    std::cin >> choice;
    
    std::cout << "Введите номер счета: ";
    std::cin >> accountIndex;
    
    std::cout << "Введите сумму: ";
    std::cin >> amount;
    
    Account* account = bank.getAccount(accountIndex);
    
    if (account == nullptr) {
        std::cout << "Счет не найден.\n";
        return;
    }
    
    Transaction transaction;
    if (choice == 1) {
        transaction.type = "deposit";
        transaction.amount = amount;
        transaction.isReversed = false;
        account->deposit(amount);
        std::cout << "Счет пополнен. Новый баланс: " << account->getBalance() << "\n";
    } else if (choice == 2) {
        transaction.type = "withdraw";
        transaction.amount = amount;
        transaction.isReversed = false;
        if (account->withdraw(amount)) {
            std::cout << "Операция выполнена успешно. Новый баланс: " << account->getBalance() << "\n";
        } else {
            std::cout << "Недостаточно средств или другие ограничения.\n";
            return;
        }
    } else {
        std::cout << "Неверный выбор операции.\n";
        return;
    }
    
    account->transactHistory.push_back(transaction);
    std::cout << "ID транзакции: " << account->transactHistory.size() - 1 << "\n";
}

void displayClientInfo(Bank& bank) {
    if (currentClientIndex < 0) {
        std::cout << "Пожалуйста, сначала авторизуйтесь.\n";
        return;
    }
    
    Client* client = bank.getClient(currentClientIndex);
    
    if (client == nullptr) {
        std::cout << "Информация о клиенте не найдена.\n";
        return;
    }
    
    std::cout << "\n=== Информация о вашем профиле ===\n";
    client->DisplayInfoClient();

    displayClientAccounts(bank);
}

void updateTime(Bank& bank) {
    int days;
    std::cout << "Введите количество дней для обновления: ";
    std::cin >> days;
    bank.updateTime(days);
    std::cout << "Время обновлено на " << days << " дней.\n";
}

void reverseTransactionMenu(Bank& bank) {
    displayClientAccounts(bank);
    
    int accountIndex;
    int transactionID;
    
    std::cout << "Введите номер счета: ";
    std::cin >> accountIndex;
    
    Account* account = bank.getAccount(accountIndex);
    if (account == nullptr) {
        std::cout << "Счет не найден.\n";
        return;
    }
    
    std::cout << "Введите ID транзакции для отмены: ";
    std::cin >> transactionID;
    
    account->reverseTransaction(transactionID);
    std::cout << "Попытка отмены транзакции выполнена. Новый баланс: " 
              << account->getBalance() << "\n";
}

void centralBankMenu(CentralBank& centralBank) {
    int choice;
    do {
        std::cout << "\n=== Центральный Банк ===\n";
        std::cout << "1. Установить базовую процентную ставку\n";
        std::cout << "2. Установить базовую комиссию\n";
        std::cout << "3. Перевести средства между банками\n";
        std::cout << "4. Обновить состояние всех банков\n";
        std::cout << "0. Назад\n";
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                double rate;
                std::cout << "Введите новую базовую процентную ставку: ";
                std::cin >> rate;
                centralBank.setBaseInterestRate(rate);
                break;
            }
            case 2: {
                double fee;
                std::cout << "Введите новую базовую комиссию: ";
                std::cin >> fee;
                centralBank.setBaseFeeRate(fee);
                break;
            }
            case 3:
                transferBetweenBanksMenu(centralBank);
                break;
            case 4:
                updateAllBanksMenu(centralBank);
                break;
            case 0:
                std::cout << "Возврат в главное меню.\n";
                break;
            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);
}

void transferBetweenBanksMenu(CentralBank& centralBank) {
    int fromBankIndex, fromAccountIndex, toBankIndex, toAccountIndex;
    double amount;

    std::cout << "Введите индекс банка-отправителя: ";
    std::cin >> fromBankIndex;
    std::cout << "Введите индекс счета-отправителя: ";
    std::cin >> fromAccountIndex;
    std::cout << "Введите индекс банка-получателя: ";
    std::cin >> toBankIndex;
    std::cout << "Введите индекс счета-получателя: ";
    std::cin >> toAccountIndex;
    std::cout << "Введите сумму перевода: ";
    std::cin >> amount;

    if (centralBank.transferBetweenBanks(fromBankIndex, fromAccountIndex, toBankIndex, toAccountIndex, amount)) {
        std::cout << "Перевод выполнен успешно.\n";
    } else {
        std::cout << "Ошибка при выполнении перевода.\n";
    }
}

void updateAllBanksMenu(CentralBank& centralBank) {
    int days;
    std::cout << "Введите количество дней для обновления: ";
    std::cin >> days;
    centralBank.updateAllBanks(days);
    std::cout << "Состояние всех банков обновлено на " << days << " дней.\n";
}

void runBankInterface(Bank& bank, CentralBank& centralBank) {
    if (!loginUser(bank)) {
        std::cout << "Авторизация не выполнена \n";
        return;
    }
    
    int choice;
    do {
        std::cout << "\n=== Банковская система ===\n";
        std::cout << "1. Открыть счет\n";
        std::cout << "2. Выполнить транзакцию\n";
        std::cout << "3. Показать информацию о вашем профиле\n";
        std::cout << "4. Обновить время (демо)\n";
        std::cout << "5. Сменить пользователя\n";
        std::cout << "6. Отменить транзакцию\n";
        if (isEmployee) {
            std::cout << "7. Управление Центральным Банком\n";
        }
        std::cout << "0. Выход\n";
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                openAccount(bank);
                break;
            case 2:
                performTransaction(bank);
                break;
            case 3:
                displayClientInfo(bank);
                break;
            case 4:
                updateTime(bank);
                break;
            case 5:
                if (!loginUser(bank)) {
                    std::cout << "Авторизация не выполнена.\n";
                }
                break;
            case 6:
                reverseTransactionMenu(bank);
                break;
            case 7:
                if (isEmployee) {
                    centralBankMenu(centralBank);
                } else {
                    std::cout << "Доступ запрещен.\n";
                }
                break;
            case 0:
                std::cout << "Выход из программы.\n";
                break;
            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);
}

int main()
{
    setlocale(LC_ALL, ""); 
    
    Bank bank1(0.05, 10.0); // DepositRate = 5%, CreditRate = 10.0
    CentralBank centralBank(0.05, 0.01); // Базовая процентная ставка = 5%, базовая комиссия = 1%
    centralBank.addBank(bank1);
    
    std::cout << "=== Добро пожаловать в Банковскую систему ===\n";
    runBankInterface(bank1, centralBank);
    
    return 0;
}