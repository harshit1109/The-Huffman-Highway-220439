#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

// Utility function to get the current date and time as a string
string getCurrentDateTime() {
    time_t now = time(0);
    char* dt = ctime(&now);
    return string(dt);
}

// Transaction class to store transaction details
class Transaction {
public:
    string date;
    double amount;
    string type;

    Transaction(double amt, const string& t) : amount(amt), type(t) {
        date = getCurrentDateTime();
    }

    void print() const {
        cout << date << " - " << type << ": $" << amount << endl;
    }
};

// Loan class to store loan details
class Loan {
public:
    double amount;
    double interestRate;
    string date;

    Loan(double amt, double rate) : amount(amt), interestRate(rate) {
        date = getCurrentDateTime();
    }

    void print() const {
        cout << "Loan taken on " << date << " - Amount: $" << amount << ", Interest Rate: " << interestRate << "%" << endl;
    }
};

// Base Account class
class Account {
protected:
    int accountNumber;
    string holderName;
    string address;
    string accountType;
    double funds;
    vector<Transaction> transactionHistory;
    vector<Loan> loanHistory;

public:
    Account(int accNum, const string& name, const string& addr, const string& type, double initialFunds)
        : accountNumber(accNum), holderName(name), address(addr), accountType(type), funds(initialFunds) {}

    virtual void deposit(double amount) {
        funds += amount;
        transactionHistory.emplace_back(amount, "Deposit");
    }

    virtual void withdraw(double amount) {
        if (amount > funds) {
            cout << "Insufficient funds!" << endl;
            return;
        }
        funds -= amount;
        transactionHistory.emplace_back(amount, "Withdrawal");
    }

    void updateAddress(const string& newAddress) {
        address = newAddress;
    }

    void viewPassbook() const {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << holderName << endl;
        cout << "Address: " << address << endl;
        cout << "Account Type: " << accountType << endl;
        cout << "Current Funds: $" << funds << endl;
        cout << "Transaction History:" << endl;
        for (const auto& txn : transactionHistory) {
            txn.print();
        }
        cout << "Loan History:" << endl;
        for (const auto& loan : loanHistory) {
            loan.print();
        }
    }

    void searchTransactionHistory(double amount) const {
        cout << "Transactions with amount $" << amount << ":" << endl;
        for (const auto& txn : transactionHistory) {
            if (txn.amount == amount) {
                txn.print();
            }
        }
    }

    void searchTransactionHistory(const string& date) const {
        cout << "Transactions on date " << date << ":" << endl;
        for (const auto& txn : transactionHistory) {
            if (txn.date.find(date) != string::npos) {
                txn.print();
            }
        }
    }

    void takeLoan(double amount, double interestRate) {
        loanHistory.emplace_back(amount, interestRate);
        funds += amount;
    }

    int getAccountNumber() const {
        return accountNumber;
    }

    double getFunds() const {
        return funds;
    }

    void receiveFunds(double amount) {
        funds += amount;
    }

    void sendFunds(Account& recipient, double amount) {
        if (amount > funds) {
            cout << "Insufficient funds!" << endl;
            return;
        }
        funds -= amount;
        recipient.receiveFunds(amount);
        transactionHistory.emplace_back(amount, "Transfer to " + to_string(recipient.getAccountNumber()));
        recipient.transactionHistory.emplace_back(amount, "Transfer from " + to_string(accountNumber));
    }
};

// Derived class for Savings Account
class SavingsAccount : public Account {
public:
    SavingsAccount(int accNum, const string& name, const string& addr, double initialFunds)
        : Account(accNum, name, addr, "Savings", initialFunds) {}
};

// Derived class for Current Account
class CurrentAccount : public Account {
public:
    CurrentAccount(int accNum, const string& name, const string& addr, double initialFunds)
        : Account(accNum, name, addr, "Current", initialFunds) {}
};

// Derived class for Joint Account
class JointAccount : public Account {
    string secondHolderName;
public:
    JointAccount(int accNum, const string& name, const string& secondName, const string& addr, double initialFunds)
        : Account(accNum, name, addr, "Joint", initialFunds), secondHolderName(secondName) {}

    void viewPassbook() {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Primary Account Holder: " << holderName << endl;
        cout << "Secondary Account Holder: " << secondHolderName << endl;
        cout << "Address: " << address << endl;
        cout << "Account Type: " << accountType << endl;
        cout << "Current Funds: $" << funds << endl;
        cout << "Transaction History:" << endl;
        for (const auto& txn : transactionHistory) {
            txn.print();
        }
        cout << "Loan History:" << endl;
        for (const auto& loan : loanHistory) {
            loan.print();
        }
    }
};

// Bank class to manage all accounts
class Bank {
    vector<Account*> accounts;
    int nextAccountNumber;

public:
    Bank() : nextAccountNumber(1001) {}

    Account* createSavingsAccount(const string& name, const string& addr, double initialFunds) {
        Account* account = new SavingsAccount(nextAccountNumber++, name, addr, initialFunds);
        accounts.push_back(account);
        return account;
    }

    Account* createCurrentAccount(const string& name, const string& addr, double initialFunds) {
        Account* account = new CurrentAccount(nextAccountNumber++, name, addr, initialFunds);
        accounts.push_back(account);
        return account;
    }

    Account* createJointAccount(const string& name, const string& secondName, const string& addr, double initialFunds) {
        Account* account = new JointAccount(nextAccountNumber++, name, secondName, addr, initialFunds);
        accounts.push_back(account);
        return account;
    }

    Account* findAccount(int accountNumber) {
        for (auto account : accounts) {
            if (account->getAccountNumber() == accountNumber) {
                return account;
            }
        }
        return nullptr;
    }

    void transferFunds(int fromAccountNumber, int toAccountNumber, double amount) {
        Account* fromAccount = findAccount(fromAccountNumber);
        Account* toAccount = findAccount(toAccountNumber);
        if (fromAccount && toAccount) {
            fromAccount->sendFunds(*toAccount, amount);
        } else {
            cout << "Invalid account number(s)!" << endl;
        }
    }

    ~Bank() {
        for (auto account : accounts) {
            delete account;
        }
    }
};

int main() {
    Bank bank;
    Account* acc1 = bank.createSavingsAccount("Alice", "MK Street", 1000);
    Account* acc2 = bank.createCurrentAccount("Bob", "Surry Lane", 500);
    Account* acc3 = bank.createJointAccount("Charlie", "Lana", "Madhav Colony", 1500);

    acc1->deposit(200);
    acc2->withdraw(100);
    acc3->takeLoan(500, 5.0);

    bank.transferFunds(acc1->getAccountNumber(), acc2->getAccountNumber(), 300);

    acc1->viewPassbook();
    acc2->viewPassbook();
    acc3->viewPassbook();

    acc1->searchTransactionHistory(200);
    acc1->searchTransactionHistory("May");

    return 0;
}
