#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// Function to validate account number
bool isValidAccountNumber(int accno) {
    return accno > 0;
}

// Base Class: Account
class account {
protected:
    string name;
    int accno;
    string atype;

public:
    void getAccountDetails() {
        cout << "\nEnter Customer Name : ";
        cin >> name;
        do {
            cout << "Enter a valid Account Number (digits only): ";
            cin >> accno;
        } while (!isValidAccountNumber(accno));  // Input validation for account number

        cout << "Enter Account Type    : ";
        cin >> atype;
    }

    void displayDetails() {
        cout << "\n\nCustomer Name : " << name;
        cout << "\nAccount Number  : " << accno;
        cout << "\nAccount Type    : " << atype;
    }

    virtual void saveAccountDetails() {
        ofstream file("account_data.txt", ios::app); // Store in a file
        file << name << " " << accno << " " << atype << endl;
        file.close();
    }
};

// Derived Class: Current Account
class current_account : public account {
private:
    float balance;
    vector<string> transactionHistory;

public:
    current_account() : balance(0.0) {}

    void recordTransaction(string type, float amount) {
        transactionHistory.push_back(type + ": " + to_string(amount));
    }

    void c_display() {
        cout << "\nBalance : " << balance;
    }

    void c_deposit() {
        float deposit;
        cout << "\nEnter amount to Deposit :  ";
        cin >> deposit;
        balance += deposit;
        recordTransaction("Deposit", deposit);
    }

    void c_withdraw() {
        float withdraw;
        cout << "\n\nBalance : " << balance;
        cout << "\nEnter amount to be withdrawn: ";
        cin >> withdraw;
        if (balance - withdraw >= 1000) {
            balance -= withdraw;
            cout << "\nBalance Amount After Withdraw: " << balance;
            recordTransaction("Withdraw", withdraw);
        } else {
            cout << "\nInsufficient Balance. Overdraft not allowed.";
        }
    }

    void displayTransactionHistory() {
        cout << "\nTransaction History:\n";
        for (const auto& transaction : transactionHistory) {
            cout << transaction << endl;
        }
    }

    void saveAccountDetails() override {
        ofstream file("current_account_data.txt", ios::app);
        file << name << " " << accno << " " << balance << endl;
        file.close();
    }
};

// Derived Class: Saving Account
class saving_account : public account {
private:
    float sav_balance;
    vector<string> transactionHistory;

public:
    saving_account() : sav_balance(0.0) {}

    void recordTransaction(string type, float amount) {
        transactionHistory.push_back(type + ": " + to_string(amount));
    }

    void s_display() {
        cout << "\nBalance :  " << sav_balance;
    }

    void s_deposit() {
        float deposit, interest;
        cout << "\nEnter amount to Deposit :  ";
        cin >> deposit;
        sav_balance += deposit;
        interest = (sav_balance * 2) / 100;  // 2% Interest
        sav_balance += interest;
        cout << "Interest Added: " << interest << endl;
        recordTransaction("Deposit", deposit);
    }

    void s_withdraw() {
        float withdraw;
        cout << "\nBalance : " << sav_balance;
        cout << "\nEnter amount to be withdrawn: ";
        cin >> withdraw;
        if (sav_balance - withdraw >= 500) {
            sav_balance -= withdraw;
            cout << "\nBalance Amount After Withdraw: " << sav_balance;
            recordTransaction("Withdraw", withdraw);
        } else {
            cout << "\nInsufficient Balance. Minimum balance of 500 required.";
        }
    }

    void displayTransactionHistory() {
        cout << "\nTransaction History:\n";
        for (const auto& transaction : transactionHistory) {
            cout << transaction << endl;
        }
    }

    void saveAccountDetails() override {
        ofstream file("saving_account_data.txt", ios::app);
        file << name << " " << accno << " " << sav_balance << endl;
        file.close();
    }
};

// Main function
int main() {
    current_account c1;
    saving_account s1;
    char type;
    string password, enteredPassword;

    cout << "\nSet your password: ";
    cin >> password;

    cout << "\nEnter S for saving account customer and C for current account customer: ";
    cin >> type;

    cout << "\nEnter your password to access the account: ";
    cin >> enteredPassword;

    if (password != enteredPassword) {
        cout << "\nIncorrect Password!";
        return 1; // Exit
    }

    int choice;
    if (type == 's' || type == 'S') {
        s1.getAccountDetails();
        s1.saveAccountDetails();

        while (1) {
            cout << "\nChoose Your Choice" << endl;
            cout << "1) Deposit" << endl;
            cout << "2) Withdraw" << endl;
            cout << "3) Display Balance" << endl;
            cout << "4) Display Transaction History" << endl;
            cout << "5) Display Full Details" << endl;
            cout << "6) Exit" << endl;
            cout << "Enter Your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    s1.s_deposit();
                    break;
                case 2:
                    s1.s_withdraw();
                    break;
                case 3:
                    s1.s_display();
                    break;
                case 4:
                    s1.displayTransactionHistory();
                    break;
                case 5:
                    s1.displayDetails();
                    s1.s_display();
                    break;
                case 6:
                    goto end;
                default:
                    cout << "\nInvalid choice, try again.";
            }
        }
    } else if (type == 'c' || type == 'C') {
        c1.getAccountDetails();
        c1.saveAccountDetails();

        while (1) {
            cout << "\nChoose Your Choice" << endl;
            cout << "1) Deposit" << endl;
            cout << "2) Withdraw" << endl;
            cout << "3) Display Balance" << endl;
            cout << "4) Display Transaction History" << endl;
            cout << "5) Display Full Details" << endl;
            cout << "6) Exit" << endl;
            cout << "Enter Your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    c1.c_deposit();
                    break;
                case 2:
                    c1.c_withdraw();
                    break;
                case 3:
                    c1.c_display();
                    break;
                case 4:
                    c1.displayTransactionHistory();
                    break;
                case 5:
                    c1.displayDetails();
                    c1.c_display();
                    break;
                case 6:
                    goto end;
                default:
                    cout << "\nInvalid choice, try again.";
            }
        }
    } else {
        cout << "\nInvalid Account Selection";
    }

end:
    cout << "\nThank You for Banking with us..";
    return 0;
}

