#include "Account.h"

void Account::reverseTransaction(int transactionID) {
    if (transactionID < 0 || transactionID >= transactHistory.size()) {
        return; 
    }

    Transaction& transaction = transactHistory[transactionID];
    if (transaction.isReversed) {
        return; 
    }

    if (transaction.type == "deposit") {
        balance -= transaction.amount;
    } else if (transaction.type == "withdraw") {
        balance += transaction.amount;
    }

    transaction.isReversed = true;
}
