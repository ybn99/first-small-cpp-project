#include <iostream>
#include <string>
#include <vector>

class Customer {
    private:
        std::vector<int> depositHistory;
        std::vector<int> withdrawHistory;
        std::string fullName;
        std::string email;
        std::string password;
        double balance = 0.0;
        double depositAmount = 0;
        double withdrawAmount = 0;
        int age = 0;

    public:

    Customer(std::string& fn, int a, std::string ml, std::string& pass) : fullName(fn), age(a), password(pass), email(ml) {}

    void createAccount(bool& isAccountCreated) {
        std::cout << "\n=== CREATING NEW ACCOUNT ===\n";
        std::cout << "\nYour FULL NAME: ";
        std::cin.ignore();
        std::getline(std::cin, fullName);
        do{
        std::cout << "Your AGE (only 18+): ";
        std::cin >> age;
        }while (age <= 18);
        std::cout << "Your E-MAIL: ";
        std::cin >> email;
        std::cout << "Your NEW PASSWORD: ";
        std::cin >> password;
        isAccountCreated = true;
    }

    void viewAccount(bool& isAccountCreated) {
        if (isAccountCreated == true) {
            std::cout << "\n=== YOUR ACCOUNT ===";
            std::cout << "\n1. Your FULL NAME: " << Customer::fullName;
            std::cout << "\n2. Your E-MAIL: " << Customer::email;
            std::cout << "\n3. Your BALANCE: $" << Customer::balance;
        } else {
            notCreatedAccount();
        }
    }

    void viewDepositHistory(bool& isAccountCreated) {
        if (!isAccountCreated) {
            notCreatedAccount();
        } else if (isAccountCreated && depositAmount <= 0) {
            std::cout << "\nNo deposits have been made.";
        } else {
        std::cout << '\n';
        for (int depositTimes : depositHistory) {
            std::cout << "Deposited: $" << depositTimes << '\n';
            }
        }
    }

    void getDepositAmount(bool& isAccountCreated) {
        if (!isAccountCreated) {
            notCreatedAccount();
        } else {
        std::cout << "\nHow much would you like to deposit?: $";
        std::cin >> depositAmount;
        std::cout << "\nNew balance: $" << (balance += depositAmount);
        depositHistory.push_back(depositAmount);
        }
    }

    void viewWithdrawHistory(bool& isAccountCreated) {
        if (!isAccountCreated) {
            notCreatedAccount();
        } else if (isAccountCreated && withdrawAmount <= 0) {
            std::cout << "\nNo withdraws have been made.";
        } else {
        std::cout << "'\n";
        for (int withdrawTimes : withdrawHistory) {
            std::cout << "Withdrawn: $" << withdrawTimes << '\n';
            }
        }
    }

    void getWithdrawAmount(bool& isAccountCreated) {        // Doulepse epanw se auto to function.
        if (!isAccountCreated) {
            notCreatedAccount();
        } else {
        std::cout << "\nHow much would you like to withdraw?: $";
        std::cin >> withdrawAmount;
        withdrawAmount > balance ? std::cout << "\nUnable to withdraw." :
        std::cout << "\nNew balance: $" << (balance -= withdrawAmount);
        withdrawHistory.push_back(withdrawAmount);
        }
    }

    void notCreatedAccount() {
        std::cout << "\nYou have not created an account.";
    }
};

void showMenu() {       // This function simply shows the menu of actions that the user can make
    std::cout << "\n\n=== MAIN MENU ===\n";
    std::cout << "1. Create Account.\n";
    std::cout << "2. View Account.\n";
    std::cout << "3. Deposit.\n";
    std::cout << "4. View Deposit History.\n";
    std::cout << "5. Withdraw.\n";
    std::cout << "6. View Withdraw History.\n";
    std::cout << "0. Exit.\n";
    std::cout << "Choice: ";
};

void handleMenu(int customerChoice, Customer& customer1, bool& isAccountCreated) {     // This function basically handles the user's input and executes accordingly.
    switch (customer1, customerChoice) {
        case 1:
            customer1.createAccount(isAccountCreated);
            break;
        case 2:
            customer1.viewAccount(isAccountCreated);
            break;
        case 3:
            customer1.getDepositAmount(isAccountCreated);
            break;
        case 4: customer1.viewDepositHistory(isAccountCreated);
            break;
        case 5: customer1.getWithdrawAmount(isAccountCreated);
            break;
        case 6: customer1.viewWithdrawHistory(isAccountCreated);
            break;
        case 0: std::exit(0);
    };
};

int main() {
    int customerChoice = 0;
    bool isAccountCreated = false;
    std::string empty = "";
    Customer customer1(empty, 0, empty, empty);

    do {
        showMenu();        // Calls the showMenu function
        std::cin >> customerChoice;     // The user's input is stored inside of this variable and then
        handleMenu(customerChoice, customer1, isAccountCreated);     // the user is redirected inside the handleMenu function
    } while (customerChoice != 0);      // All of the above happen unless this variable takes the 0 value

    return 0;
}

